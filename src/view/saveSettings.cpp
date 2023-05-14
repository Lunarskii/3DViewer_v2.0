#include "./ui_viewer.h"
#include "view.h"

void View::saveSettings() {
  // saving color settings
  lastSettings->setValue(BACKGROUND_COLOR, backgroundColor.name());
  lastSettings->setValue(EDGE_COLOR, edgeColor.name());
  lastSettings->setValue(VERTEX_COLOR, vertexColor.name());

  // saving step settings
  lastSettings->setValue(STEP, ui->step->value());
  lastSettings->setValue(ANGLE, ui->angle->value());
  lastSettings->setValue(SCALE, ui->scale->value());

  // saving projection settings
  if (ui->radioButton_parallel_type->isChecked())
    lastSettings->setValue(PROJECTION_TYPE, PARALLEL);
  if (ui->radioButton_central_type->isChecked())
    lastSettings->setValue(PROJECTION_TYPE, CENTRAL);

  // saving edge settings
  lastSettings->setValue(EDGE_THICKNESS, ui->edgeThickness->value());
  if (ui->radioButton_edgeType_solid->isChecked())
    lastSettings->setValue(EDGE_TYPE, SOLID);
  if (ui->radioButton_edgeType_dashed->isChecked())
    lastSettings->setValue(EDGE_TYPE, DASHED);

  // saving vertex settings
  lastSettings->setValue(VERTEX_SIZE, ui->vertexSize->value());
  if (ui->radioButton_vertexType_circle->isChecked())
    lastSettings->setValue(VERTEX_TYPE, CIRCLE);
  if (ui->radioButton_vertexType_square->isChecked())
    lastSettings->setValue(VERTEX_TYPE, SQUARE);
  if (ui->radioButton_vertexType_novertex->isChecked())
    lastSettings->setValue(VERTEX_TYPE, NOVERTEX);
}

void View::restoreSettings() {
  QString tempBackgroundColor =
      lastSettings->value(BACKGROUND_COLOR, -1).toString();
  QString tempEdgeColor = lastSettings->value(EDGE_COLOR, -1).toString();
  QString tempVertexColor = lastSettings->value(VERTEX_COLOR, -1).toString();
  int tempEdgeThickness = lastSettings->value(EDGE_THICKNESS, -1).toInt();
  int tempVertexSize = lastSettings->value(VERTEX_SIZE, -1).toInt();

  // restoring color settings
  if (tempBackgroundColor != "-1")
    backgroundColor.setNamedColor(tempBackgroundColor);
  if (tempEdgeColor != "-1") edgeColor.setNamedColor(tempEdgeColor);
  if (tempVertexColor != "-1") vertexColor.setNamedColor(tempVertexColor);

  // restoring step settings
  if (double tempStep = lastSettings->value(STEP, -1).toDouble();
      tempStep != -1)
    ui->step->setValue(tempStep);
  if (int tempAngle = lastSettings->value(ANGLE, -1).toInt(); tempAngle != -1)
    ui->angle->setValue(tempAngle);
  if (int tempScale = lastSettings->value(SCALE, -1).toInt(); tempScale != -1)
    ui->scale->setValue(tempScale);

  // restoring projection settings
  if (lastSettings->value(PROJECTION_TYPE).toInt() == PARALLEL)
    ui->radioButton_parallel_type->setChecked(true);
  if (lastSettings->value(PROJECTION_TYPE).toInt() == CENTRAL)
    ui->radioButton_central_type->setChecked(true);

  // restoring edge settings
  if (tempEdgeThickness != -1) ui->edgeThickness->setValue(tempEdgeThickness);
  if (lastSettings->value(EDGE_TYPE).toInt() == SOLID)
    ui->radioButton_edgeType_solid->setChecked(true);
  if (lastSettings->value(EDGE_TYPE).toInt() == DASHED)
    ui->radioButton_edgeType_dashed->setChecked(true);

  // restoring vertex settings
  if (tempVertexSize != -1) ui->vertexSize->setValue(tempVertexSize);
  if (lastSettings->value(VERTEX_TYPE).toInt() == CIRCLE)
    ui->radioButton_vertexType_circle->setChecked(true);
  if (lastSettings->value(VERTEX_TYPE).toInt() == SQUARE)
    ui->radioButton_vertexType_square->setChecked(true);
  if (lastSettings->value(VERTEX_TYPE).toInt() == NOVERTEX)
    ui->radioButton_vertexType_novertex->setChecked(true);
}
