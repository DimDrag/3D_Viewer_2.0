#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_MODEL_H_

#include <model/figure.h>
#include <model/renderoptions.h>

#include <string>

namespace s21 {
class Model {
 public:
  Model();
  void ReadSettings();
  void WriteSettings();
  Figure *GetModel3d();
  Figure *GetAxis();
  RenderOptions GetRenderOptions();
  void SetRenderOptions(RenderOptions render_options);
  void ResetRenderOptions();
  Figure::AffineTransformations GetTransformations();
  void SetTransformations(Figure::AffineTransformations transformations);
  void ResetTransformations();
  void Transform();
  void LoadFigure(std::string file_name);

 private:
  Figure model3d_;
  Figure axis_;
  RenderOptions render_options_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_MODEL_MODEL_H_
