#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_VIEW_FIGURERENDERER_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_VIEW_FIGURERENDERER_H_

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QOpenGLWidget>

#include "model/figure.h"
#include "model/renderoptions.h"

namespace s21 {
class FigureRenderer : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit FigureRenderer(QWidget *parent = nullptr);
  ~FigureRenderer();
  void SetFigure(Figure *figure);
  void SetRenderOptions(RenderOptions render_opts);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

 private:
  Figure *figure_;
  RenderOptions render_opts_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_VIEW_FIGURERENDERER_H_
