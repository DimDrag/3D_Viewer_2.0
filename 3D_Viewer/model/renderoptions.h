#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_RENDEROPTIONS_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_RENDEROPTIONS_H_

namespace s21 {
struct RenderOptions {
 public:
  struct Color {
    float r;
    float g;
    float b;
  };
  enum class ProjectionMode { kParallel, kCentral };
  struct Edges {
    enum EdgesType { kSolid, kDashed } type;
    float thickness;
    Color color;
  };
  struct Vertices {
    enum VerticesType { kNone, kSquare, kCircle } type;
    float thickness;
    Color color;
  };

  ProjectionMode projection_mode = ProjectionMode::kParallel;
  Color background_color = {.r = 0, .g = 0, .b = 0};
  Edges edges = {.type = Edges::kSolid,
                 .thickness = 1,
                 .color = {.r = 255, .g = 255, .b = 255}};
  Vertices vertices = {.type = Vertices::kNone,
                       .thickness = 0,
                       .color = {.r = 255, .g = 255, .b = 255}};
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_RENDEROPTIONS_H_
