#include "view.h"

View::View(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::View)
    , facade(new Facade(ui))
{
    setlocale(LC_NUMERIC, "C");
    ui->setupUi(this);
    this->resize(1440, 1080);
    initDefaultValues();

    connect(ui->_pushButton_transformation2, SIGNAL(clicked()), this, SLOT(changeTab()));
    connect(ui->pushButton_settings1, SIGNAL(clicked()), this, SLOT(changeTab()));

    connect(ui->horizontalSlider_move_x, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
    connect(ui->horizontalSlider_move_y, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
    connect(ui->horizontalSlider_move_z, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
    connect(ui->horizontalSlider_rotate_x, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
    connect(ui->horizontalSlider_rotate_y, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
    connect(ui->horizontalSlider_rotate_z, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));
    connect(ui->horizontalSlider_scale, SIGNAL(valueChanged(int)), this, SLOT(transformModel()));

    // // QList<QPushButton*> propertyButtons = { ui->radioButton_parallel_type,
    // //                                         ui->radioButton_central_type, 
    // //                                         ui->radioButton_edgeType_dashed, 
    // //                                         ui->radioButton_edgeType_solid, 
    // //                                         ui->radioButton_vertexType_circle,
    // //                                         ui->radioButton_vertexType_square,
    // //                                         ui->radioButton_vertexType_novertex };

    // // foreach (QPushButton* button, propertyButtons) 
    // // {
    // //     connect(button, SIGNAL(clicked()), this, SLOT(update()));
    // // }

    // // connecting colors
     connect(ui->pushButton_bg_color, SIGNAL(clicked()), this, SLOT(setColor()));
     connect(ui->pushButton_edges_color, SIGNAL(clicked()), this, SLOT(setColor()));
     connect(ui->pushButton_vertex_color, SIGNAL(clicked()), this, SLOT(setColor()));

    // // connecting buttons to synchronize model updates
    // connect(ui->radioButton_parallel_type, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->radioButton_central_type, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->radioButton_edgeType_dashed, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->radioButton_edgeType_solid, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->radioButton_vertexType_circle, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->radioButton_vertexType_square, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->radioButton_vertexType_novertex, SIGNAL(clicked()), this, SLOT(update()));
    // connect(ui->edgeThickness, SIGNAL(valueChanged(int)), this, SLOT(update()));
    // connect(ui->vertexSize, SIGNAL(valueChanged(int)), this, SLOT(update()));

    // lastSettings = new QSettings("SAVE_3DVIEWER", "3DViewer", this);
    // restoreSettings();
}

View::~View()
{
    // saveSettings();
    // delete lastSettings;
    delete facade;
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
        char buffer[50] = {};

        if (button == ui->pushButton_bg_color)
        {
            backgroundColor = color;
            sprintf(buffer, "background-color: rgb(%d, %d, %d);", color.red(), color.green(), color.blue());
            ui->pushButton_bg_color->setStyleSheet(buffer);
        }
        else if (button == ui->pushButton_edges_color)
        {
            edgeColor = color;
            sprintf(buffer, "background-color: rgb(%d, %d, %d);", color.red(), color.green(), color.blue());
            ui->pushButton_edges_color->setStyleSheet(buffer);
        }
        else if (button == ui->pushButton_vertex_color)
        {
            vertexColor = color;
            sprintf(buffer, "background-color: rgb(%d, %d, %d);", color.red(), color.green(), color.blue());
            ui->pushButton_vertex_color->setStyleSheet(buffer);
        }

        update();
    }
}

void View::changeTab()
{
    QPushButton *button = (QPushButton *)sender();
    int tabIndex = ui->tabWidget->currentIndex();

    if (button == ui->_pushButton_transformation2 && tabIndex != 0)
    {
        ui->tabWidget->setCurrentIndex(0);
    }
    else if (button == ui->pushButton_settings1 && tabIndex != 1)
    {
        ui->tabWidget->setCurrentIndex(1);
    }
}

void View::on_pushButton_open_file_clicked() {
    QString filePath = QFileDialog::getOpenFileName(this, ("Select Model"), "../models/", "3D Image Files (*.obj)");

    if (filePath != "") 
    {
        emit setModel(filePath);

        ui->label_filename->setText((QFileInfo(filePath)).fileName());
    }
}

void View::handleSolution(std::vector<int>* vertexIndex, std::vector<double>* vertexCoord)
{
    this->vertexIndex = vertexIndex->data();
    this->vertexCoord = vertexCoord->data();
    this->countVertexIndex = vertexIndex->size();
    this->countVertexCoord = vertexCoord->size();
    update();
}

void View::transformModel() 
{
    QSlider* slider = qobject_cast<QSlider*>(sender());
    facade->transform(slider);
    update();
}
