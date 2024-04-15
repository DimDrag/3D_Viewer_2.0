#include "mainwindow.h"

#include <QActionGroup>
#include <QColorDialog>
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
#include <cmath>

#include "ui_mainwindow.h"

namespace s21 {
/// @brief Parametrised constructor. Sets some of the UI components, connects
/// QT's SLOTS and SIGNALS
/// @param parent
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);

  // Initialize ui fields
  model_view_ = ui_->modelView;
  axis_view_ = ui_->axisView;

  // Set edges menu
  edges_color_dialog_ = new QColorDialog();
  edges_color_dialog_->setOption(QColorDialog::NoButtons, true);
  edges_color_dialog_->setOption(QColorDialog::DontUseNativeDialog, true);
  QGridLayout *edges_color_dialog_layout = new QGridLayout();
  edges_color_dialog_layout->addWidget(edges_color_dialog_);
  ui_->edgesColor->setLayout(edges_color_dialog_layout);
  QSlider *edges_thickness_slider = new QSlider(Qt::Horizontal);
  edges_thickness_slider->setMinimum(0);
  edges_thickness_slider->setMaximum(10);
  edges_thickness_slider->setSizePolicy(QSizePolicy::Minimum,
                                        QSizePolicy::Minimum);
  edges_thickness_slider->setPageStep(1);
  QGridLayout *edges_thickness_slider_layout = new QGridLayout();
  edges_thickness_slider_layout->addWidget(edges_thickness_slider);
  ui_->edgesThickness->setLayout(edges_thickness_slider_layout);
  v_info_ = new QLabel;
  l_info_ = new QLabel;
  ui_->statusBar->addWidget(v_info_);
  ui_->statusBar->addWidget(l_info_);

  // Set vertices menu
  QColorDialog *vertices_color_dialog = new QColorDialog();
  vertices_color_dialog->setOption(QColorDialog::NoButtons, true);
  vertices_color_dialog->setOption(QColorDialog::DontUseNativeDialog, true);
  QGridLayout *vertices_color_dialog_layout = new QGridLayout();
  vertices_color_dialog_layout->addWidget(vertices_color_dialog);
  ui_->verticesColor->setLayout(vertices_color_dialog_layout);
  QSlider *vertices_thickness_slider = new QSlider(Qt::Horizontal);
  vertices_thickness_slider->setMinimum(0);
  vertices_thickness_slider->setMaximum(10);
  vertices_thickness_slider->setSizePolicy(QSizePolicy::Minimum,
                                           QSizePolicy::Minimum);
  vertices_thickness_slider->setPageStep(1);
  QGridLayout *vertices_thickness_slider_layout = new QGridLayout();
  vertices_thickness_slider_layout->addWidget(vertices_thickness_slider);
  ui_->verticesThickness->setLayout(vertices_thickness_slider_layout);

  // Set background menu
  QColorDialog *background_color_dialog = new QColorDialog();
  background_color_dialog->setOption(QColorDialog::NoButtons, true);
  background_color_dialog->setOption(QColorDialog::DontUseNativeDialog, true);
  QGridLayout *background_color_dialog_layout = new QGridLayout();
  background_color_dialog_layout->addWidget(background_color_dialog);
  ui_->backgroundColor->setLayout(background_color_dialog_layout);

  // Set reset menu option
  ui_->menuBar->addAction(ui_->actionReset);

  mouse_pressed_pos_ = QPoint(0, 0);
  mouse_moved_pos_ = QPoint(0, 0);

  model_view_->installEventFilter(this);

  axis_view_->SetFigure(controller_.GetAxis());
  model_view_->SetFigure(controller_.GetModel3d());
  axis_view_->SetRenderOptions(controller_.GetRenderOptions());
  controller_.ReadSettings();
  model_view_->SetRenderOptions(controller_.GetRenderOptions());

  // Connect slots & signals
  connect(ui_->sliderMoveX, &QSlider::valueChanged, this,
          &MainWindow::MoveModel);
  connect(ui_->sliderMoveY, &QSlider::valueChanged, this,
          &MainWindow::MoveModel);
  connect(ui_->sliderMoveZ, &QSlider::valueChanged, this,
          &MainWindow::MoveModel);
  connect(ui_->spinBoxMoveX, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::MoveModel);
  connect(ui_->spinBoxMoveY, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::MoveModel);
  connect(ui_->spinBoxMoveZ, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::MoveModel);

  connect(ui_->sliderRotateX, &QSlider::valueChanged, this,
          &MainWindow::RotateModel);
  connect(ui_->sliderRotateY, &QSlider::valueChanged, this,
          &MainWindow::RotateModel);
  connect(ui_->sliderRotateZ, &QSlider::valueChanged, this,
          &MainWindow::RotateModel);
  connect(ui_->spinBoxRotateX, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::RotateModel);
  connect(ui_->spinBoxRotateY, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::RotateModel);
  connect(ui_->spinBoxRotateZ, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::RotateModel);

  connect(ui_->sliderScale, &QSlider::valueChanged, this,
          &MainWindow::ScaleModel);
  connect(ui_->spinBoxScale, qOverload<int>(&QSpinBox::valueChanged), this,
          &MainWindow::ScaleModel);

  connect(ui_->buttonResetAffine, &QPushButton::clicked, this,
          &MainWindow::ResetTransformations);

  connect(ui_->actionOpen_file, &QAction::triggered, this,
          &MainWindow::OpenFile);
  connect(ui_->actionTake_a_screenshot, &QAction::triggered, this,
          &MainWindow::TakeScreenshot);
  connect(ui_->actionMake_a_GIF, &QAction::triggered, this,
          &MainWindow::MakeGif);
  connect(edges_color_dialog_, &QColorDialog::currentColorChanged, this,
          &MainWindow::ChangeEdgesColor);
  connect(vertices_color_dialog, &QColorDialog::currentColorChanged, this,
          &MainWindow::ChangeVerticesColor);
  connect(edges_thickness_slider, &QSlider::valueChanged, this,
          &MainWindow::ChangeEdgesThickness);
  connect(vertices_thickness_slider, &QSlider::valueChanged, this,
          &MainWindow::ChangeVerticesThickness);

  connect(ui_->actionSolid, &QAction::triggered, this,
          &MainWindow::ChangeEdgesType);
  connect(ui_->actionDashed, &QAction::triggered, this,
          &MainWindow::ChangeEdgesType);

  connect(ui_->actionNone, &QAction::triggered, this,
          &MainWindow::ChangeVerticesType);
  connect(ui_->actionSquare, &QAction::triggered, this,
          &MainWindow::ChangeVerticesType);
  connect(ui_->actionCircle, &QAction::triggered, this,
          &MainWindow::ChangeVerticesType);

  connect(ui_->actionReset, &QAction::triggered, this,
          &MainWindow::ResetRenderOptions);

  connect(ui_->actionCentral, &QAction::triggered, this,
          &MainWindow::ChangeProjectionMode);
  connect(ui_->actionParallel, &QAction::triggered, this,
          &MainWindow::ChangeProjectionMode);

  connect(background_color_dialog, &QColorDialog::currentColorChanged, this,
          &MainWindow::ChangeBackgroundColor);
}

