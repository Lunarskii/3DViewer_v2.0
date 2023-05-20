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

    QList<QPushButton*> transformButtons = 
    { 
        ui->pushButton_moving_x_minus,
        ui->pushButton_moving_x_plus,
        ui->pushButton_moving_y_minus,
        ui->pushButton_moving_y_plus,
        ui->pushButton_moving_z_minus,
        ui->pushButton_moving_z_plus,
        ui->pushButton_rotation_x_minus,
        ui->pushButton_rotation_x_plus,
        ui->pushButton_rotation_y_minus,
        ui->pushButton_rotation_y_plus,
        ui->pushButton_rotation_z_minus,
        ui->pushButton_rotation_z_plus,
        ui->pushButton_scaling_minus,
        ui->pushButton_scaling_plus,
    };

    // QList<QPushButton*> propertyButtons = { ui->radioButton_parallel_type,
    //                                         ui->radioButton_central_type, 
    //                                         ui->radioButton_edgeType_dashed, 
    //                                         ui->radioButton_edgeType_solid, 
    //                                         ui->radioButton_vertexType_circle,
    //                                         ui->radioButton_vertexType_square,
    //                                         ui->radioButton_vertexType_novertex };

    foreach (QPushButton* button, transformButtons) 
    {
        connect(button, SIGNAL(clicked()), this, SLOT(transformModel()));
    }
    // foreach (QPushButton* button, propertyButtons) 
    // {
    //     connect(button, SIGNAL(clicked()), this, SLOT(update()));
    // }

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
    QColor color = QColorDialog::getColor();

    if (color.isValid())
    {
        QPushButton *button = (QPushButton *)sender();
        
        if (button == ui->pushButton_backgroundColor) 
        {
            backgroundColor = color;
        } 
        else if (button == ui->pushButton_edgeColor) 
        {
            edgeColor = color;
        } 
        else if (button == ui->pushButton_vertexColor) 
        {
            vertexColor = color;
        }

        update();
    }
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

void View::transformModel() 
{
    QPushButton *button = (QPushButton *)sender();
    facade.transformModel(button);

    update();
}
