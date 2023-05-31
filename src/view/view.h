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
#include "QtGifImage/gifimage/qgifimage.h"
#include "ui_view.h"

enum Settings {
    // projection type
    PARALLEL = 1,
    CENTRAL = 2,
    // edge type
    SOLID = 1,
    DASHED = 2,
    // vertex type
    CIRCLE = 1,
    SQUARE = 2,
    NOVERTEX = 3,
    AVERTEX = 4,
};

QT_BEGIN_NAMESPACE
namespace Ui 
{ 
    class View;
    class Facade;
}
QT_END_NAMESPACE

class Facade : public QObject
{
    Q_OBJECT

public:
    Facade() : ui(nullptr) {}
    Facade(Ui::View* ui) : ui(ui) {}

    void moveModel(QString& sliderName);
    void rotateModel(QString& sliderName);
    void scaleModel(QString& sliderName);
    void transform(QSlider* slider);

signals:
    void setTransform(int strategyType, double value, int axis);

private:
    Ui::View* ui;
    double moveX{};
    double moveY{};
    double moveZ{};
    int rotateX{};
    int rotateY{};
    int rotateZ{};
    double scale{};
};

class View : public QOpenGLWidget
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    ~View();
    friend class Facade;

signals:
    void setModel(QString fileName);

public slots:
    void handleSolution(std::vector<int>* vertexIndex, std::vector<double>* vertexCoord);

private slots:
    void on_pushButton_open_file_clicked();
    void clearSliders();
    void transformModel();
    void setColor();
    void changeTab();

    // Methods for saving images
    // void on_actionSave_as_GIF_triggered();
    // void on_actionSave_as_bmp_triggered();
    // void on_actionSave_as_jpeg_triggered();
    // void saveImage();

private:
    Ui::View *ui;
    int* vertexIndex{nullptr};
    double* vertexCoord{nullptr};
    int countVertexIndex{};
    int countVertexCoord{};

    // Model rendering methods
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void updateValues();
    void setProjectionType();
    void setEdges();
    void setVertices();

    // Methods for saving and restoring settings
    // QSettings *lastSettings;
    // void saveSettings();
    // void restoreSettings();

    // Colors
    QColor backgroundColor;
    QColor edgeColor;
    QColor vertexColor;

    // GIF
    QGifImage *gif;
    QTimer *timer;
    int frames;

//     Events
     QPoint clickPosition;
     bool leftButton;
     bool rightButton;
     void mouseMoveEvent(QMouseEvent *cursorPosition) override;
     void mousePressEvent(QMouseEvent *event) override;
     void mouseReleaseEvent(QMouseEvent *cursorPosition) override;
     void wheelEvent(QWheelEvent *event) override;
//     void keyPressEvent(QKeyEvent *event) override;  // keys for calling saving gif, jpeg and bmp

    void initDefaultValues();

    int projectionType;
    int edgeType;
    float edgeWidth;
    int pointType;
    float pointSize;
    int pointVisibility;
    float x_angle, y_angle, z_angle;

public: //  для использования в коннекте контроллера, пока другого способа не нашел
    Facade* facade;
};

#endif  // CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