/// @brief Destructor (frees allocated memory)
MainWindow::~MainWindow() {
  controller_.WriteSettings();
  delete ui_;
}

/// @brief Signals the Controller to move the model if user triggers
/// corresponding ui components
/// @param value Model offset value
void MainWindow::MoveModel(int value) {
  Figure::AffineTransformations transformations =
      controller_.GetTransformations();
  if (sender() == ui_->sliderMoveX || sender() == ui_->spinBoxMoveX) {
    transformations.offset_x = -value / 100.0;
    ui_->sliderMoveX->setValue(value);
    ui_->spinBoxMoveX->setValue(value);
  } else if (sender() == ui_->sliderMoveY || sender() == ui_->spinBoxMoveY) {
    transformations.offset_y = -value / 100.0;
    ui_->sliderMoveY->setValue(value);
    ui_->spinBoxMoveY->setValue(value);
  } else if (sender() == ui_->sliderMoveZ || sender() == ui_->spinBoxMoveZ) {
    transformations.offset_z = -value / 100.0;
    ui_->sliderMoveZ->setValue(value);
    ui_->spinBoxMoveZ->setValue(value);
  }
  controller_.SetTransformations(transformations);
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to rotate the model if user triggers
/// corresponding ui components
/// @param value Model rotation value
void MainWindow::RotateModel(int value) {
  value -= 360 * (value > 180);
  value += 360 * (value < -180);

  Figure::AffineTransformations transformations =
      controller_.GetTransformations();
  if (sender() == ui_->sliderRotateX || sender() == ui_->spinBoxRotateX) {
    transformations.angle_x = value;
  } else if (sender() == ui_->sliderRotateY ||
             sender() == ui_->spinBoxRotateY) {
    transformations.angle_y = value;
  } else if (sender() == ui_->sliderRotateZ ||
             sender() == ui_->spinBoxRotateZ) {
    transformations.angle_z = value;
  }
  ui_->sliderRotateX->setValue(transformations.angle_x);
  ui_->spinBoxRotateX->setValue(transformations.angle_x);
  ui_->sliderRotateY->setValue(transformations.angle_y);
  ui_->spinBoxRotateY->setValue(transformations.angle_y);
  ui_->sliderRotateZ->setValue(transformations.angle_z);
  ui_->spinBoxRotateZ->setValue(transformations.angle_z);

  controller_.SetTransformations(transformations);
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to scale the model if user triggers
/// corresponding ui components
/// @param value Scale factor
void MainWindow::ScaleModel(int value) {
  Figure::AffineTransformations transformations =
      controller_.GetTransformations();
  transformations.scale_factor = 1 + value / 101.0;
  controller_.SetTransformations(transformations);
  ui_->sliderScale->setValue(value);
  ui_->spinBoxScale->setValue(value);
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to update both model and axis
void MainWindow::UpdateModelAndAxis() {
  controller_.Transform();
  model_view_->update();
  axis_view_->update();
}

/// @brief Method for the rotation and scaling model by mouse
/// @param watched Object to apply method
/// @param event Event (e.g. mouse moved, button pressed)
/// @return The return value indicates whether an event was dealt with;
/// a true value prevents the event from being sent on to other objects.
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
    mouse_pressed_pos_ = mouse_event->pos();
  } else if (event->type() == QEvent::MouseMove) {
    if (!mouse_pressed_pos_.isNull()) {
      QMouseEvent *mouse_event = static_cast<QMouseEvent *>(event);
      mouse_moved_pos_ = mouse_event->pos();
      emit ui_->sliderRotateX->valueChanged(
          ui_->sliderRotateX->value() +
          (1 / M_PI * (mouse_moved_pos_.y() - mouse_pressed_pos_.y()) * 1.8));
      emit ui_->sliderRotateY->valueChanged(
          ui_->sliderRotateY->value() +
          (1 / M_PI * (mouse_moved_pos_.x() - mouse_pressed_pos_.x()) * 1.8));
      mouse_pressed_pos_ = mouse_moved_pos_;
    }
  } else if (event->type() == QEvent::MouseButtonRelease) {
    mouse_pressed_pos_.setX(0);
    mouse_pressed_pos_.setY(0);
  } else if (event->type() == QEvent::Wheel) {
    QWheelEvent *wheel_event = static_cast<QWheelEvent *>(event);
    emit ui_->sliderScale->valueChanged(ui_->sliderScale->value() +
                                        (wheel_event->angleDelta().y()) / 30);
  }
  return QMainWindow::eventFilter(watched, event);
}

/// @brief Sets brief info about the 3D-model (number of vertices and edges)
void MainWindow::SetInfo() {
  setWindowTitle(file_name_);
  QString vertices_info =
      "Number of vertices: " +
      QString::number(controller_.GetModel3d()->GetViewVertices()->size());
  QString links_info =
      "Number of links: " +
      QString::number(controller_.GetModel3d()->GetIndices()->size() / 4);
  v_info_->setText(vertices_info);
  l_info_->setText(links_info);
}

/// @brief Starts timer for making a GIF
void MainWindow::StartTimerGif() {
  gif_ = new QGifImage(QSize(640, 480));
  timer_gif_ = new QTimer(this);
  connect(timer_gif_, &QTimer::timeout, this, &MainWindow::RecordGif);
  timer_gif_->start(100);
  frame_ = 0;
}

/// @brief Records a GIF of model view
void MainWindow::RecordGif() {
  const QRect rect(0, 100, 640, 480);
  QPixmap pixmap = model_view_->grab(rect);
  QImage my_image = pixmap.toImage();
  frame_++;
  gif_->addFrame(my_image, 100);
  if (frame_ >= 50) {
    timer_gif_->stop();
    gif_->save(ptr_save_gif_);
    ptr_save_gif_->close();
    delete ptr_save_gif_;
    ptr_save_gif_ = nullptr;
    delete gif_;
    gif_ = nullptr;
    QMessageBox::about(this, "Status", "GIF saved");
  }
}

/// @brief Makes a screenshot of model view
void MainWindow::TakeScreenshot() {
  QImage img = model_view_->grabFramebuffer();
  QString screenshot = QFileDialog::getSaveFileName(
      this, tr("Save File"), QDir::homePath(), tr("Images (*.jpeg *.bmp)"));
  if (!screenshot.isNull()) {
    img.save(screenshot);
  }
}

/// @brief Opens the dialog window for saving the GIF
void MainWindow::MakeGif() {
  QString filter = "*.gif";
  gif_file_name_ = "/0";
  gif_file_name_ =
      QFileDialog::getSaveFileName(this, "Save GIF", QDir::homePath(), filter);

  ptr_save_gif_ = new QFile(gif_file_name_);
  if (!ptr_save_gif_->open(QIODevice::WriteOnly)) {
    QMessageBox::critical(this, "Warning", "Failed to write file");
  } else {
    StartTimerGif();
  }
}

/// @brief Signals the Controller to change projection mode if user triggers
/// corresponding ui components
void MainWindow::ChangeProjectionMode() {
  RenderOptions render_options = controller_.GetRenderOptions();
  if (sender() == ui_->actionCentral) {
    render_options.projection_mode = RenderOptions::ProjectionMode::kCentral;
  } else {
    render_options.projection_mode = RenderOptions::ProjectionMode::kParallel;
  }
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change edges color if user triggers
/// corresponding ui components
/// @param edges_color New edges color
void MainWindow::ChangeEdgesColor(QColor edges_color) {
  RenderOptions render_options = controller_.GetRenderOptions();
  render_options.edges.color = {static_cast<float>(edges_color.redF()),
                                static_cast<float>(edges_color.greenF()),
                                static_cast<float>(edges_color.blueF())};
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change vertices color if user triggers
/// corresponding ui components
/// @param vertices_color New vertices color
void MainWindow::ChangeVerticesColor(QColor vertices_color) {
  RenderOptions render_options = controller_.GetRenderOptions();
  render_options.vertices.color = {static_cast<float>(vertices_color.redF()),
                                   static_cast<float>(vertices_color.greenF()),
                                   static_cast<float>(vertices_color.blueF())};
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change edges thickness if user triggers
/// corresponding ui components
/// @param value Thickness value
void MainWindow::ChangeEdgesThickness(int value) {
  RenderOptions render_options = controller_.GetRenderOptions();
  render_options.edges.thickness = value;
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change vertices thickness if user triggers
/// corresponding ui components
/// @param value Thickness value
void MainWindow::ChangeVerticesThickness(int value) {
  RenderOptions render_options = controller_.GetRenderOptions();
  render_options.vertices.thickness = value;
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change edges type if user triggers
/// corresponding ui components
void MainWindow::ChangeEdgesType() {
  RenderOptions render_options = controller_.GetRenderOptions();
  if (sender() == ui_->actionSolid) {
    render_options.edges.type = RenderOptions::Edges::kSolid;
  } else if (sender() == ui_->actionDashed) {
    render_options.edges.type = RenderOptions::Edges::kDashed;
  }
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change vertices type if user triggers
/// corresponding ui components
void MainWindow::ChangeVerticesType() {
  RenderOptions render_options = controller_.GetRenderOptions();
  if (sender() == ui_->actionNone) {
    render_options.vertices.type = RenderOptions::Vertices::kNone;
  } else if (sender() == ui_->actionSquare) {
    render_options.vertices.type = RenderOptions::Vertices::kSquare;
  } else if (sender() == ui_->actionCircle) {
    render_options.vertices.type = RenderOptions::Vertices::kCircle;
  }
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to change background color if user triggers
/// corresponding ui components
/// @param background_color New background color
void MainWindow::ChangeBackgroundColor(QColor background_color) {
  RenderOptions render_options = controller_.GetRenderOptions();
  render_options.background_color = {
      static_cast<float>(background_color.redF()),
      static_cast<float>(background_color.greenF()),
      static_cast<float>(background_color.blueF())};
  controller_.SetRenderOptions(render_options);
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to reset affine transformations if user
/// triggers corresponding ui components
void MainWindow::ResetTransformations() {
  controller_.ResetTransformations();
  ui_->sliderRotateX->setValue(0);
  ui_->sliderRotateY->setValue(0);
  ui_->sliderRotateZ->setValue(0);
  ui_->sliderMoveX->setValue(0);
  ui_->sliderMoveY->setValue(0);
  ui_->sliderMoveZ->setValue(0);
  ui_->sliderScale->setValue(0);
  UpdateModelAndAxis();
}

/// @brief Signals the Controller to reset render options if user triggers
/// corresponding ui components
void MainWindow::ResetRenderOptions() {
  controller_.ResetRenderOptions();
  model_view_->SetRenderOptions(controller_.GetRenderOptions());
  UpdateModelAndAxis();
}

/// @brief Opens the dialog window to open the .obj file
void MainWindow::OpenFile() {
  setlocale(LC_NUMERIC, "C");
  QString filter = "Obj files (*.obj*)";
  QString file_name = QFileDialog::getOpenFileName(
      this, "Chose a file:", QDir::currentPath(), filter);
  QFileInfo f(file_name);
  if (file_name.isEmpty()) {
    qDebug() << "No file chosen";
  } else {
    controller_.LoadFigure(f.absoluteFilePath().toStdString());
    SetInfo();
    UpdateModelAndAxis();
  }
}
}  // namespace s21
