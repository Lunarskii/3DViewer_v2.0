#include "view.h"

void Facade::moveModel(QString& sliderName)
{
    double rate = 0;
    if (sliderName == "horizontalSlider_move_x")
    {
        rate = ui->horizontalSlider_move_x->value() / 50.0;
        emit setTransform(0, rate - moveX, 0);
        moveX = rate;
    }
    else if (sliderName == "horizontalSlider_move_y")
    {
        rate = ui->horizontalSlider_move_y->value() / 50.0;
        emit setTransform(0, rate - moveY, 1);
        moveY = rate;
    }
    else if (sliderName == "horizontalSlider_move_z")
    {
        rate = ui->horizontalSlider_move_z->value() / 50.0;
        emit setTransform(0, rate - moveZ, 2);
        moveZ = rate;
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
        double rate = ui->horizontalSlider_scale->value() / 20.0;
        emit setTransform(2, rate / scale, 0);
        scale = rate;
    }
}

void Facade::transform(QSlider* slider)
{
    QString sliderName = slider->objectName();

    moveModel(sliderName);
    rotateModel(sliderName);
    scaleModel(sliderName);
}