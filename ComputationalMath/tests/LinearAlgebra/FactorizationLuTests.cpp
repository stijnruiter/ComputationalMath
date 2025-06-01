#include <LinearAlgebra/FactorizationLU.hpp>
#include <LinearAlgebra/Matrix.hpp>
#include <gtest/gtest.h>

namespace LinearAlgebra::Factorization
{
    static auto FacorizationMatricesSets = ::testing::Values(
        std::make_tuple(
            Matrix<float>({
                {6, -7},
                {0, 3},
            }),
            Matrix<float>({{1, 0},
                           {0, 1}}),
            Matrix<float>({{6, -7},
                           {0, 3}}),
            new int[2]{0, 1},
            0),
        std::make_tuple(
            Matrix<float>({{1, 2, 3},
                           {3, 2, 1},
                           {2, 1, 3}}),
            Matrix<float>({
                {1, 0, 0},
                {1.0f / 3, 1, 0},
                {2.0f / 3, -1.0f / 4, 1},
            }),
            Matrix<float>({
                {3, 2, 1},
                {0, 4.0f / 3, 8.0f / 3},
                {0, 0, 3},
            }),
            new int[3]{1, 0, 2},
            1),
        std::make_tuple(
            Matrix<float>({{1.0f, 5.0f, 3.2f, 4.3f, 8.2f, 6.0f},
                           {1.0f, 4.3f, 5.6f, 2.4f, 5.1f, -5.0f},
                           {0.0f, 0.0f, 3.1f, 4.0f, 5.0f, 6.0f},
                           {0.0f, 18.0f, 0.1f, 2.0f, 5.0f, 8.0f},
                           {1.0f, -50.0f, -3.21f, 3.0f, 1.0f, 0.0f},
                           {0.0f, -2.0f, 3.1f, 4.0f, 0.0f, 0.0f}}),
            Matrix<float>({{1, 0, 0, 0, 0, 0},
                           {1, 1, 0, 0, 0, 0},
                           {0, 0.03636f, 1, 0, 0, 0},
                           {1, 0.01273f, 0.74453f, 1, 0, 0},
                           {0, 0, 0.93007f, -0.04815f, 1, 0},
                           {0, -0.32727f, -0.59939f, -0.81695f, 0.03990f, 1}}),
            Matrix<float>({{1, 5, 3.2f, 4.3f, 8.2f, 6},
                           {0, -55, -6.41f, -1.3f, -7.2f, -6},
                           {0, 0, 3.33309f, 4.04727f, 0.26182f, 0.21818f},
                           {0, 0, 0, -4.89677f, -3.20329f, -11.08608f},
                           {0, 0, 0, 0, 4.60226f, 5.26332f},
                           {0, 0, 0, 0, 0, -3.09968f}}),
            new int[6]{0, 4, 5, 1, 2, 3},
            4));
    class MatrixLuFactorizationTests : public ::testing::TestWithParam<std::tuple<Matrix<float>, Matrix<float>, Matrix<float>, int*, int>>
    {
    };

    TEST_P(MatrixLuFactorizationTests, PluFactorization_WhenMatrixInvertible_ShouldComputeCorrectFactorizationResults)
    {
        Matrix<float> matrix = std::get<0>(GetParam());
        Matrix<float> expectedLower = std::get<1>(GetParam());
        Matrix<float> expectedUpper = std::get<2>(GetParam());
        int* expectedPivots = std::get<3>(GetParam());
        int expectedPermutationCount = std::get<4>(GetParam());

        FactorizationResult<float> results = PluFactorization(matrix, 1e-5f);
        std::stringstream os;
        os << results.Factorization;
        std::string result = os.str();

        EXPECT_EQ(results.PermutationCount, expectedPermutationCount);
        EXPECT_TRUE(std::equal(expectedPivots, expectedPivots + matrix.GetColumnCount(), results.Pivots));

        Matrix<float> lower = ExtractLowerMatrix(results.Factorization);
        Matrix<float> upper = ExtractUpperMatrix(results.Factorization);
        EXPECT_TRUE(upper.ElementwiseCompare(expectedUpper, 1e-5f));
        EXPECT_TRUE(lower.ElementwiseCompare(expectedLower, 1e-5f));

        // PA = LU
        Matrix<float> pa = Matrix<float>(matrix.GetRowCount(), matrix.GetColumnCount());
        for (size_t i = 0; i < matrix.GetRowCount(); i++)
        {
            for (size_t j = 0; j < matrix.GetColumnCount(); j++)
            {
                pa(i, j) = matrix(results.Pivots[i], j);
            }
        }
        Matrix<float> LU = lower * upper;
        EXPECT_TRUE(LU.ElementwiseCompare(pa, 1e-5f));
    }
    INSTANTIATE_TEST_SUITE_P(PluFactorization_WhenMatrixInvertible_ShouldComputeCorrectFactorizationResults, MatrixLuFactorizationTests, FacorizationMatricesSets);

