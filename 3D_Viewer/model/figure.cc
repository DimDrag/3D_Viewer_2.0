#include "figure.h"

#include <math.h>

#include <cstdint>
#include <thread>
#include <utility>
#include <vector>

namespace s21 {
// Constructors & assertion operators

/// @brief Constructor which initializes transformations_ field
Figure::Figure() {
  transformations_ = {.scale_factor = 1,
                      .offset_x = 0,
                      .offset_y = 0,
                      .offset_z = 0,
                      .angle_x = 0,
                      .angle_y = 0,
                      .angle_z = 0};
}

/// @brief Parametrized constructor which creates new figure with params
/// @param vertices Vertices that make up the model
/// @param indices Edges that make up the model
Figure::Figure(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
    : Figure() {
  origin_vertices_ = vertices;
  view_vertices_ = vertices;
  indices_ = indices;
}

/// @brief Copy constructor
/// @param other Figure to copy data from
Figure::Figure(const Figure &other) noexcept
    : origin_vertices_(other.origin_vertices_),
      view_vertices_(other.origin_vertices_),
      indices_(other.indices_),
      edges_colors_(other.edges_colors_),
      vertices_colors_(other.vertices_colors_),
      transformations_(other.transformations_) {}

/// @brief Move constructor
/// @param other Figure to move data from
Figure::Figure(Figure &&other) noexcept {
  origin_vertices_ = std::move(other.origin_vertices_);
  indices_ = std::move(other.indices_);
  edges_colors_ = std::move(other.edges_colors_);
  vertices_colors_ = std::move(other.vertices_colors_);
  transformations_ = other.transformations_;
}

/// @brief Copy assignment operator
/// @param other Figure to copy data from
/// @return Figure with copied data
Figure &Figure::operator=(const Figure &other) noexcept {
  origin_vertices_ = other.origin_vertices_;
  indices_ = other.indices_;
  edges_colors_ = other.edges_colors_;
  vertices_colors_ = other.vertices_colors_;
  transformations_ = other.transformations_;
  return *this;
}

/// @brief Move assignment operator
/// @param other Figure to move data from
/// @return Figure with moved data
Figure &Figure::operator=(Figure &&other) noexcept {
  origin_vertices_ = std::move(other.origin_vertices_);
  indices_ = std::move(other.indices_);
  edges_colors_ = std::move(other.edges_colors_);
  vertices_colors_ = std::move(other.vertices_colors_);
  transformations_ = other.transformations_;
  return *this;
}

// Accessors & mutators

/// @brief Returns non original vertices (with applied affine transformations)
/// @return Vector of non original vertices
const std::vector<Vertex> *Figure::GetViewVertices() const noexcept {
  return &view_vertices_;
}

/// @brief Returns the vector of edges of the 3d figure
/// @return Vector of edges
const std::vector<uint32_t> *Figure::GetIndices() const noexcept {
  return &indices_;
}

/// @brief Returns the vector of edges colors
/// @return Vector of edges colors
const std::vector<float> *Figure::GetEdgesColors() const noexcept {
  return &edges_colors_;
}

/// @brief Returns the vector of vertices colors
/// @return Vector of vertices colors
const std::vector<float> *Figure::GetVerticesColors() const noexcept {
  return &vertices_colors_;
}

/// @brief Returns affine transformations applied to the figure
/// @return Affine transformations
Figure::AffineTransformations Figure::GetTransformations() const noexcept {
  return transformations_;
}

/// @brief Sets the model's vertex vector
/// @param vertices Vector of vertices to be set
void Figure::SetVertices(std::vector<Vertex> &vertices) noexcept {
  origin_vertices_ = vertices;
  view_vertices_ = vertices;
}

/// @brief Sets the model's edges vector
/// @param indices Vector of edges to be set
void Figure::SetIndices(std::vector<uint32_t> &indices) noexcept {
  indices_ = indices;
}

/// @brief Sets the model's vector of edges colors
/// @param edges_colors Vector of edges colors to be set
void Figure::SetEdgesColors(std::vector<float> &edges_colors) noexcept {
  edges_colors_ = edges_colors;
}

/// @brief Sets the model's vector of edges color by RGB params
/// @param r Red param
/// @param g Green param
/// @param b Blue param
void Figure::SetEdgesColor(float r, float g, float b) noexcept {
  edges_colors_ = std::vector<float>(origin_vertices_.size() * 3);
  for (size_t i = 0; i < origin_vertices_.size() * 3; i += 3) {
    edges_colors_[i] = r;
    edges_colors_[i + 1] = g;
    edges_colors_[i + 2] = b;
  }
}

/// @brief Sets the model's vector of vertices colors
/// @param vertices_colors Vector of vertices colors to be set
void Figure::SetVerticesColors(std::vector<float> &vertices_colors) noexcept {
  vertices_colors_ = vertices_colors;
}

/// @brief Sets the model's vector of vertices color by RGB params
/// @param r Red param
/// @param g Green param
/// @param b Blue param
void Figure::SetVerticesColor(float r, float g, float b) noexcept {
  vertices_colors_ = std::vector<float>(origin_vertices_.size() * 3);
  for (size_t i = 0; i < origin_vertices_.size() * 3; i += 3) {
    vertices_colors_[i] = r;
    vertices_colors_[i + 1] = g;
    vertices_colors_[i + 2] = b;
  }
}

/// @brief Sets affine transformations (rotation, scale, etc)
/// @param transformations Affine transformations to be set
void Figure::SetTransformations(
    AffineTransformations transformations) noexcept {
  transformations_ = transformations;
}

/// @brief Sets affine transformations to it's default
void Figure::ResetTransformations() noexcept {
  transformations_ = {.scale_factor = 1,
                      .offset_x = 0,
                      .offset_y = 0,
                      .offset_z = 0,
                      .angle_x = 0,
                      .angle_y = 0,
                      .angle_z = 0};
}

/// @brief Apply current affine transformations to the model
void Figure::Transform() noexcept {
  view_vertices_ = origin_vertices_;
  if (transformations_.scale_factor != 1) {
    Scale(view_vertices_, transformations_.scale_factor);
  }
  if (transformations_.offset_x != 0 || transformations_.offset_y != 0 ||
      transformations_.offset_z != 0) {
    Translate(view_vertices_, transformations_.offset_x,
              transformations_.offset_y, transformations_.offset_z);
  }
  if (transformations_.angle_x != 0 || transformations_.angle_y != 0 ||
      transformations_.angle_z != 0) {
    Rotate(view_vertices_, transformations_.angle_x, transformations_.angle_y,
           transformations_.angle_z);
  }
}

/// @brief Normalizes model (centers the model, sets the scale value for easy
/// viewing). Warning! Normalize applies to original vertices array
void Figure::Normalize() noexcept {
  float max_cord = 0;
  for (size_t i = 0; i < origin_vertices_.size(); ++i) {
    if (fabs(max_cord) < fabs(origin_vertices_[i].x)) {
      max_cord = origin_vertices_[i].x;
    }
    if (fabs(max_cord) < fabs(origin_vertices_[i].y)) {
      max_cord = origin_vertices_[i].y;
    }
    if (fabs(max_cord) < fabs(origin_vertices_[i].z)) {
      max_cord = origin_vertices_[i].z;
    }
  }
  Scale(origin_vertices_, 1.0 / (max_cord * 1.2));

  float max_x = -1e18;
  float max_y = -1e18;
  float max_z = -1e18;
  float min_x = 1e18;
  float min_y = 1e18;
  float min_z = 1e18;
  for (size_t i = 0; i < origin_vertices_.size(); ++i) {
    max_x = fmax(max_x, origin_vertices_[i].x);
    min_x = fmin(min_x, origin_vertices_[i].x);

    max_y = fmax(max_y, origin_vertices_[i].y);
    min_y = fmin(min_y, origin_vertices_[i].y);

    max_z = fmax(max_z, origin_vertices_[i].z);
    min_z = fmin(min_z, origin_vertices_[i].z);
  }
  float offsetX = -(max_x + min_x) / 2;
  float offsetY = -(max_y + min_y) / 2;
  float offsetZ = -(max_z + min_z) / 2;
  Translate(origin_vertices_, offsetX, offsetY, offsetZ);
}

/// @brief Rotates part of the vertices from the vertices vector
/// @param vertices Vertices vector to rotate vertices from
/// @param start_index Start index of the chunk of vertices to rotate
/// @param end_index End index of the chunk of vertices to rotate
/// @param angle_x Angle X of rotation
/// @param angle_y Angle Y of rotation
/// @param angle_z Angle Z of rotation
void RotateChunk(std::vector<Vertex> &vertices, int start_index, int end_index,
                 float angle_x, float angle_y, float angle_z) noexcept {
  float rad_x = angle_x * (M_PI / 180);
  float cos_x = cos(rad_x);
  float sin_x = sin(rad_x);

  float rad_y = angle_y * (M_PI / 180);
  float cos_y = cos(rad_y);
  float sin_y = sin(rad_y);

  float rad_z = angle_z * (M_PI / 180);
  float cos_z = cos(rad_z);
  float sin_z = sin(rad_z);

  for (int i = 0; i < end_index - start_index; ++i) {
    Vertex res_vertex;

    res_vertex.x = vertices[i + start_index].x;
    res_vertex.y = vertices[i + start_index].y * cos_x -
                   vertices[i + start_index].z * sin_x;
    res_vertex.z = vertices[i + start_index].y * sin_x +
                   vertices[i + start_index].z * cos_x;

    res_vertex.x = res_vertex.x * cos_y + res_vertex.z * sin_y;
    res_vertex.z = res_vertex.x * -sin_y + res_vertex.z * cos_y;

    float prev = res_vertex.x;
    res_vertex.x = res_vertex.x * cos_z - res_vertex.y * sin_z;
    res_vertex.y = prev * sin_z + res_vertex.y * cos_z;

    vertices[i + start_index] = res_vertex;
  }
}

/// @brief Rotates all vertices from the vertices vector
/// @param vertices Vertices vector to rotate vertices from
/// @param angle_x Angle X of rotation
/// @param angle_y Angle Y of rotation
/// @param angle_z Angle Z of rotation
void Figure::Rotate(std::vector<Vertex> &vertices, float angle_x, float angle_y,
                    float angle_z) noexcept {
  const int num_threads = std::thread::hardware_concurrency();
  const int chunk_size = vertices.size() / num_threads;
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; ++i) {
    int start = i * chunk_size;
    int end = (i == num_threads - 1) ? vertices.size() : (i + 1) * chunk_size;
    threads.emplace_back(RotateChunk, std::ref(vertices), start, end, angle_x,
                         angle_y, angle_z);
  }
  for (auto &thread : threads) {
    thread.join();
  }
}

/// @brief Scales part of the vertices from the vertices vector
/// @param vertices Vertices vector to scale vertices from
/// @param start_index Start index of the chunk of vertices to scale
/// @param end_index End index of the chunk of vertices to scale
/// @param scale_factor Scale factor
void ScaleChunk(std::vector<Vertex> &vertices, int start_index, int end_index,
                float scale_factor) noexcept {
  for (int i = 0; i < end_index - start_index; ++i) {
    vertices[i + start_index].x *= scale_factor;
    vertices[i + start_index].y *= scale_factor;
    vertices[i + start_index].z *= scale_factor;
  }
}

/// @brief Scales all vertices from the vertices vector
/// @param vertices Vertices vector to scale vertices from
/// @param scale_factor Scale factor
void Figure::Scale(std::vector<Vertex> &vertices, float scale_factor) noexcept {
  const int num_threads = std::thread::hardware_concurrency();
  const int chunk_size = vertices.size() / num_threads;
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; ++i) {
    int start = i * chunk_size;
    int end = (i == num_threads - 1) ? vertices.size() : (i + 1) * chunk_size;
    threads.emplace_back(ScaleChunk, std::ref(vertices), start, end,
                         scale_factor);
  }
  for (auto &thread : threads) {
    thread.join();
  }
}

