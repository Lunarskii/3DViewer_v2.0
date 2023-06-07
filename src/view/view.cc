#include "view.h"

View::View(QWidget *parent)
    : QOpenGLWidget(parent), ui(new Ui::View), facade(new Facade(ui)) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  this->resize(1440, 1080);
  initDefaultValues();
  ConnectSlotSignals();
  lastSettings = new QSettings("SAVE_3DVIEWER", "3DViewer", this);
  RestoreSettings();
}

View::~View() {
  SaveSettings();
  delete lastSettings;
  delete facade;
  delete ui;
}

void View::ConnectSlotSignals() {
  // connecting change tab
  connect(ui->buttonGroupTabs, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(ChangeTab(QAbstractButton *)));

  // connecting colors
  connect(ui->buttonGroupColors, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(SetColor(QAbstractButton *)));

  // connecting save format
  connect(ui->buttonGroupImg, SIGNAL(buttonClicked(QAbstractButton *)), this,
          SLOT(Record(QAbstractButton *)));

  // connecting transform
  std::vector<QSlider *> transform_sliders = {
      ui->horizontalSlider_move_x,   ui->horizontalSlider_move_y,
      ui->horizontalSlider_move_z,   ui->horizontalSlider_rotate_x,
      ui->horizontalSlider_rotate_y, ui->horizontalSlider_rotate_z,
      ui->horizontalSlider_scale};

  for (auto slider : transform_sliders) {
    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(TransformModel()));
  }

  connect(ui->horizontalSlider_vert_size, SIGNAL(valueChanged(int)), this, SLOT(update()));
  connect(ui->horizontalSlider_edges_thick, SIGNAL(valueChanged(int)), this, SLOT(update()));
  connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(ui->comboBox_disp_method, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
  connect(ui->comboBox_disp_method_2, SIGNAL(currentIndexChanged(int)), this, SLOT(update()));
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

void View::SetColor(QAbstractButton *button) {
  QColor color = QColorDialog::getColor();

  if (color.isValid()) {
    if (button == ui->pushButton_bg_color) {
      backgroundColor = color;
      ui->pushButton_bg_color->setStyleSheet(
          QString("background-color: %1").arg(backgroundColor.name()));
    } else if (button == ui->pushButton_edges_color) {
      edgeColor = color;
      ui->pushButton_edges_color->setStyleSheet(
          QString("background-color: %1").arg(edgeColor.name()));
    } else if (button == ui->pushButton_vertex_color) {
      vertexColor = color;
      ui->pushButton_vertex_color->setStyleSheet(
          QString("background-color: %1").arg(vertexColor.name()));
    }

    update();
  }
}

void View::ChangeTab(QAbstractButton *button) {
  int tabIndex = ui->tabWidget->currentIndex();

  if (button == ui->_pushButton_transformation2 && tabIndex != 0) {
    ui->tabWidget->setCurrentIndex(0);
  } else if (button == ui->pushButton_settings1 && tabIndex != 1) {
    ui->tabWidget->setCurrentIndex(1);
  }
}

void View::ClearSliders() {
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
  QString filepath = QFileDialog::getOpenFileName(
      this, ("Select Model"), "../models/", "3D Image Files (*.obj)");

  if (filepath != "") {
    ClearSliders();
    emit SetModel(filepath);
    ui->label_filename->setText((QFileInfo(filepath)).fileName());
    ui->label_filename->setStyleSheet(
        QString("background-color: %1").arg(QColor(58, 81, 113).name()));
  }
}

void View::HandleSolution(std::vector<int> *vertex_index,
                          std::vector<double> *vertex_coord) {
  vertex_index_ = vertex_index->data();
  vertex_coord_ = vertex_coord->data();
  count_vertex_index_ = static_cast<int>(vertex_index->size());
  count_vertex_coord_ = static_cast<int>(vertex_coord->size());
  QString info = "Count of vertex: %1\nCount of facets: %2";
  ui->label_file_info->setText(
      info.arg(count_vertex_coord_ / 3).arg(count_vertex_index_ / 8));
  update();
}

void View::TransformModel() {
  auto *slider = qobject_cast<QSlider *>(sender());
  facade->Transform(slider);
  update();
}

void View::Record(QAbstractButton *button) {
  if (button == ui->pushButton_bmp)
    SaveBmp();
  else if (button == ui->pushButton_jpeg)
    SaveJpeg();
  else if (button == ui->pushButton_gif)
    SaveGif();
}
