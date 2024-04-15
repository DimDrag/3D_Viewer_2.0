#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_FIGURE_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_FIGURE_H_

#include <cstdint>
#include <vector>

namespace s21 {
struct Vertex {
 public:
  float x;
  float y;
  float z;
};

class Figure {
 public:
  struct AffineTransformations {
    float scale_factor;
    float offset_x, offset_y, offset_z;
    float angle_x, angle_y, angle_z;
  };
  // Constructors & assertion operators
  Figure();
  Figure(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
  Figure(const Figure &other) noexcept;
  Figure(Figure &&other) noexcept;
  Figure &operator=(const Figure &other) noexcept;
  Figure &operator=(Figure &&other) noexcept;

  // Accessors & mutators
  const std::vector<Vertex> *GetViewVertices() const noexcept;
  const std::vector<uint32_t> *GetIndices() const noexcept;
  const std::vector<float> *GetEdgesColors() const noexcept;
  const std::vector<float> *GetVerticesColors() const noexcept;
  AffineTransformations GetTransformations() const noexcept;
  void SetVertices(std::vector<Vertex> &vertices) noexcept;
  void SetIndices(std::vector<uint32_t> &indices) noexcept;
  void SetEdgesColors(std::vector<float> &edges_colors) noexcept;
  void SetEdgesColor(float r, float g, float b) noexcept;
  void SetVerticesColors(std::vector<float> &vertices_colors) noexcept;
  void SetVerticesColor(float r, float g, float b) noexcept;
  void SetTransformations(AffineTransformations transformations) noexcept;
  void ResetTransformations() noexcept;

  // Complex transformations
  void Transform() noexcept;
  void Normalize() noexcept;

  // Affine(basic) transformations
  void Rotate(std::vector<Vertex> &vertices, float angle_x, float angle_y,
              float angle_z) noexcept;
  void Scale(std::vector<Vertex> &vertices, float scale_factor) noexcept;
  void Translate(std::vector<Vertex> &vertices, float x_mov, float y_mov,
                 float z_mov) noexcept;

 private:
  std::vector<Vertex> origin_vertices_;
  std::vector<Vertex> view_vertices_;
  std::vector<unsigned int> indices_;
  std::vector<float> edges_colors_;
  std::vector<float> vertices_colors_;
  AffineTransformations transformations_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_FIGURE_H_
