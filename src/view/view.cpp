#include "view.h"

View::View(QWidget *parent)
    : QOpenGLWidget(parent), ui(new Ui::View), facade(new Facade(ui)) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  this->resize(1440, 1080);
  initDefaultValues();

  // connecting change tab
  connect(ui->_pushButton_transformation2, SIGNAL(clicked()), this,
          SLOT(changeTab()));
  connect(ui->pushButton_settings1, SIGNAL(clicked()), this, SLOT(changeTab()));

  // connecting colors
  connect(ui->pushButton_bg_color, SIGNAL(clicked()), this, SLOT(setColor()));
  connect(ui->pushButton_edges_color, SIGNAL(clicked()), this,
          SLOT(setColor()));
  connect(ui->pushButton_vertex_color, SIGNAL(clicked()), this,
          SLOT(setColor()));

  // connecting transform
  std::vector<QSlider *> transform_sliders = {
      ui->horizontalSlider_move_x,   ui->horizontalSlider_move_y,
      ui->horizontalSlider_move_z,   ui->horizontalSlider_rotate_x,
      ui->horizontalSlider_rotate_y, ui->horizontalSlider_rotate_z,
      ui->horizontalSlider_scale};

  for (auto slider : transform_sliders) {
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
  }

  // lastSettings = new QSettings("SAVE_3DVIEWER", "3DViewer", this);
  // restoreSettings();
}

View::~View() {
  // saveSettings();
  // delete lastSettings;
  delete facade;
  delete ui;
}

void View::initDefaultValues() {
  // setting the color
  QColor bgColor = ui->pushButton_bg_color->palette().button().color();
  QColor eColor = ui->pushButton_edges_color->palette().button().color();
  QColor vColor = ui->pushButton_vertex_color->palette().button().color();
  backgroundColor.setRgb(bgColor.red(), bgColor.green(), bgColor.blue());
  edgeColor.setRgb(eColor.red(), eColor.green(), eColor.blue());
  vertexColor.setRgb(vColor.red(), vColor.green(), vColor.blue());
  ui->tabWidget->setCurrentIndex(0);
}

void View::setColor() {
  QColor color = QColorDialog::getColor();

  if (color.isValid()) {
    QPushButton *button = (QPushButton *)sender();
    char buffer[50] = {};

    if (button == ui->pushButton_bg_color) {
      backgroundColor = color;
      sprintf(buffer, "background-color: rgb(%d, %d, %d);", color.red(),
              color.green(), color.blue());
      ui->pushButton_bg_color->setStyleSheet(buffer);
    } else if (button == ui->pushButton_edges_color) {
      edgeColor = color;
      sprintf(buffer, "background-color: rgb(%d, %d, %d);", color.red(),
              color.green(), color.blue());
      ui->pushButton_edges_color->setStyleSheet(buffer);
    } else if (button == ui->pushButton_vertex_color) {
      vertexColor = color;
      sprintf(buffer, "background-color: rgb(%d, %d, %d);", color.red(),
              color.green(), color.blue());
      ui->pushButton_vertex_color->setStyleSheet(buffer);
    }

    update();
  }
}

void View::changeTab() {
  QPushButton *button = (QPushButton *)sender();
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
  }
}

void View::handleSolution(std::vector<int> *vertexIndex,
                          std::vector<double> *vertexCoord) {
  this->vertexIndex = vertexIndex->data();
  this->vertexCoord = vertexCoord->data();
  this->countVertexIndex = vertexIndex->size();
  this->countVertexCoord = vertexCoord->size();
  update();
}

void View::transformModel() {
  QSlider *slider = qobject_cast<QSlider *>(sender());
  facade->transform(slider);
  update();
}
