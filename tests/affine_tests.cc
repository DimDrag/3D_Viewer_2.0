#include "tests.h"

const float eps = 1e-6;

TEST(Affine, Translate) {
  std::string file_name = "./tests/cube.obj1";
  s21::Parser *parser = s21::Parser::GetInstance(file_name);
  std::vector<s21::Vertex> vertices(parser->data.vertices.size() / 3);
  for (size_t i = 0; i < parser->data.vertices.size() / 3; i++) {
    vertices[i].x = parser->data.vertices[i * 3];
    vertices[i].y = parser->data.vertices[i * 3 + 1];
    vertices[i].z = parser->data.vertices[i * 3 + 2];
  }
  std::vector<uint32_t> indices = parser->data.indices;
  parser->FreeInstance();

  s21::Figure f;
  f.Translate(vertices, -1, +2, -1.5);
  std::vector<s21::Vertex> correct_vertices = {
      {-0.5, +1.5, -2}, {-0.5, +1.5, -1}, {-1.5, +1.5, -1}, {-1.5, +1.5, -2},
      {-0.5, +2.5, -2}, {-0.5, +2.5, -1}, {-1.5, +2.5, -1}, {-1.5, +2.5, -2}};

  for (size_t i = 0; i < correct_vertices.size(); i++) {
    EXPECT_NEAR(vertices[i].x, correct_vertices[i].x, eps);
    EXPECT_NEAR(vertices[i].y, correct_vertices[i].y, eps);
    EXPECT_NEAR(vertices[i].z, correct_vertices[i].z, eps);
  }
}
TEST(Affine, Rotate) {
  std::string file_name = "./tests/cube.obj1";
  s21::Parser *parser = s21::Parser::GetInstance(file_name);
  std::vector<s21::Vertex> vertices(parser->data.vertices.size() / 3);
  for (size_t i = 0; i < parser->data.vertices.size() / 3; i++) {
    vertices[i].x = parser->data.vertices[i * 3];
    vertices[i].y = parser->data.vertices[i * 3 + 1];
    vertices[i].z = parser->data.vertices[i * 3 + 2];
  }
  std::vector<uint32_t> indices = parser->data.indices;
  parser->FreeInstance();

  s21::Figure f;
  f.Rotate(vertices, 30, -45, 180);
  std::vector<s21::Vertex> correct_vertices = {
      {-0.836516, +0.183013, +0.108543}, {-0.224144, +0.683013, +0.287903},
      {+0.482963, +0.683013, -0.212097}, {-0.129410, +0.183013, -0.391457},
      {-0.482963, -0.683013, +0.212097}, {+0.129410, -0.183013, +0.391457},
      {+0.836516, -0.183013, -0.108543}, {+0.224144, -0.683013, -0.287903}};

  for (size_t i = 0; i < correct_vertices.size(); i++) {
    EXPECT_NEAR(vertices[i].x, correct_vertices[i].x, eps);
    EXPECT_NEAR(vertices[i].y, correct_vertices[i].y, eps);
    EXPECT_NEAR(vertices[i].z, correct_vertices[i].z, eps);
  }
}
TEST(Affine, Scale) {
  std::string file_name = "./tests/cube.obj1";
  s21::Parser *parser = s21::Parser::GetInstance(file_name);
  std::vector<s21::Vertex> vertices(parser->data.vertices.size() / 3);
  for (size_t i = 0; i < parser->data.vertices.size() / 3; i++) {
    vertices[i].x = parser->data.vertices[i * 3];
    vertices[i].y = parser->data.vertices[i * 3 + 1];
    vertices[i].z = parser->data.vertices[i * 3 + 2];
  }
  std::vector<uint32_t> indices = parser->data.indices;
  parser->FreeInstance();

  s21::Figure f;
  f.Scale(vertices, 2.25);
  std::vector<s21::Vertex> correct_vertices = {
      {+1.125, -1.125, -1.125}, {+1.125, -1.125, +1.125},
      {-1.125, -1.125, +1.125}, {-1.125, -1.125, -1.125},
      {+1.125, +1.125, -1.125}, {+1.125, +1.125, +1.125},
      {-1.125, +1.125, +1.125}, {-1.125, +1.125, -1.125}};

  for (size_t i = 0; i < correct_vertices.size(); i++) {
    EXPECT_NEAR(vertices[i].x, correct_vertices[i].x, eps);
    EXPECT_NEAR(vertices[i].y, correct_vertices[i].y, eps);
    EXPECT_NEAR(vertices[i].z, correct_vertices[i].z, eps);
  }
}