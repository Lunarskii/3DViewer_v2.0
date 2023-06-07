#ifndef CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
#define CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_

#include <QButtonGroup>
#include <QColor>         // library for using colors
#include <QColorDialog>   // library for dialog windows
#include <QFileDialog>    // library for dialog windows
#include <QKeyEvent>      // library for receiving keyboard signals
#include <QMouseEvent>    // library for receiving mouse signals
#include <QOpenGLWidget>  // library for using widgets
#include <QPalette>
#include <QScrollArea>  //
#include <QSettings>    // library for saving and restoring settings
#include <QTimer>       // library for time counting
#include <QWheelEvent>  // library for receiving mouse wheel signals
#include <QWidget>      // library for using widgets

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

struct TransformInfo {
  double move_x;
  double move_y;
  double move_z;
  int rotate_x;
  int rotate_y;
  int rotate_z;
  double scale;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
class Facade;
}  // namespace Ui
QT_END_NAMESPACE

class Facade : public QObject {
  Q_OBJECT

 public:
  Facade() : ui(nullptr) {}
  explicit Facade(Ui::View* ui) : ui(ui) {}

  void MoveModel(QString& sliderName);
  void RotateModel(QString& sliderName);
  void ScaleModel(QString& sliderName);
  void Transform(QSlider* slider);

 signals:
  void SetTransform(int strategyType, double value, int axis);

 private:
  Ui::View* ui;
  struct TransformInfo transform_info_ {};
};

class View : public QOpenGLWidget {
  Q_OBJECT

 public:
  explicit View(QWidget* parent = nullptr);
  ~View() override;
  friend class Facade;

 signals:
  void SetModel(QString fileName);

 public slots:
  void HandleSolution(std::vector<int>* vertex_index_,
                      std::vector<double>* vertex_coord_);

 private slots:
  void on_pushButton_open_file_clicked();
  void ClearSliders();
  void TransformModel();
  void Record(QAbstractButton* button);
  void SetColor(QAbstractButton* button);
  void ChangeTab(QAbstractButton* button);
  void SaveImage();

 private:
  Ui::View* ui;
  int* vertex_index_{nullptr};
  double* vertex_coord_{nullptr};
  int count_vertex_index_{};
  int count_vertex_coord_{};

  // Model rendering methods
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void updateValues();
  void setProjectionType();
  void setEdges();
  void setVertices();

  // Methods for saving and restoring settings
  QSettings* lastSettings;
  void SaveSettings();
  void RestoreSettings();

  // Methods for saving images
  void SaveGif();
  void SaveBmp();
  void SaveJpeg();

  // Colors
  QColor backgroundColor;
  QColor edgeColor;
  QColor vertexColor;

  // GIF
  QGifImage* gif;
  QTimer* timer;
  int frames;

  //     Events
  QPoint clickPosition;
  bool leftButton;
  bool rightButton;
  void mouseMoveEvent(QMouseEvent* cursorPosition) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* cursorPosition) override;
  void wheelEvent(QWheelEvent* event) override;

  void initDefaultValues();
  void ConnectSlotSignals();

  int projectionType;
  int edgeType;
  float edgeWidth;
  int pointType;
  float pointSize;
  int pointVisibility;
  float x_angle, y_angle, z_angle;

 public:  //  для использования в коннекте контроллера, пока другого способа не
          //  нашел
  Facade* facade;
};

#endif  // CPP4_3DVIEWER_V2_0_VIEW_VIEW_H_
