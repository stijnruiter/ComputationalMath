#include <gtest/gtest.h>

#include <LinearAlgebra/ColumnVector.h>

TEST(example, subtract) {
  double res;
  res = 1.0 - 2.0;
  ASSERT_NEAR(res, -1.0, 1.0e-11);
}