    static auto ForwardSubstitutionColumnVectorSets = ::testing::Values(
        std::make_tuple(
            Matrix<int>({{1, 0},
                         {2, 1}}),
            ColumnVector<int>({1, 5}),
            ColumnVector<int>({1, 3})),
        std::make_tuple(
            Matrix<int>({{1, 0, 0, 0},
                         {2, 1, 0, 0},
                         {3, 4, 1, 0},
                         {1, 2, 3, 1}}),
            ColumnVector<int>({1, 5, 3, 4}),
            ColumnVector<int>({1, 3, -12, 33})));

    class ForwardSubstitutionVectorTests : public ::testing::TestWithParam<std::tuple<Matrix<int>, ColumnVector<int>, ColumnVector<int>>>
    {
    };

    TEST_P(ForwardSubstitutionVectorTests, ForwardSubstitutionInPlace_WhenColumnVector_ShouldReturnColumnVector)
    {
        Matrix<int> matrix = std::get<0>(GetParam());
        ColumnVector<int> rhs = std::get<1>(GetParam());
        ColumnVector<int> expectedResult = std::get<2>(GetParam());

        ForwardSubstitutionInPlace(matrix, rhs);
        EXPECT_TRUE(rhs.ElementwiseCompare(expectedResult, 1e-5f));
    }
    INSTANTIATE_TEST_CASE_P(ForwardSubstitutionInPlace_WhenColumnVector_ShouldReturnColumnVector, ForwardSubstitutionVectorTests, ForwardSubstitutionColumnVectorSets);

    static auto BackwardSubstitutionColumnVectorSets = ::testing::Values(
        std::make_tuple(
            Matrix<int>({
                {3, 4},
                {0, 2},
            }),
            ColumnVector<int>({3, 6}),
            ColumnVector<int>({-3, 3})),
        std::make_tuple(
            Matrix<int>({{3, 4, 5, 6},
                         {0, 2, 4, 2},
                         {0, 0, 6, 5},
                         {0, 0, 0, 2}}),
            ColumnVector<int>({3, 6, 3, 6}),
            ColumnVector<int>({-7, 4, -2, 3})));

    class BackwardSubstitutionVectorTests : public ::testing::TestWithParam<std::tuple<Matrix<int>, ColumnVector<int>, ColumnVector<int>>>
    {
    };
    TEST_P(BackwardSubstitutionVectorTests, BackwardSubstitutionInPlace_WhenColumnVector_ShouldReturnColumnVector)
    {
        Matrix<int> matrix = std::get<0>(GetParam());
        ColumnVector<int> rhs = std::get<1>(GetParam());
        ColumnVector<int> expectedResult = std::get<2>(GetParam());

        BackwardSubstitutionInPlace(matrix, rhs);
        EXPECT_TRUE(rhs.ElementwiseCompare(expectedResult, 1e-5f));
    }
    INSTANTIATE_TEST_CASE_P(BackwardSubstitutionInPlace_WhenColumnVector_ShouldReturnColumnVector, BackwardSubstitutionVectorTests, BackwardSubstitutionColumnVectorSets);