/// @brief Moves in space (in X,Y,Z coords) part of the vertices from the
/// vertices vector
/// @param vertices Vertices vector to move vertices from
/// @param start_index Start index of the chunk of vertices to move
/// @param end_index End index of the chunk of vertices to move
/// @param x_mov The x value by which the model must be moves along the OX axis
/// @param y_mov The y value by which the model must be moves along the OY axis
/// @param z_mov The z value by which the model must be moves along the OZ axis
void TranslateChunk(std::vector<Vertex> &vertices, int start_index,
                    int end_index, float x_mov, float y_mov,
                    float z_mov) noexcept {
  for (int i = 0; i < end_index - start_index; ++i) {
    vertices[i + start_index].x += x_mov;
    vertices[i + start_index].y += y_mov;
    vertices[i + start_index].z += z_mov;
  }
}

/// @brief Moves in space (in X,Y,Z coords) all vertices from the vertices
/// vector
/// @param vertices Vertices vector to translate vertices from
/// @param x_mov The x value by which the model must be moves along the OX axis
/// @param y_mov The y value by which the model must be moves along the OY axis
/// @param z_mov The z value by which the model must be moves along the OZ axis
void Figure::Translate(std::vector<Vertex> &vertices, float x_mov, float y_mov,
                       float z_mov) noexcept {
  const int num_threads = std::thread::hardware_concurrency();
  const int chunkSize = vertices.size() / num_threads;
  std::vector<std::thread> threads;
  for (int i = 0; i < num_threads; ++i) {
    int start = i * chunkSize;
    int end = (i == num_threads - 1) ? vertices.size() : (i + 1) * chunkSize;
    threads.emplace_back(TranslateChunk, std::ref(vertices), start, end, x_mov,
                         y_mov, z_mov);
  }
  for (auto &thread : threads) {
    thread.join();
  }
}
}  // namespace s21
