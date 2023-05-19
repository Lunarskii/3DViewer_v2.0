#include "view.h"

View::View(Controller* c, QWidget *parent)
    : controller(c)
    , QOpenGLWidget(parent)
    , ui(new Ui::View)
{
    setlocale(LC_NUMERIC, "C");
    ui->setupUi(this);
    this->resize(1440, 1080);
    initDefaultValues();

    // connecting the movement buttons
    connect(ui->pushButton_moving_x_minus, SIGNAL(clicked()), this, SLOT(moving()));
    connect(ui->pushButton_moving_x_plus, SIGNAL(clicked()), this, SLOT(moving()));
    connect(ui->pushButton_moving_y_minus, SIGNAL(clicked()), this, SLOT(moving()));
    connect(ui->pushButton_moving_y_plus, SIGNAL(clicked()), this, SLOT(moving()));
    connect(ui->pushButton_moving_z_minus, SIGNAL(clicked()), this, SLOT(moving()));
    connect(ui->pushButton_moving_z_plus, SIGNAL(clicked()), this, SLOT(moving()));

    // connecting the rotation buttons
    connect(ui->pushButton_rotation_x_minus, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->pushButton_rotation_x_plus, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->pushButton_rotation_y_minus, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->pushButton_rotation_y_plus, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->pushButton_rotation_z_minus, SIGNAL(clicked()), this, SLOT(rotation()));
    connect(ui->pushButton_rotation_z_plus, SIGNAL(clicked()), this, SLOT(rotation()));

    // connecting zoom buttons
    connect(ui->pushButton_scaling_minus, SIGNAL(clicked()), this, SLOT(scaling()));
    connect(ui->pushButton_scaling_plus, SIGNAL(clicked()), this, SLOT(scaling()));

    // connecting colors
    connect(ui->pushButton_backgroundColor, SIGNAL(clicked()), this, SLOT(setColor()));
    connect(ui->pushButton_edgeColor, SIGNAL(clicked()), this, SLOT(setColor()));
    connect(ui->pushButton_vertexColor, SIGNAL(clicked()), this, SLOT(setColor()));

    // connecting buttons to synchronize model updates
    connect(ui->radioButton_parallel_type, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->radioButton_central_type, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->radioButton_edgeType_dashed, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->radioButton_edgeType_solid, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->radioButton_vertexType_circle, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->radioButton_vertexType_square, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->radioButton_vertexType_novertex, SIGNAL(clicked()), this, SLOT(update()));
    connect(ui->edgeThickness, SIGNAL(valueChanged(int)), this, SLOT(update()));
    connect(ui->vertexSize, SIGNAL(valueChanged(int)), this, SLOT(update()));

    lastSettings = new QSettings("SAVE_3DVIEWER", "3DViewer", this);
    restoreSettings();
}

View::~View()
{
    saveSettings();
    delete lastSettings;
    delete ui;
}

void View::initDefaultValues() 
{
    // setting the color
    backgroundColor.setRgb(255, 255, 255);
    edgeColor.setRgb(0, 0, 255);
    vertexColor.setRgb(255, 0, 0);
}

void View::setColor() 
{
    QPushButton *button = (QPushButton *)sender();

    if (button == ui->pushButton_backgroundColor) 
    {
        backgroundColor = QColorDialog::getColor();
    } 
    else if (button == ui->pushButton_edgeColor) 
    {
        edgeColor = QColorDialog::getColor();
    } 
    else if (button == ui->pushButton_vertexColor) 
    {
        vertexColor = QColorDialog::getColor();
    }

    update();
}

void View::on_pushButton_selectFile_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, ("Select Model"), "../models/", "3D Image Files (*.obj)");

    if (filePath != "") 
    {
        controller->setFileName(filePath.toStdString());
        if (controller->getError() == 0)
        {
            ui->fileName->setText((QFileInfo(filePath)).fileName());
            ui->numberOfVertices->setText(QString::number(controller->getVertexCoord().size() / 3));
            ui->numberOfEdges->setText(QString::number(controller->getVertexIndex().size() / 2));
            update();
        }
        else
        {
            // создать окно с ошибкой
        }
    }
}

void View::moving() 
{
  double step = ui->step->value();
  QPushButton *button = (QPushButton *)sender();

  if (button == ui->pushButton_moving_x_minus) {
    controller->transform(MOVE, -step, X);
  } else if (button == ui->pushButton_moving_x_plus) {
    controller->transform(MOVE, step, X);
  } else if (button == ui->pushButton_moving_y_minus) {
    controller->transform(MOVE, -step, Y);
  } else if (button == ui->pushButton_moving_y_plus) {
    controller->transform(MOVE, step, Y);
  } else if (button == ui->pushButton_moving_z_minus) {
    controller->transform(MOVE, -step, Z);
  } else if (button == ui->pushButton_moving_z_plus) {
    controller->transform(MOVE, step, Z);
  }

  update();
}

void View::rotation() 
{
  int angle = ui->angle->value();
  QPushButton *button = (QPushButton *)sender();

  if (button == ui->pushButton_rotation_x_minus) {
    controller->transform(ROTATE, -angle, X);
  } else if (button == ui->pushButton_rotation_x_plus) {
    controller->transform(ROTATE, angle, X);
  } else if (button == ui->pushButton_rotation_y_minus) {
    controller->transform(ROTATE, -angle, Y);
  } else if (button == ui->pushButton_rotation_y_plus) {
    controller->transform(ROTATE, angle, Y);
  } else if (button == ui->pushButton_rotation_z_minus) {
    controller->transform(ROTATE, -angle, Z);
  } else if (button == ui->pushButton_rotation_z_plus) {
    controller->transform(ROTATE, angle, Z);
  }

  update();
}

void View::scaling() 
{
  int scale = ui->scale->value();
  QPushButton *button = (QPushButton *)sender();
  QString buttonText = button->text();

  if (buttonText == "-") {
    controller->transform(SCALE, -scale);
  } else {
    controller->transform(SCALE, scale);
  }

  update();
}

