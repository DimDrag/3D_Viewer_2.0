#include "tests.h"

TEST(Parser, Test1) {
  std::string file_name = "./tests/cube.obj1";
  s21::Parser *test = s21::Parser::GetInstance(file_name);
  EXPECT_EQ(test->data.count_of_facets, 12);
  EXPECT_EQ(test->data.count_of_indices, 72);
  EXPECT_EQ(test->data.count_of_vertices, 24);

  std::vector<double> correct_vertices;
  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(-0.500000);

  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(0.500000);

  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(0.500000);

  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(-0.500000);

  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(-0.500000);

  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(0.500000);

  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(0.500000);

  correct_vertices.push_back(-0.500000);
  correct_vertices.push_back(0.500000);
  correct_vertices.push_back(-0.500000);

  for (uint32_t i = 0; i < test->data.count_of_vertices; ++i) {
    EXPECT_FLOAT_EQ(test->data.vertices[i], correct_vertices[i]);
  }

  std::vector<int> correct_indices;
  correct_indices.push_back(1);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(1);

  correct_indices.push_back(7);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(7);

  correct_indices.push_back(4);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(4);

  correct_indices.push_back(5);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(5);

  correct_indices.push_back(2);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(2);

  correct_indices.push_back(0);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(0);

  correct_indices.push_back(0);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(0);

  correct_indices.push_back(4);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(4);

  correct_indices.push_back(0);
  correct_indices.push_back(4);
  correct_indices.push_back(4);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(0);

  correct_indices.push_back(1);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(1);

  correct_indices.push_back(3);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(3);

  correct_indices.push_back(4);
  correct_indices.push_back(0);
  correct_indices.push_back(0);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(4);

  for (uint32_t i = 0; i < test->data.count_of_indices; ++i) {
    EXPECT_EQ(test->data.indices[i], correct_indices[i]);
  }

  test->FreeInstance();
}

TEST(Parser, Test2) {
  std::string file_name = "./tests/cube2.obj1";
  s21::Parser *test = s21::Parser::GetInstance(file_name);
  EXPECT_EQ(test->data.count_of_facets, 12);
  EXPECT_EQ(test->data.count_of_indices, 72);
  EXPECT_EQ(test->data.count_of_vertices, 24);

  std::vector<double> correct_vertices;
  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(-1.000000);

  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(1.000000);

  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(1.000000);

  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(-1.000000);

  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(-0.999999);

  correct_vertices.push_back(0.999999);
  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(1.000001);

  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(1.000000);

  correct_vertices.push_back(-1.000000);
  correct_vertices.push_back(1.000000);
  correct_vertices.push_back(-1.000000);

  for (uint32_t i = 0; i < test->data.count_of_vertices; ++i) {
    EXPECT_FLOAT_EQ(test->data.vertices[i], correct_vertices[i]);
  }

  std::vector<int> correct_indices;
  correct_indices.push_back(1);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(1);

  correct_indices.push_back(7);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(7);

  correct_indices.push_back(4);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(4);

  correct_indices.push_back(5);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(5);

  correct_indices.push_back(2);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(2);

  correct_indices.push_back(0);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(0);

  correct_indices.push_back(0);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(0);

  correct_indices.push_back(4);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(4);

  correct_indices.push_back(0);
  correct_indices.push_back(4);
  correct_indices.push_back(4);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(0);

  correct_indices.push_back(1);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(1);

  correct_indices.push_back(3);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(3);

  correct_indices.push_back(4);
  correct_indices.push_back(0);
  correct_indices.push_back(0);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(4);

  for (uint32_t i = 0; i < test->data.count_of_indices; ++i) {
    EXPECT_EQ(test->data.indices[i], correct_indices[i]);
  }

  test->FreeInstance();
}

