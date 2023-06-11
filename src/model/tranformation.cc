#include "tranformation.h"

void MoveStrategy::Transform(std::vector<double> &vertexCoord, double &step,
                             transformation_t &axis) {
  for (int i = axis; i < vertexCoord.size(); i += 3) {
    vertexCoord[i] += step;
  }
}

void RotateStrategy::Transform(std::vector<double> &vertexCoord, double &angle,
                               transformation_t &axis) {
  double tempAngle = angle * M_PI / 180;
  double cosValue = cos(tempAngle);
  double sinValue = sin(tempAngle);

  for (int i = (axis == kX) ? 1 : 0; i < vertexCoord.size(); i += 3) {
    double coord = vertexCoord[i];

    if (axis == kX) {
      vertexCoord[i] = cosValue * coord - sinValue * vertexCoord[i + 1];
      vertexCoord[i + 1] = sinValue * coord + cosValue * vertexCoord[i + 1];
    } else if (axis == kY) {
      vertexCoord[i] = cosValue * coord + sinValue * vertexCoord[i + 2];
      vertexCoord[i + 2] = -sinValue * coord + cosValue * vertexCoord[i + 2];
    } else if (axis == kZ) {
      vertexCoord[i] = cosValue * coord + sinValue * vertexCoord[i + 1];
      vertexCoord[i + 1] = -sinValue * coord + cosValue * vertexCoord[i + 1];
    }
  }
}

void ScaleStrategy::Transform(std::vector<double> &vertexCoord, double &scale,
                              transformation_t &) {
  for (double &i : vertexCoord) {
    i *= scale;
  }
}

Strategy::Strategy() : strategy_(nullptr) {}

void Strategy::setStrategy(TransformationStrategy *strategy) {
  strategy_ = strategy;
}

void Strategy::performTransformation(std::vector<double> &vertexCoord,
                                     double &value, transformation_t &axis) {
  strategy_->Transform(vertexCoord, value, axis);
  delete strategy_;
}