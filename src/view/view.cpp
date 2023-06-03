#include "view.h"

View::View(QWidget *parent)
    : QOpenGLWidget(parent), ui(new Ui::View), facade(new Facade(ui)) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  this->resize(1440, 1080);
  initDefaultValues();

  // connecting change tab
  connect(ui->buttonGroupTabs, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(changeTab(QAbstractButton *)));

  // connecting colors
  connect(ui->buttonGroupColors, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(setColor(QAbstractButton *)));

  // connecting transform
  std::vector<QSlider *> transform_sliders = {
      ui->horizontalSlider_move_x,   ui->horizontalSlider_move_y,
      ui->horizontalSlider_move_z,   ui->horizontalSlider_rotate_x,
      ui->horizontalSlider_rotate_y, ui->horizontalSlider_rotate_z,
      ui->horizontalSlider_scale};

  for (auto slider : transform_sliders) {
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
  }

  // connecting save format

  connect(ui->buttonGroupImg, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(on_buttonGroupImg_clicked(QAbstractButton *)));

   lastSettings = new QSettings("SAVE_3DVIEWER", "3DViewer", this);
   restoreSettings();
}

View::~View() {
  saveSettings();
  delete lastSettings;
  delete facade;
  delete ui;
}

void View::initDefaultValues() {
  // setting the color
  QColor bgColor = ui->pushButton_bg_color->palette().button().color();
  QColor eColor = ui->pushButton_edges_color->palette().button().color();
  QColor vColor = ui->pushButton_vertex_color->palette().button().color();
  backgroundColor.setNamedColor(bgColor.name());
  edgeColor.setNamedColor(eColor.name());
  vertexColor.setNamedColor(vColor.name());
  ui->tabWidget->setCurrentIndex(0);
}

void View::setColor(QAbstractButton *button) {
  QColor color = QColorDialog::getColor();

  if (color.isValid()) {
    if (button == ui->pushButton_bg_color) {
      backgroundColor = color;
      ui->pushButton_bg_color->setStyleSheet(QString("background-color: %1").arg(backgroundColor.name()));
    } else if (button == ui->pushButton_edges_color) {
      edgeColor = color;
      ui->pushButton_edges_color->setStyleSheet(QString("background-color: %1").arg(edgeColor.name()));
    } else if (button == ui->pushButton_vertex_color) {
      vertexColor = color;
      ui->pushButton_vertex_color->setStyleSheet(QString("background-color: %1").arg(vertexColor.name()));
    }

    update();
  }
}

void View::changeTab(QAbstractButton *button) {
  int tabIndex = ui->tabWidget->currentIndex();

  if (button == ui->_pushButton_transformation2 && tabIndex != 0) {
    ui->tabWidget->setCurrentIndex(0);
  } else if (button == ui->pushButton_settings1 && tabIndex != 1) {
    ui->tabWidget->setCurrentIndex(1);
  }
}

void View::clearSliders() {
  QSlider *sliders[] = {
      ui->horizontalSlider_move_x,   ui->horizontalSlider_move_y,
      ui->horizontalSlider_move_z,   ui->horizontalSlider_rotate_x,
      ui->horizontalSlider_rotate_y, ui->horizontalSlider_rotate_z,
  };

  for (auto slider : sliders) {
    slider->setValue(0);
  }

  ui->horizontalSlider_scale->setValue(100);
}

void View::on_pushButton_open_file_clicked() {
  QString filePath = QFileDialog::getOpenFileName(
      this, ("Select Model"), "../models/", "3D Image Files (*.obj)");

  if (filePath != "") {
    clearSliders();
    emit setModel(filePath);
    ui->label_filename->setText((QFileInfo(filePath)).fileName());
    ui->label_filename->setStyleSheet(QString("background-color: %1").arg(QColor(58, 81, 113).name()));
  }
}

void View::handleSolution(std::vector<int> *vertexIndex,
                          std::vector<double> *vertexCoord) {
  this->vertexIndex = vertexIndex->data();
  this->vertexCoord = vertexCoord->data();
  this->countVertexIndex = vertexIndex->size();
  this->countVertexCoord = vertexCoord->size();
  QString info = "Count of vertex: %1\nCount of facets: %2";
  ui->label_file_info->setText(info.arg(countVertexCoord / 3).arg(countVertexIndex / 8));
  update();
}

void View::transformModel() {
  QSlider *slider = qobject_cast<QSlider *>(sender());
  facade->transform(slider);
  update();
}

void View::on_buttonGroupImg_clicked(QAbstractButton *button) {
   if (button == ui->pushButton_bmp) saveBmp();
    else if (button == ui->pushButton_jpeg) saveJpeg();
    else if (button == ui->pushButton_gif) saveGif();

}

