# Computational Mathematics

Finite Element Method using C++ and visualization with OpenGL. This repository is my implementation of numerical analysis procedures, which is ported from [FEMSharp](https://github.com/stijnruiter/FemSharp). 

For educational purposes, I will implement all numerical methods myself, and only use the GLFW/GLAD libraries of OpenGL binding and Google Test and Benchmark for testing.

## Installation
The project uses CMake, and has various build targets for unit and benchmark tests. To install and
run the main program, the following commands can be used:

```
git clone --recurse-submodules git@github.com:stijnruiter/ComputationalMath.git
cmake -DCMAKE_BUILD_TYPE=[Debug|Release] -Bout -S.
cmake --build out --target Physics
debug\bin\Physics.exe
```

## Current state
The main entry point of this repository is located in the Physics directory, which solves and renders various numerical problems (see below), which can be toggled by pressing _1_. Rotating is possible with the arrow keys. 

![FEM simulations and Delaunay triangulations.](FemDemo.gif)

### Linear Algebra
- Dense Row vector data structure
- Dense Matrix data structure (only row-major storage at the moment)
- Some simple matrix vector arithmetics (nothing optimized)
    - Operators for scalar/vector/matrix arithmetics
- _LU_ factorization (with partial pivoting)
- Solving the system **Ax=b** and **AX=B** 
    - Determinant and inverse of matrix

### Geometry
- Incremental Delaunay triangulation[^1]
    - Ruppert's Algorithm for producing quality triangular planar meshes[^2]

### Finite Element Methods
- Basic matrix assembly precedure for common Weak Formulations terms[^3]
    - Simple boundary conditions using lambda function 

## Up next
__Linear Algebra__
- Stack allocated Linear Algebra structures
    - Currently, all matrices are heap allocated
    - _Could be interesting for smaller common vector/matrices, e.g. 4x4 matrix_
- Column/Row major matrix switching
- Sparse matrices
- Introducte SSE/AVX2 instructions in the Linear Algebra precedures
- Cache friendly precedures

__Numerical methods__
- Finite Element Method with deforming meshes
- Material Point Method using B-splines
- Method of Moments 

### Finite Element Problem Sets
Currently, the project is three FEM scenes implemented, solving the partial differential equation and rendering the solution. The problems are the well-known Helmholtz equation with a source, Laplace's equation with boundary conditions, and the heat equation without source, a simple time dependent problem. For the simulations, a 2-dimensional rectangular grid is used, where $\Omega=[x_1, x_2]\times[y_1, y_2]$. The implemented FEM problems are then defined below.


##### Helmholtz equation:
$$\begin{align*} 
-\nabla^2 u + k\cdot u &= f\\ 
\nabla u \cdot\mathbf{\dot{n}}&=0 \text{ on  } \partial\Omega,
\end{align*}$$

##### Laplace's equation:

$$\begin{align*} 
-\nabla^2 u &= f,\\ 
\frac{\partial u}{\partial n}(x,y_1) &= \frac{\partial u}{\partial n}(x,y_2)=0,\\
u(x_1, y) &= u(x_2, y) =0.
\end{align*}$$

##### Heat equation:

$$\begin{align*}
\frac{\partial T}{\partial t}&=k\nabla^2 T\\
\nabla u \cdot\mathbf{\dot{n}}&=0 \text{ on  } \partial\Omega,
\end{align*}$$

## References
[^1]: Guibas L.J. et al. (1992) _Randomized incremental construction of Delaunay and Voronoi diagrams_ Algorithmica, 7(1), 381 - 413 [https://doi.org/10.1007/BF01758770](https://doi.org/10.1007/BF01758770)

[^2]: Ruppert J. (1995) _A Delaunay Refinement Algorithm for Quality 2-Dimensional Mesh Generation_ Journal of Algorithms, 18(3), 548-585 [https://doi.org/10.1006/jagm.1995.1021](https://doi.org/10.1006/jagm.1995.1021)

[^3]: van Kan J. et al. (2005) _Numerical Methods in Scientific Computing_ Delft Academic Press [https://doi.org/10.59490/t.2023.009](https://doi.org/10.59490/t.2023.009)