#include "view.h"

void Facade::moveModel(QString& sliderName)
{
    if (sliderName == "horizontalSlider_move_x")
    {
        emit setTransform(0, ui->horizontalSlider_move_x->value() - moveX, 0);
        moveX = ui->horizontalSlider_move_x->value();
    }
    else if (sliderName == "horizontalSlider_move_y")
    {
        emit setTransform(0, ui->horizontalSlider_move_y->value() - moveY, 1);
        moveY = ui->horizontalSlider_move_y->value();
    }
    else if (sliderName == "horizontalSlider_move_z")
    {
        emit setTransform(0, ui->horizontalSlider_move_z->value() - moveZ, 2);
        moveZ = ui->horizontalSlider_move_z->value();
    }
}

void Facade::rotateModel(QString& sliderName)
{
    if (sliderName == "horizontalSlider_rotate_x")
    {
        emit setTransform(1, ui->horizontalSlider_rotate_x->value() - rotateX, 0);
        rotateX = ui->horizontalSlider_rotate_x->value();
    }
    else if (sliderName == "horizontalSlider_rotate_y")
    {
        emit setTransform(1, ui->horizontalSlider_rotate_y->value() - rotateY, 1);
        rotateY = ui->horizontalSlider_rotate_y->value();
    }
    else if (sliderName == "horizontalSlider_rotate_z")
    {
        emit setTransform(1, ui->horizontalSlider_rotate_z->value() - rotateZ, 2);
        rotateZ = ui->horizontalSlider_rotate_z->value();
    }
}

void Facade::scaleModel(QString& sliderName)
{
    if (sliderName == "horizontalSlider_scale")
    {
        if (scale == 0) scale = 1;
        emit setTransform(2, ui->horizontalSlider_scale->value() / 20.0 / scale, 0);
        scale = ui->horizontalSlider_scale->value() / 20.0;
    }
}

void Facade::transform(QSlider* slider)
{
    QString sliderName = slider->objectName();

    moveModel(sliderName);
    rotateModel(sliderName);
    scaleModel(sliderName);
}