    static auto LinearSystemSets = ::testing::Values(
        std::make_tuple(
            Matrix<float>({{6, -7},
                           {0, 3}}),
            ColumnVector<float>({3, 4}),
            ColumnVector<float>({37.0f / 18, 4.0f / 3})),
        std::make_tuple(
            Matrix<float>({{1, 2, 3},
                           {3, 2, 1},
                           {2, 1, 3}}),
            ColumnVector<float>({1, 2, 2}),
            ColumnVector<float>({3.0f / 4, -1.0f / 4, 1.0f / 4})),
        std::make_tuple(
            Matrix<float>({
                {1.0f, 5.0f, 3.2f, 4.3f, 8.2f, 6.0f},
                {1.0f, 4.3f, 5.6f, 2.4f, 5.1f, -5.0f},
                {0.0f, 0.0f, 3.1f, 4.0f, 5.0f, 6.0f},
                {0.0f, 18.0f, 0.1f, 2.0f, 5.0f, 8.0f},
                {1.0f, -50.0f, -3.21f, 3.0f, 1.0f, 0.0f},
                {0.0f, -2.0f, 3.1f, 4.0f, 0.0f, 0.0f},
            }),
            ColumnVector<float>({1.0f, 2.0f, 3.3f, 4.4f, 5.5f, 6.6f}),
            ColumnVector<float>({-10.2777f,
                                 0.214471f,
                                 -3.5016f,
                                 4.47097f,
                                 1.8482f,
                                 -2.16166f})));
    class SolveUsingLuTests : public ::testing::TestWithParam<std::tuple<Matrix<float>, ColumnVector<float>, ColumnVector<float>>>
    {
    };
    TEST_P(SolveUsingLuTests, SolveLU_WhenSystemIsGiven_ShouldComputeCorrectly)
    {
        Matrix<float> matrix = std::get<0>(GetParam());
        ColumnVector<float> rhs = std::get<1>(GetParam());
        ColumnVector<float> expectedResult = std::get<2>(GetParam());

        ColumnVector<float> values = LUSolve(matrix, rhs, 5e-5f);
        EXPECT_TRUE(values.ElementwiseCompare(expectedResult, 5e-5f));
    }
    INSTANTIATE_TEST_CASE_P(SolveLU_WhenSystemIsGiven_ShouldComputeCorrectly, SolveUsingLuTests, LinearSystemSets);

    static auto InverseMatrixSets = ::testing::Values(
        std::make_tuple(
            Matrix<float>({
                {1, 2},
                {3, 4},
            }),
            Matrix<float>({{-2, 1},
                           {1.5f, -0.5f}})),
        std::make_tuple(
            Matrix<float>({
                {1.0f, 5.0f, 3.2f, 4.3f, 8.2f, 6.0f},
                {1.0f, 4.3f, 5.6f, 2.4f, 5.1f, -5.0f},
                {0.0f, 0.0f, 3.1f, 4.0f, 5.0f, 6.0f},
                {0.0f, 18.0f, 0.1f, 2.0f, 5.0f, 8.0f},
                {1.0f, -50.0f, -3.21f, 3.0f, 1.0f, 0.0f},
                {0.0f, -2.0f, 3.1f, 4.0f, 0.0f, 0.0f},
            }),
            Matrix<float>({
                {2.48269f, -1.08299f, -1.39254f, -1.49448f, -0.399701f, 0.420458f},
                {-0.0065064f, 0.0108966f, -0.0450246f, 0.0454587f, -0.00439019f, 0.0260444f},
                {0.426931f, -0.234924f, 0.179534f, -0.601676f, -0.192006f, -0.0526869f},
                {-0.334124f, 0.187515f, -0.161651f, 0.489028f, 0.14661f, 0.303855f},
                {-0.435192f, 0.311171f, 0.202564f, 0.368953f, 0.124022f, -0.198927f},
                {0.364829f, -0.262941f, 0.0128716f, -0.322614f, -0.101888f, -0.00957533f},
            })));
    class InverseMatrixTests : public ::testing::TestWithParam<std::tuple<Matrix<float>, Matrix<float>>>
    {
    };
    TEST_P(InverseMatrixTests, InverseMatrix_ShouldReturnMatrix)
    {
        Matrix<float> matrix = std::get<0>(GetParam());
        Matrix<float> expectedInverse = std::get<1>(GetParam());

        Matrix<float> inverse = InverseMatrix(matrix, 1e-5f);

        EXPECT_TRUE(inverse.ElementwiseCompare(expectedInverse, 5e-5f));
    }
    INSTANTIATE_TEST_CASE_P(InverseMatrix_WhenSystemIsGiven_ShouldComputeCorrectly, InverseMatrixTests, InverseMatrixSets);

