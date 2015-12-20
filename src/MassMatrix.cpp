#include "MassMatrix.h"
#include "Legendre.h"

using namespace arma;
using namespace std;

MassMatrix::MassMatrix(PolyMesh &m, int d) : msh(m), deg(d)
{
    int i, j, k;
    int basisSize = (deg+1)*(deg+2)/2;
    int N;
    double integ;
    ProductFunctor prod(msh);
    
    prod.phi = zeros<vec>(basisSize);
    prod.psi = zeros<vec>(basisSize);
    
    prod.m = deg+1;
    
    N = msh.np*basisSize;
    
    matrix  = sp_mat(N, N);
    
    for (i = 0; i < msh.np; i++)
    {
        prod.i = i;
        
        for (j = 0; j < basisSize; j++)
        {
            prod.phi[j] = 1.0;
            for (k = 0; k < basisSize; k++)
            {
                prod.psi[k] = 1.0;
                
                integ = msh.polygonIntegral(prod, i);
                
                matrix(i*basisSize + j, i*basisSize + k) = integ;
                matrix(i*basisSize + k, i*basisSize + j) = integ;
                
                prod.psi[k] = 0.0;
            }
            prod.phi[j] = 0.0;
        }
    }
}

MeshFn MassMatrix::solve(const MeshFn &fn) const
{
    int component;
    int basisSize = (deg+1)*(deg+2)/2;
    MeshFn result(msh, deg, fn.nc);
    
    for (component = 0; component < fn.nc; component++)
    {
        mat fnComponent = fn.a.tube(0, component, result.a.n_rows - 1, component);
        vec b = vectorise(fnComponent, 1).t();
        vec x = arma::spsolve(matrix, b);
        
        result.a.tube(0, component, result.a.n_rows - 1, component) = 
            reshape(x, basisSize, msh.np).t();
    }
    
    return result;
}

void MassMatrix::spy(std::string filename)
{
    int i, j;
    ofstream file;
    file.open(filename);
    
    for (i = 0; i < matrix.n_rows; i++)
    {
        for (j = 0; j < matrix.n_cols; j++)
        {
            if (matrix(i, j) != 0.0)
            {
                file << i << "\t" << j << "\t" << matrix(i, j) << endl;
            }
        }
    }
    
    file.close();
}
