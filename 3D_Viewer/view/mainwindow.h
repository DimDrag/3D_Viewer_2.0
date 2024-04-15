#ifndef CPP4_3DVIEWER_V2_0_1_3D_VIEWER_VIEW_MAINWINDOW_H_
#define CPP4_3DVIEWER_V2_0_1_3D_VIEWER_VIEW_MAINWINDOW_H_

#include <controller/controller.h>
#include <view/figurerenderer.h>

#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPushButton>
#include <QRadioButton>
#include <QSlider>
#include <QSpinBox>
#include <QTimer>

#include "gifLibrary/QtGifImage/3rdParty/giflib/gif_lib.h"
#include "gifLibrary/QtGifImage/gifimage/qgifimage.h"

#define _USE_MATH_DEFINES

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  // Affine
  void MoveModel(int value);
  void RotateModel(int value);
  void ScaleModel(int value);
  void ResetTransformations();
  // Render
  void ChangeProjectionMode();
  void ChangeEdgesColor(QColor edgesColor);
  void ChangeVerticesColor(QColor verticesColor);
  void ChangeEdgesThickness(int value);
  void ChangeVerticesThickness(int value);
  void ChangeEdgesType();
  void ChangeVerticesType();
  void ChangeBackgroundColor(QColor backgroundColor);
  void ResetRenderOptions();
  // Other methods
  void OpenFile();
  void TakeScreenshot();
  void MakeGif();

 private:
  Ui::MainWindow *ui_;
  FigureRenderer *model_view_;
  FigureRenderer *axis_view_;

  QLabel *v_info_;
  QLabel *l_info_;
  QString file_name_;
  QColorDialog *edges_color_dialog_;

  QPoint mouse_pressed_pos_;
  QPoint mouse_moved_pos_;

  QTimer timer_ui_;
  QString gif_file_name_;
  QTimer *timer_gif_;
  int frame_;
  QGifImage *gif_;
  QFile *ptr_save_gif_;

  Controller controller_;

  void UpdateModelAndAxis();
  bool eventFilter(QObject *watched, QEvent *event);
  void SetInfo();
  void StartTimerGif();
  void RecordGif();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_1_3D_VIEWER_VIEW_MAINWINDOW_H_