    TEST(FactorizationLUTests, SubstitutionInPlace_WhenMatrixMatrixDimensionMismatch_ShouldThrow)
    {
        ColumnVector<float> vec(3);
        Matrix<float> nonSquare5x3(5, 3);
        Matrix<float> nonSquare3x5(3, 5);

        EXPECT_THROW(ForwardSubstitutionInPlace(Matrix<float>(5, 3), nonSquare5x3), std::invalid_argument) << "Non-square matrix should throw";
        EXPECT_THROW(ForwardSubstitutionInPlace(Matrix<float>(5, 5), nonSquare5x3), std::invalid_argument) << "Matrix Matrix should have same dimensions";
        EXPECT_THROW(ForwardSubstitutionInPlace(Matrix<float>(5, 5), nonSquare3x5), std::invalid_argument) << "Matrix Matrix should have same dimensions";

        EXPECT_THROW(ForwardSubstitutionInPlace(Matrix<float>(5, 3), vec), std::invalid_argument) << "Non-square matrix should throw";
        EXPECT_THROW(ForwardSubstitutionInPlace(Matrix<float>(5, 5), vec), std::invalid_argument) << "Matrix Vector should have same dimensions";

        EXPECT_THROW(BackwardSubstitutionInPlace(Matrix<float>(5, 3), nonSquare5x3), std::invalid_argument) << "Non-square matrix should throw";
        EXPECT_THROW(BackwardSubstitutionInPlace(Matrix<float>(5, 5), nonSquare5x3), std::invalid_argument) << "Matrix Matrix should have same dimensions";
        EXPECT_THROW(BackwardSubstitutionInPlace(Matrix<float>(5, 5), nonSquare3x5), std::invalid_argument) << "Matrix Matrix should have same dimensions";

        EXPECT_THROW(BackwardSubstitutionInPlace(Matrix<float>(5, 3), vec), std::invalid_argument) << "Non-square matrix should throw";
        EXPECT_THROW(BackwardSubstitutionInPlace(Matrix<float>(5, 5), vec), std::invalid_argument) << "Matrix Vector should have same dimensions";

        EXPECT_THROW(LUSolve(Matrix<float>(5, 3), vec, 1e-5f), std::invalid_argument) << "Non-square matrix should throw";
        EXPECT_THROW(LUSolve(Matrix<float>(5, 5), vec, 1e-5f), std::invalid_argument) << "Matrix Vector should have same dimensions";

        EXPECT_THROW(LUSolve(Matrix<float>(5, 3), nonSquare5x3, 1e-5f), std::invalid_argument) << "Non-square matrix should throw";
        EXPECT_THROW(LUSolve(Matrix<float>(5, 5), nonSquare5x3, 1e-5f), std::invalid_argument) << "Matrix Matrix should have same dimensions";
        EXPECT_THROW(LUSolve(Matrix<float>(5, 5), nonSquare3x5, 1e-5f), std::invalid_argument) << "Matrix Matrix should have same dimensions";

        EXPECT_THROW(InverseMatrix(Matrix<float>(5, 3), 1e-5f), std::invalid_argument) << "Non-square matrix should throw";
    }

    static auto DeterminantMatrixSets = ::testing::Values(
        std::make_tuple(
            Matrix<float>({{6, -7},
                           {0, 3}}),
            18.0f),
        std::make_tuple(
            Matrix<float>({{1, 2, 3},
                           {3, 2, 1},
                           {2, 1, 3}}),
            -12.0f),
        std::make_tuple(
            Matrix<float>({
                {1.0f, 5.0f, 3.2f, 4.3f, 8.2f, 6.0f},
                {1.0f, 4.3f, 5.6f, 2.4f, 5.1f, -5.0f},
                {0.0f, 0.0f, 3.1f, 4.0f, 5.0f, 6.0f},
                {0.0f, 18.0f, 0.1f, 2.0f, 5.0f, 8.0f},
                {1.0f, -50.0f, -3.21f, 3.0f, 1.0f, 0.0f},
                {0.0f, -2.0f, 3.1f, 4.0f, 0.0f, 0.0f},
            }),
            -12805.829f));

    class DeterminantMatrixTests : public ::testing::TestWithParam<std::tuple<Matrix<float>, float>>
    {
    };
    TEST_P(DeterminantMatrixTests, DeterminantMatrix_WhenSystemIsGiven_ShouldComputeCorrectly)
    {
        Matrix<float> matrix = std::get<0>(GetParam());
        float expectedDeterminant = std::get<1>(GetParam());

        float determinant = Determinant(matrix, 1e-5f);

        EXPECT_NEAR(determinant, expectedDeterminant, 1e-5f);
    }
    INSTANTIATE_TEST_CASE_P(DeterminantMatrix_WhenSystemIsGiven_ShouldComputeCorrectly, DeterminantMatrixTests, DeterminantMatrixSets);
}