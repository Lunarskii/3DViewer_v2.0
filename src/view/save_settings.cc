#include "view.h"

void View::SaveSettings() {
  // saving color settings
  lastSettings->setValue("background_color", settings.backgroundColor.name());
  lastSettings->setValue("edge_color", settings.edgeColor.name());
  lastSettings->setValue("vertex_color", settings.vertexColor.name());

  // saving projection settings
  if (ui->comboBox_disp_method_2->currentText() == "Parallel") {
    lastSettings->setValue("projection_type", kParallel);
  } else {
    lastSettings->setValue("projection_type", kCentral);
  }

  // saving edge settings
  lastSettings->setValue("edge_thickness",
                         ui->horizontalSlider_edges_thick->value());
  if (ui->comboBox->currentText() == "Solid") {
    lastSettings->setValue("edge_type", kSolid);
  } else {
    lastSettings->setValue("edge_type", kDashed);
  }

  // saving vertex settings
  lastSettings->setValue("vertex_size",
                         ui->horizontalSlider_vert_size->value());
  if (ui->comboBox_disp_method->currentText() == "Circle") {
    lastSettings->setValue("vertex_type", kCircle);
  } else if (ui->comboBox_disp_method->currentText() == "Square") {
    lastSettings->setValue("vertex_type", kSquare);
  } else {
    lastSettings->setValue("vertex_type", kNoVertex);
  }
}

void View::RestoreSettings() {
  QString tempBackgroundColor =
      lastSettings->value("background_color", -1).toString();
  QString tempEdgeColor = lastSettings->value("edge_color", -1).toString();
  QString tempVertexColor = lastSettings->value("vertex_color", -1).toString();
  int tempEdgeThickness = lastSettings->value("edge_thickness", -1).toInt();
  int tempVertexSize = lastSettings->value("vertex_size", -1).toInt();

  // restoring color settings
  if (tempBackgroundColor != "-1") {
    settings.backgroundColor.setNamedColor(tempBackgroundColor);
    QColor color(tempBackgroundColor);
    ui->pushButton_bg_color->setStyleSheet(
        QString("background-color: %1").arg(color.name()));
  }
  if (tempEdgeColor != "-1") {
    settings.edgeColor.setNamedColor(tempEdgeColor);
    QColor color(tempEdgeColor);
    ui->pushButton_edges_color->setStyleSheet(
        QString("background-color: %1").arg(color.name()));
  }
  if (tempVertexColor != "-1") {
    settings.vertexColor.setNamedColor(tempVertexColor);
    QColor color(tempVertexColor);
    ui->pushButton_vertex_color->setStyleSheet(
        QString("background-color: %1").arg(color.name()));
  }

  // restoring projection settings
  if (lastSettings->value("projection_type").toInt() == kParallel)
    ui->comboBox_disp_method_2->setCurrentIndex(0);
  if (lastSettings->value("projection_type").toInt() == kCentral)
    ui->comboBox_disp_method_2->setCurrentIndex(1);

  // restoring edge settings
  if (tempEdgeThickness != -1) {
    ui->horizontalSlider_edges_thick->setValue(tempEdgeThickness);
  }
  if (lastSettings->value("edge_type").toInt() == kSolid) {
    ui->comboBox->setCurrentIndex(0);
  }
  if (lastSettings->value("edge_type").toInt() == kDashed) {
    ui->comboBox->setCurrentIndex(1);
  }

  // restoring vertex settings
  if (tempVertexSize != -1) {
    ui->horizontalSlider_vert_size->setValue(tempVertexSize);
  }
  if (lastSettings->value("vertex_type").toInt() == kCircle) {
    ui->comboBox_disp_method->setCurrentIndex(0);
  }
  if (lastSettings->value("vertex_type").toInt() == kSquare) {
    ui->comboBox_disp_method->setCurrentIndex(1);
  }
  if (lastSettings->value("vertex_type").toInt() == kNoVertex) {
    ui->comboBox_disp_method->setCurrentIndex(2);
  }
}
