# Computational Mathematics

Finite Element Method using C++ and visualization with OpenGL. This repository is my implementation of numerical analysis procedures, which is ported from [FEMSharp](https://github.com/stijnruiter/FemSharp), a C#/.NET repository I've created earlier.

## Current state

### Linear Algebra
- Dense Row vector data structure
- Dense Matrix data structure (only row-major storage at the moment)
- Some simple matrix vector arithmetics (nothing optimized)
    - Operators for scalar/vector/matrix arithmetics
- _LU_ factorization (with partial pivoting)
- Solving the system **Ax=b** and **AX=B** 
    - Determinant and inverse of matrix

### Geometry
- Incremental Delaunay triangulation
    - Ruppert's Algorithm for producing quality triangular planar meshes

### Finite Element Methods
- Basic matrix assembly precedure for common Weak Formulation
    - Simple boundary conditions using lambda function 

## Up next
- Stack allocated Linear Algebra structures
    - Currently, all matrices are heap allocated
    - _Could be interesting for smaller common vector/matrices, e.g. 4x4 matrix_
- Column/Row major matrix switching
- Sparse matrices

- Finite Element Method with deforming meshes
- Material Point Method using B-splines
- Method of Moments 

### Finite Element Problem Sets
Currently, the project is  able to solve the Helmholtz equation with a source and Laplace's equation with boundary conditions. For the simulations, a 2-dimensional rectangular grid is used, where $\Omega=[x_1, x_2]\times[y_1, y_2]$. The implemented FEM problems are then defined as

$$\begin{align*} 
-\nabla^2 u + k\cdot u &= f\\ 
\nabla u \cdot\mathbf{\dot{n}}&=0 \text{ on  } \partial\Omega,
\end{align*}$$

and 

$$\begin{align*} 
-\nabla^2 u = f,\\ 
\frac{\partial u}{\partial n}(x,y_1) = \frac{\partial u}{\partial n}(x,y_2)=0,\\
u(x_1, y) = u(x_2, y) =0.
\end{align*}$$