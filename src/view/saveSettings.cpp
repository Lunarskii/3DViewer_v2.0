 #include "view.h"

 void View::saveSettings() {
   // saving color settings
   lastSettings->setValue("background_color", backgroundColor.name());
   lastSettings->setValue("edge_color", edgeColor.name());
   lastSettings->setValue("vertex_color", vertexColor.name());

   // saving projection settings
   if (ui->comboBox_disp_method_2->currentText() == "Parallel") {
     lastSettings->setValue("projection_type", PARALLEL);
   } else {
     lastSettings->setValue("projection_type", CENTRAL);
   }

   // saving edge settings
   lastSettings->setValue("edge_thickness", ui->horizontalSlider_edges_thick->value());
   if (ui->comboBox->currentText() == "Solid") {
     lastSettings->setValue("edge_type", SOLID);
   } else {
     lastSettings->setValue("edge_type", DASHED);
   }

   // saving vertex settings
   lastSettings->setValue("vertex_size", ui->horizontalSlider_vert_size->value());
   if (ui->comboBox_disp_method->currentText() == "Circle") {
     lastSettings->setValue("vertex_type", CIRCLE);
   } else if (ui->comboBox_disp_method->currentText() == "Square") {
     lastSettings->setValue("vertex_type", SQUARE);
   } else {
     lastSettings->setValue("vertex_type", NOVERTEX);
   }
 }

 void View::restoreSettings() {
   QString tempBackgroundColor =lastSettings->value("background_color", -1).toString();
   QString tempEdgeColor = lastSettings->value("edge_color", -1).toString();
   QString tempVertexColor = lastSettings->value("vertex_color", -1).toString();
   int tempEdgeThickness = lastSettings->value("edge_thickness", -1).toInt();
   int tempVertexSize = lastSettings->value("vertex_size", -1).toInt();

   // restoring color settings
   if (tempBackgroundColor != "-1")
     backgroundColor.setNamedColor(tempBackgroundColor);
   if (tempEdgeColor != "-1") edgeColor.setNamedColor(tempEdgeColor);
   if (tempVertexColor != "-1") vertexColor.setNamedColor(tempVertexColor);

   // restoring projection settings
   if (lastSettings->value("projection_type").toInt() == PARALLEL)
     ui->comboBox_disp_method_2->setCurrentIndex(0);
   if (lastSettings->value("projection_type").toInt() == CENTRAL)
     ui->comboBox_disp_method_2->setCurrentIndex(1);

   // restoring edge settings
   if (tempEdgeThickness != -1) {
     ui->horizontalSlider_edges_thick->setValue(tempEdgeThickness);
   }
   if (lastSettings->value("edge_type").toInt() == SOLID) {
     ui->comboBox->setCurrentIndex(0);
   }
   if (lastSettings->value("edge_type").toInt() == DASHED) {
     ui->comboBox->setCurrentIndex(1);
   }

   // restoring vertex settings
   if (tempVertexSize != -1) {
     ui->horizontalSlider_vert_size->setValue(tempVertexSize);
   }
   if (lastSettings->value("vertex_type").toInt() == CIRCLE) {
     ui->comboBox_disp_method->setCurrentIndex(0);
   }
   if (lastSettings->value("vertex_type").toInt() == SQUARE) {
     ui->comboBox_disp_method->setCurrentIndex(1);
   }
   if (lastSettings->value("vertex_type").toInt() == NOVERTEX) {
     ui->comboBox_disp_method->setCurrentIndex(2);
   }
 }
