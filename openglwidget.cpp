#include "openglwidget.h"

#include <iostream>

OpenGLWidget::OpenGLWidget(QWidget* parent) :
    QOpenGLWidget(parent)
{
    std::cout << "OpenGLWidget::OpenGLWidget()" << std::endl;
}
