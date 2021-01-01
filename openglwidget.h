#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H


#include <QOpenGLWidget>
#include "node.h"
#include "paintHelper.h"

class OpenGLWidget : public QOpenGLWidget
{
public:
    OpenGLWidget(QWidget* parent);
    virtual ~OpenGLWidget();

    void setModel(Node* node);

    void initializeGL() override;
    void paintGL() override;

    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    bool event(QEvent *e) override;
    void animate();

protected:
    Node* node_;
    PaintHelper paintHelper_;
    int elapsed_;
};

#endif // OPENGLWIDGET_H
