#include "model.h"

#include <fstream>
#include <iostream>
#include <vector>

#include "model/parser.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

namespace s21 {
/// @brief Constructor which creates axis model
Model::Model() {
  std::vector<Vertex> axis_vertices = {
      Vertex{0, 0, 0},    // 0
      Vertex{0.5, 0, 0},  // 1
      Vertex{0, 0, 0},    // 2
      Vertex{0, 0.5, 0},  // 3
      Vertex{0, 0, 0},    // 4
      Vertex{0, 0, 0.5}   // 5
  };
  std::vector<uint32_t> axis_indices = {4, 5, 5, 4, 0, 1, 1, 0, 3, 2,
                                        2, 3, 0, 4, 4, 0, 0, 3, 3, 0};
  std::vector<float> axis_edges_colors = {1, 0, 0, 1, 0, 0, 0, 1, 0,
                                          0, 1, 0, 0, 0, 1, 0, 0, 1};
  axis_.SetVertices(axis_vertices);
  axis_.SetIndices(axis_indices);
  axis_.SetEdgesColors(axis_edges_colors);
}

/// @brief Read settings from the settings file (if exists)
void Model::ReadSettings() {
  char *homedir = getpwuid(getuid())->pw_dir;
  std::string path = strcat(homedir, "/.3d_viewer/settings.dat");
  std::ifstream in(path, std::ios::binary);
  if (in.is_open()) {
    in.read(reinterpret_cast<char *>(&render_options_),
            sizeof(render_options_));
  } else {
    std::cout << "NO" << std::endl;
  }
  in.close();
}

/// @brief Write settings to the settings file
void Model::WriteSettings() {
  char *homedir = getpwuid(getuid())->pw_dir;
  std::string path = strcat(homedir, "/.3d_viewer/settings.dat");
  std::ofstream out(path, std::ios::binary);
  if (out.is_open()) {
    out.write(reinterpret_cast<char *>(&render_options_),
              sizeof(render_options_));
  } else {
    std::cout << "NO" << std::endl;
  }
  out.close();
}

/// @brief Returns 3D-model
/// @return 3D-model
Figure *Model::GetModel3d() { return &model3d_; }

/// @brief Returns axis model
/// @return Axis model
Figure *Model::GetAxis() { return &axis_; }

/// @brief Returns render options e.g. edges thickness, vertices color
/// @return Render options
RenderOptions Model::GetRenderOptions() { return render_options_; }

/// @brief Sets render options e.g. edges thickness, vertices color
/// @param render_options Render options to be set
void Model::SetRenderOptions(RenderOptions render_options) {
  render_options_ = render_options;
  model3d_.SetEdgesColor(render_options.edges.color.r,
                         render_options.edges.color.g,
                         render_options.edges.color.b);
  model3d_.SetVerticesColor(render_options.vertices.color.r,
                            render_options.vertices.color.g,
                            render_options.vertices.color.b);
}

/// @brief Resets render options to it's default
void Model::ResetRenderOptions() {
  render_options_ = RenderOptions();
  model3d_.SetEdgesColor(render_options_.edges.color.r,
                         render_options_.edges.color.g,
                         render_options_.edges.color.b);
  model3d_.SetVerticesColor(render_options_.vertices.color.r,
                            render_options_.vertices.color.g,
                            render_options_.vertices.color.b);
}

/// @brief Returns current transfromation parameters
/// @return Current transfromations applied to model
Figure::AffineTransformations Model::GetTransformations() {
  return model3d_.GetTransformations();
}

/// @brief Set transfromation parameters
/// @param transformations Affine transfromations to be applied to model
void Model::SetTransformations(Figure::AffineTransformations transformations) {
  model3d_.SetTransformations(transformations);
  transformations.offset_x = 0;
  transformations.offset_y = 0;
  transformations.offset_z = 0;
  axis_.SetTransformations(transformations);
}

/// @brief Resets affinne transformations to default
void Model::ResetTransformations() {
  model3d_.ResetTransformations();
  axis_.ResetTransformations();
}

/// @brief Applies affinne transformation to Figures
void Model::Transform() {
  model3d_.Transform();
  axis_.Transform();
}

/// @brief Loads figure from file located at file_name
/// @param file_name Relative or absolute path to the file
void Model::LoadFigure(std::string file_name) {
  Parser *parser = Parser::GetInstance(file_name);
  std::vector<Vertex> vertices(parser->data.vertices.size() / 3);
  for (size_t i = 0; i < parser->data.vertices.size() / 3; i++) {
    vertices[i].x = parser->data.vertices[i * 3];
    vertices[i].y = parser->data.vertices[i * 3 + 1];
    vertices[i].z = parser->data.vertices[i * 3 + 2];
  }
  std::vector<uint32_t> indices = parser->data.indices;
  parser->FreeInstance();

  model3d_.SetVertices(vertices);
  model3d_.SetIndices(indices);
  model3d_.Normalize();
  model3d_.SetEdgesColor(render_options_.edges.color.r,
                         render_options_.edges.color.g,
                         render_options_.edges.color.b);
  model3d_.SetVerticesColor(render_options_.vertices.color.r,
                            render_options_.vertices.color.g,
                            render_options_.vertices.color.b);
}
}  // namespace s21
