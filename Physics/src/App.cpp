#include <iostream>
#include <LinearAlgebra/VectorBase.h>
#include <LinearAlgebra/Matrix.h>

#include <LinearAlgebra/FactorizationLU.h>
int main()
{
	Matrix<float> mat(3, 3, new float[9]{
		1,2,3,
		3,2,1,
		2,1,3
	});
	ColumnVector<float> rhs(3, new float[3]{1, 2,2});

	LinearAlgebra::Factorization::FactorizationResult<float> factorization = LinearAlgebra::Factorization::PluFactorization(mat, 1e-5f);

	std::cout << "A = PLU = " << mat << std::endl;
	std::cout << "U = " << LinearAlgebra::Factorization::ExtractUpperMatrix(factorization.Factorization) << std::endl;
	std::cout << "L = " << LinearAlgebra::Factorization::ExtractLowerMatrix(factorization.Factorization) << std::endl;
	std::cout << "Determinant: " << LinearAlgebra::Factorization::Determinant(factorization) << std::endl;
	ColumnVector<float> result = LinearAlgebra::Factorization::LUSolve(mat, rhs, 1e-5f);
	std::cout << std::endl << "b = " << rhs << std::endl; 
	std::cout << "A\\b = " << result << std::endl;
	return 0;
}