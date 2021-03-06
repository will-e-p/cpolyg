#include <cmath>
#include "Meshes.h"
#include "Advection.h"
#include "TimeIntegration.h"

// Initial conditions
double gaussian(double x, double y) {
    return exp(-150*((x-0.25)*(x-0.25) + (y-0.5)*(y-0.5)));
}

double zero(double x, double y) { return 0; }

int main() {
    // specify the degree of polynomials to use
    int deg = 2;
    // specify the size of each element in the mesh
    double h = 0.1;
    // specify the time step
    double dt = h/10;
    
    // create the mesh, in this case hexagonal tessellation
    // of the unit square
    PolyMesh msh = hexUnitSquare(h);
    
    // create a mesh function by interpolating the 
    // initial conditions defined by the function above
    MeshFn f = MeshFn(msh, gaussian, deg);
    
    // specify the advection equation
    // with zero Dirichlet boundary conditions
    VecFnCallbackFunctor zeroFunctor(zero);
    BoundaryConditions bc = 
        BoundaryConditions::dirichletConditions(msh, &zeroFunctor);
    Advection eqn(msh, bc);
    
    // compute the mass matrix
    MassMatrix M(msh, deg, eqn.nc);
    
    // create the time integration object
    ForwardEuler ti(M, eqn);
    
    for (int i = 0; i < 200; i++) {
        std::cout << "Beginning timestep " << i << std::endl;
        f = ti.advance(f, dt, i*dt);
        f.gnuplot("plt/u" + std::to_string(i) + ".gnu");
    }
    
    return 0;
}
