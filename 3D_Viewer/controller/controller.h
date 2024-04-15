#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_CONTROLLER_CONTROLLER_H_

#include <model/figure.h>
#include <model/model.h>

#include <QObject>
#include <string>

namespace s21 {
class Controller : public QObject {
  Q_OBJECT
 public:
  explicit Controller(QObject *parent = nullptr);
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
  Model model_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_CONTROLLER_CONTROLLER_H_
