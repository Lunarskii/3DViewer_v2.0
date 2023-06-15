#include "controller.h"

void Controller::SetFileName(const QString& fileName) {
  model_->SetFileName(fileName.toStdString());
  model_->Parser();

  if (GetError() == 0) {
    emit SolutionReady(&GetVertexIndex(), &GetVertexCoord());
  } else {
    emit ErrorHasOccured();
  }
}

int Controller::GetError() { return model_->GetError(); }

std::vector<int>& Controller::GetVertexIndex() {
  return model_->GetVertexIndex();
}

std::vector<double>& Controller::GetVertexCoord() {
  return model_->GetVertexCoord();
}

void Controller::Transform(int strategyType, double value, int axis) {
  auto tempAxis = static_cast<transformation_t>(axis);
  model_->Transform(strategyType, value, tempAxis);
}