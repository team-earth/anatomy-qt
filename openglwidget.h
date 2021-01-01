#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H


#include <QOpenGLWidget>
#include "model.h"
#include "paintHelper.h"

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget(QWidget* parent);
    virtual ~OpenGLWidget();

    void setModel(Model* node);

    void initializeGL() override;
    void paintGL() override;

    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    bool event(QEvent *e) override;
    void animate();

protected:
    Model* model_;
    PaintHelper paintHelper_;
    int elapsed_;
};

#endif // OPENGLWIDGET_H
