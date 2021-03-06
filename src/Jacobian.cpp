#include <cassert>
#include "Jacobian.h"
#include "Timer/CH_Timer.H"

using namespace arma;

Jacobian::Jacobian(const PolyMesh &a_msh, int a_deg, int a_nc) : msh(&a_msh)
{
    int i;
    unsigned int j;
    int numBlocks;
    
    n_rows = msh->np;
    nc = a_nc;
    deg = a_deg;
    bl = nc*(deg + 1)*(deg + 2)/2;
    
    mat zeroMat = zeros<mat>(bl, bl);
    
    numBlocks = 0;
    
    for (i = 0; i < n_rows; i++)
    {
        blocks.push_back(zeroMat);
        colIndices.push_back(i);
        rowBlock.push_back(numBlocks);
        numBlocks++;
        
        for (j = 0; j < msh->p2p[i].size(); j++)
        {
            if (msh->p2p[i][j] >= 0)
            {
                blocks.push_back(zeroMat);
                colIndices.push_back(msh->p2p[i][j]);
                numBlocks++;
            } else if (msh->bc.at(msh->p2p[i][j]).periodic)
            {
                blocks.push_back(zeroMat);
                colIndices.push_back(msh->bc.at(msh->p2p[i][j]).p2);
                numBlocks++;
            }
        }
    }
    
    rowBlock.push_back(numBlocks);
    nb = numBlocks;
}

Jacobian& Jacobian::operator=(const Jacobian &J2)
{
    BlockMatrix::operator=(J2);
    
    nc = J2.nc;
    deg = J2.deg;
    
    return *this;
}

MeshFn Jacobian::matvec(const MeshFn &x)
{
    CH_TIMERS("Jacobian matvec");
    MeshFn result = x;
    BlockMatrix::matvec(result.a.memptr());
    
    return result;
}

MeshFn Jacobian::solve(const MeshFn &b, Preconditioner &pc, Solver s/* = kGMRESSolver */)
{
    MeshFn result(*msh, deg, nc);
    vec bVec = vectorise(b.a);
    vec x = zeros<vec>(bVec.n_rows);
    int basisSize = (deg + 1)*(deg + 2)/2;
    
    double tol = 1.e-14;
    int maxIt = 90000;
    
    switch(s)
    {
        case kGMRESSolver:
            gmres(bVec, x, 20, tol, maxIt, pc);
            cout << "    GMRES iterations: " << maxIt << endl;
            break;
        case kJacobiSolver:
            jacobi(bVec, x, tol, maxIt, pc);
            cout << "    Jacobi iterations: " << maxIt << endl;
            break;
    }
    
    // hack to reshape vector into cube...
    cube xCube(x.n_rows, 1, 1);
    xCube.slice(0) = x;
    
    result.a = reshape(xCube, basisSize, nc, msh->np);
    
    return result;
}

Jacobian& Jacobian::operator +=(const MassMatrix &M)
{
    int i, b;
    b = M.bl;
    
    for (i = 0; i < n_rows; i++)
    {
        blocks[rowBlock[i]] += M.blocks[i];
    }
    
    return *this;
}

Jacobian& Jacobian::operator -=(const MassMatrix &M)
{
    int i, c, b;
    b = M.bl;
    
    for (i = 0; i < n_rows; i++)
    {
        for (c = 0; c < nc; c++)
        {
            blocks[rowBlock[i]].submat(c*b, c*b, (c+1)*b-1, (c+1)*b-1) -= M.blocks[i];
        }
    }
    
    return *this;
}
