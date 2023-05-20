#ifndef CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
#define CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_

#include <QColor>         // library for using colors
#include <QColorDialog>   // library for dialog windows
#include <QFileDialog>    // library for dialog windows
#include <QKeyEvent>      // library for receiving keyboard signals
#include <QMouseEvent>    // library for receiving mouse signals
#include <QOpenGLWidget>  // library for using widgets
#include <QScrollArea>    //
#include <QSettings>      // library for saving and restoring settings
#include <QTimer>         // library for time counting
#include <QWheelEvent>    // library for receiving mouse wheel signals
#include <QWidget>        // library for using widgets
#include "../controller/controller.h"
#include "QtGifImage/gifimage/qgifimage.h"
#include "ui_view.h"

// projection type
#define PARALLEL 1
#define CENTRAL 2

// edge type
#define SOLID 1
#define DASHED 2

// vertex type
#define CIRCLE 1
#define SQUARE 2
#define NOVERTEX 3
#define AVERTEX 4

// lines to save the definition
#define PROJECTION_TYPE "projectionType"
#define EDGE_TYPE "edgeType"
#define VERTEX_TYPE "vertexType"
#define EDGE_THICKNESS "edgeThickness"
#define VERTEX_SIZE "vertexSize"
#define BACKGROUND_COLOR "backgroundColor"
#define EDGE_COLOR "edgeColor"
#define VERTEX_COLOR "vertexColor"
#define STEP "step"
#define ANGLE "angle"
#define SCALE_BOX "scale"

#define GL_SILENCE_DEPRECATION // проверить эту штуку, чзх

QT_BEGIN_NAMESPACE
namespace Ui 
{ 
    class View;
    class Facade;
}
QT_END_NAMESPACE

class View : public QOpenGLWidget
{
    Q_OBJECT

public:
    View(Controller* c, QWidget *parent = nullptr);
    ~View();

private slots:
    void on_pushButton_selectFile_clicked();
    void transformModel();
    void setColor();

    // Methods for saving images
    void on_actionSave_as_GIF_triggered();
    void on_actionSave_as_bmp_triggered();
    void on_actionSave_as_jpeg_triggered();
    void saveImage();

private:
    Ui::View *ui;
    Controller* controller;

    // Model rendering methods
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void updateValues();
    void setProjectionType();
    void setEdges();
    void setVertices();

    // Methods for saving and restoring settings
    QSettings *lastSettings;
    void saveSettings();
    void restoreSettings();

    // Colors
    QColor backgroundColor;
    QColor edgeColor;
    QColor vertexColor;

    // GIF
    QGifImage *gif;
    QTimer *timer;
    int frames;

    // Events
    QPoint clickPosition;
    bool leftButton;
    bool rightButton;
    void mouseMoveEvent(QMouseEvent *cursorPosition) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *cursorPosition) override;
    // void wheelEvent(QWheelEvent *event) override;
    // void keyPressEvent(QKeyEvent *event) override;  // keys for calling saving gif, jpeg and bmp

    // удалить, если не будет использоваться
    QScrollArea *scrollArea;

    void initDefaultValues();

    int projectionType;
    int edgeType;
    int edgeWidth;
    int pointType;
    int pointSize;
    int pointVisibility;

    float x_angle, y_angle, z_angle;

public:
    class Facade
    {
    public:
        Facade() : ui(nullptr), controller(nullptr) {}
        Facade(Ui::View* ui, Controller* c) : ui(ui), controller(c) {}

        void setFacadeData(Ui::View* ui, Controller* c)
        {
            this->ui = ui;
            this->controller = c;
        }

        void moveModel(QPushButton* button);
        void rotateModel(QPushButton* button);
        void scaleModel(QString buttonText);
        void transformModel(QPushButton* button);

    private:
        Ui::View* ui;
        Controller* controller;
    };

private:
    Facade facade{ui, controller};
};

#endif  // CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
