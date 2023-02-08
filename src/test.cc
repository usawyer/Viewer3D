#include <gtest/gtest.h>

#include "./3DViewer_v2/affine_transformation.h"
#include "./3DViewer_v2/model.h"

TEST(parsing_tests, test_vertexes) {
  Model test;
  test.ParsingFile("./objectives/cube.obj");
  EXPECT_EQ(test.GetNumberOfVertexes(), 8);
  EXPECT_EQ(test.GetNumberOfFacets(), 36);
}

TEST(parsing_tests, test_vertexes_2) {
  Model test;
  test.ParsingFile("./objectives/coca-cola.obj");
  EXPECT_EQ(test.GetNumberOfVertexes(), 41461);
  EXPECT_EQ(test.GetNumberOfFacets(), 155352);
}

TEST(transformation_tests, translate) {
  TransformMatrix test;
  test.Translate(0.1, 0.0, 0.0);

  Matrix result(4, 4,
                {{1.0, 0.0, 0.0, 0.1},
                 {0.0, 1.0, 0.0, 0.0},
                 {0.0, 0.0, 1.0, 0.0},
                 {0.0, 0.0, 0.0, 1.0}});
  EXPECT_EQ(result.eq_matrix(test.GetTransform()), true);
}

TEST(transformation_tests, rotate) {
  TransformMatrix test;
  test.Rotate(0.0, 1.0, 0.0);

  Matrix result(4, 4,
                {{0.999848, 0, -0.0174524, 0},
                 {0.0, 1.0, 0.0, 0.0},
                 {0.0174524, 0.0, 0.999848, 0.0},
                 {0.0, 0.0, 0.0, 1.0}});
  EXPECT_EQ(result.eq_matrix(test.GetTransform()), true);
}

TEST(transformation_tests, scale) {
  TransformMatrix test;
  test.Scale(1.01, 1.0, 1.0);

  Matrix result(4, 4,
                {{1.01, 0.0, 0.0, 0.0},
                 {0.0, 1.0, 0.0, 0.0},
                 {0.0, 0.0, 1.0, 0.0},
                 {0.0, 0.0, 0.0, 1.0}});
  EXPECT_EQ(result.eq_matrix(test.GetTransform()), true);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