TEST(Parser, Test3) {
  std::string file_name = "./tests/dodecahedron.obj1";
  s21::Parser *test = s21::Parser::GetInstance(file_name);
  EXPECT_EQ(test->data.count_of_facets, 36);
  EXPECT_EQ(test->data.count_of_indices, 216);
  EXPECT_EQ(test->data.count_of_vertices, 60);

  std::vector<double> correct_vertices;
  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(0.57735);

  correct_vertices.push_back(0.934172);
  correct_vertices.push_back(0.356822);
  correct_vertices.push_back(0);

  correct_vertices.push_back(0.934172);
  correct_vertices.push_back(-0.356822);
  correct_vertices.push_back(0);

  correct_vertices.push_back(-0.934172);
  correct_vertices.push_back(0.356822);
  correct_vertices.push_back(0);

  correct_vertices.push_back(-0.934172);
  correct_vertices.push_back(-0.356822);
  correct_vertices.push_back(0);

  correct_vertices.push_back(0);
  correct_vertices.push_back(0.934172);
  correct_vertices.push_back(0.356822);

  correct_vertices.push_back(0);
  correct_vertices.push_back(0.934172);
  correct_vertices.push_back(-0.356822);

  correct_vertices.push_back(0.356822);
  correct_vertices.push_back(0);
  correct_vertices.push_back(-0.934172);

  correct_vertices.push_back(-0.356822);
  correct_vertices.push_back(0);
  correct_vertices.push_back(-0.934172);

  correct_vertices.push_back(0);
  correct_vertices.push_back(-0.934172);
  correct_vertices.push_back(-0.356822);

  correct_vertices.push_back(0);
  correct_vertices.push_back(-0.934172);
  correct_vertices.push_back(0.356822);

  correct_vertices.push_back(0.356822);
  correct_vertices.push_back(0);
  correct_vertices.push_back(0.934172);

  correct_vertices.push_back(-0.356822);
  correct_vertices.push_back(0);
  correct_vertices.push_back(0.934172);

  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(-0.57735);

  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(0.57735);

  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(-0.57735);

  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(0.57735);

  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(-0.57735);

  correct_vertices.push_back(0.57735);
  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(0.57735);

  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(-0.57735);
  correct_vertices.push_back(-0.57735);

  for (uint32_t i = 0; i < test->data.count_of_vertices; ++i) {
    EXPECT_FLOAT_EQ(test->data.vertices[i], correct_vertices[i]);
  }

  std::vector<int> correct_indices;
  correct_indices.push_back(18);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(18);

  correct_indices.push_back(11);
  correct_indices.push_back(18);
  correct_indices.push_back(18);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(11);

  correct_indices.push_back(14);
  correct_indices.push_back(11);
  correct_indices.push_back(11);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(14);

  correct_indices.push_back(7);
  correct_indices.push_back(13);
  correct_indices.push_back(13);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(7);

  correct_indices.push_back(17);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(17);

  correct_indices.push_back(2);
  correct_indices.push_back(17);
  correct_indices.push_back(17);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(2);

  correct_indices.push_back(19);
  correct_indices.push_back(4);
  correct_indices.push_back(4);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(19);

  correct_indices.push_back(8);
  correct_indices.push_back(19);
  correct_indices.push_back(19);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(8);

  correct_indices.push_back(15);
  correct_indices.push_back(8);
  correct_indices.push_back(8);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(15);

  correct_indices.push_back(12);
  correct_indices.push_back(16);
  correct_indices.push_back(16);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(12);

  correct_indices.push_back(0);
  correct_indices.push_back(12);
  correct_indices.push_back(12);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(0);

  correct_indices.push_back(4);
  correct_indices.push_back(0);
  correct_indices.push_back(0);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(4);

  correct_indices.push_back(6);
  correct_indices.push_back(15);
  correct_indices.push_back(15);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(6);

  correct_indices.push_back(5);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(5);

  correct_indices.push_back(16);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(3);
  correct_indices.push_back(3);
  correct_indices.push_back(16);

  correct_indices.push_back(5);
  correct_indices.push_back(14);
  correct_indices.push_back(14);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(5);

  correct_indices.push_back(6);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(6);

  correct_indices.push_back(13);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(1);
  correct_indices.push_back(1);
  correct_indices.push_back(13);

  correct_indices.push_back(9);
  correct_indices.push_back(17);
  correct_indices.push_back(17);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(9);

  correct_indices.push_back(10);
  correct_indices.push_back(9);
  correct_indices.push_back(9);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(10);

  correct_indices.push_back(18);
  correct_indices.push_back(10);
  correct_indices.push_back(10);
  correct_indices.push_back(2);
  correct_indices.push_back(2);
  correct_indices.push_back(18);

  correct_indices.push_back(10);
  correct_indices.push_back(0);
  correct_indices.push_back(0);
  correct_indices.push_back(4);
  correct_indices.push_back(4);
  correct_indices.push_back(10);

  correct_indices.push_back(9);
  correct_indices.push_back(10);
  correct_indices.push_back(10);
  correct_indices.push_back(4);
  correct_indices.push_back(4);
  correct_indices.push_back(9);

  correct_indices.push_back(19);
  correct_indices.push_back(9);
  correct_indices.push_back(9);
  correct_indices.push_back(4);
  correct_indices.push_back(4);
  correct_indices.push_back(19);

  correct_indices.push_back(19);
  correct_indices.push_back(8);
  correct_indices.push_back(8);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(19);

  correct_indices.push_back(9);
  correct_indices.push_back(19);
  correct_indices.push_back(19);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(9);

  correct_indices.push_back(17);
  correct_indices.push_back(9);
  correct_indices.push_back(9);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(17);

  correct_indices.push_back(8);
  correct_indices.push_back(15);
  correct_indices.push_back(15);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(8);

  correct_indices.push_back(7);
  correct_indices.push_back(8);
  correct_indices.push_back(8);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(7);

  correct_indices.push_back(13);
  correct_indices.push_back(7);
  correct_indices.push_back(7);
  correct_indices.push_back(6);
  correct_indices.push_back(6);
  correct_indices.push_back(13);

  correct_indices.push_back(11);
  correct_indices.push_back(14);
  correct_indices.push_back(14);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(11);

  correct_indices.push_back(12);
  correct_indices.push_back(11);
  correct_indices.push_back(11);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(12);

  correct_indices.push_back(16);
  correct_indices.push_back(12);
  correct_indices.push_back(12);
  correct_indices.push_back(5);
  correct_indices.push_back(5);
  correct_indices.push_back(16);

  correct_indices.push_back(12);
  correct_indices.push_back(0);
  correct_indices.push_back(0);
  correct_indices.push_back(10);
  correct_indices.push_back(10);
  correct_indices.push_back(12);

  correct_indices.push_back(11);
  correct_indices.push_back(12);
  correct_indices.push_back(12);
  correct_indices.push_back(10);
  correct_indices.push_back(10);
  correct_indices.push_back(11);

  correct_indices.push_back(18);
  correct_indices.push_back(11);
  correct_indices.push_back(11);
  correct_indices.push_back(10);
  correct_indices.push_back(10);
  correct_indices.push_back(18);

  for (uint32_t i = 0; i < test->data.count_of_indices; ++i) {
    EXPECT_EQ(test->data.indices[i], correct_indices[i]);
  }

  test->FreeInstance();
}

TEST(Parser, Test4) {
  std::string file_name = "./tests/cube.obj2";
  EXPECT_ANY_THROW(s21::Parser::GetInstance(file_name));
}
