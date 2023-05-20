#include "view.h"

void View::Facade::moveModel(QPushButton* button)
{
    double step = ui->step->value();

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
}

void View::Facade::rotateModel(QPushButton* button)
{
    int angle = ui->angle->value();

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
}

void View::Facade::scaleModel(QString buttonText)
{
    int scale = ui->scale->value();

    if (buttonText == "-") {
        controller->transform(SCALE, -scale);
    } else if (buttonText == "+") {
        controller->transform(SCALE, scale);
    }
}

void View::Facade::transformModel(QPushButton* button)
{
    moveModel(button);
    rotateModel(button);
    scaleModel(button->text());
}