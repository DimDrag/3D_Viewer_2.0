#include "figurerenderer.h"

#include <QOpenGLExtraFunctions>
#include <QOpenGLFunctions>
#include <vector>

#include "model/figure.h"
#include "model/renderoptions.h"

namespace s21 {
/// @brief Parametrised constructor
/// @param parent
FigureRenderer::FigureRenderer(QWidget *parent)
    : QOpenGLWidget(parent), figure_(nullptr) {}

/// @brief Destructor
FigureRenderer::~FigureRenderer() {}

/// @brief Sets the figure to display it
/// @param figure Figure to display
void FigureRenderer::SetFigure(Figure *figure) { figure_ = figure; }

/// @brief Sets render options e.g. edges thickness, vertices color
/// @param render_opts
void FigureRenderer::SetRenderOptions(RenderOptions render_opts) {
  render_opts_ = render_opts;
}

/// @brief Sets up the OpenGL resources and state. Gets called once before the
/// first time resizeGL() or paintGL() is called
void FigureRenderer::initializeGL() { glEnable(GL_DEPTH_TEST); }

/// @brief This virtual function is called whenever the widget has been resized.
/// The new size is passed in width and height.
/// @param w New width
/// @param h New height
void FigureRenderer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

/// @brief Renders the OpenGL scene (draws the model)
void FigureRenderer::paintGL() {
  float *vertices = new float[figure_->GetViewVertices()->size() * 3];
  for (size_t i = 0; i < figure_->GetViewVertices()->size() * 3; i += 3) {
    vertices[i] = figure_->GetViewVertices()->data()[i / 3].x;
    vertices[i + 1] = figure_->GetViewVertices()->data()[i / 3].y;
    vertices[i + 2] = figure_->GetViewVertices()->data()[i / 3].z;
    if (render_opts_.projection_mode ==
        RenderOptions::ProjectionMode::kCentral) {
      vertices[i] *= 2;
      vertices[i + 1] *= 2;
      vertices[i + 2] *= 2;
      vertices[i + 2] -= 2.25;
    }
  }
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (render_opts_.projection_mode == RenderOptions::ProjectionMode::kCentral) {
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 10.0);
  }
  glClearColor(render_opts_.background_color.r, render_opts_.background_color.g,
               render_opts_.background_color.b, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
  glLineWidth(render_opts_.edges.thickness);
  glPointSize(render_opts_.vertices.thickness);

  if (render_opts_.edges.type == RenderOptions::Edges::kDashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xAAAA);
  }
  if (render_opts_.vertices.type == RenderOptions::Vertices::kCircle) {
    glEnable(GL_POINT_SMOOTH);
  }

  // Draw edges
  glVertexPointer(3, GL_FLOAT, 0, vertices);
  glEnableClientState(GL_VERTEX_ARRAY);
  glColorPointer(3, GL_FLOAT, 0, figure_->GetEdgesColors()->data());
  glEnableClientState(GL_COLOR_ARRAY);
  glDrawElements(GL_LINES, figure_->GetIndices()->size(), GL_UNSIGNED_INT,
                 figure_->GetIndices()->data());

  // Draw vertices
  if (render_opts_.vertices.type != RenderOptions::Vertices::kNone) {
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, figure_->GetVerticesColors()->data());
    glEnableClientState(GL_COLOR_ARRAY);
    glDrawElements(GL_POINTS, figure_->GetIndices()->size(), GL_UNSIGNED_INT,
                   figure_->GetIndices()->data());
  }

  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);

  glDisable(GL_LINE_STIPPLE);
  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_BLEND);
  delete[] vertices;
}
}  // namespace s21
