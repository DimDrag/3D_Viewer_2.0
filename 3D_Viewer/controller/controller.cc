#include "controller.h"

namespace s21 {
/// @brief Parametrised constructor
/// @param parent
Controller::Controller(QObject *parent) : QObject{parent} {}

/// @brief Make Model read settings from the settings file
void Controller::ReadSettings() { model_.ReadSettings(); }

/// @brief Make Model write settings to ther settings file
void Controller::WriteSettings() { model_.WriteSettings(); }

/// @brief Make Model return current transfromation parameters
/// @return Current transfromations applied to model
Figure::AffineTransformations Controller::GetTransformations() {
  return model_.GetTransformations();
}

/// @brief Make Model set transfromation parameters
/// @param transformations Affine transfromations to be applied to model
void Controller::SetTransformations(
    Figure::AffineTransformations transformations) {
  model_.SetTransformations(transformations);
}

/// @brief Make Model reset affinne transformations to default
void Controller::ResetTransformations() { model_.ResetTransformations(); }

/// @brief Make Model apply affinne transformation to Figures
void Controller::Transform() { model_.Transform(); }

/// @brief Make Model load figure from file located at file_name
/// @param file_name Relative or absolute path to the file
void Controller::LoadFigure(std::string file_name) {
  model_.LoadFigure(file_name);
}

/// @brief Make Model return 3D-model
/// @return 3D-model
Figure *Controller::GetModel3d() { return model_.GetModel3d(); }

/// @brief Make Model return axis
/// @return Axis
Figure *Controller::GetAxis() { return model_.GetAxis(); }

/// @brief Make Model return render options e.g. edges thickness, vertices color
/// @return Render options struct
RenderOptions Controller::GetRenderOptions() {
  return model_.GetRenderOptions();
}

/// @brief Make Model set render options e.g. edges thickness, vertices color
/// @param render_options Render options to be set
void Controller::SetRenderOptions(RenderOptions render_options) {
  model_.SetRenderOptions(render_options);
}

/// @brief Make Model reset render options to default
void Controller::ResetRenderOptions() { model_.ResetRenderOptions(); }
}  // namespace s21
