#ifndef VIEW_H
#define VIEW_H


#include <QOpenGLWidget>
#include "model.h"
#include "paintHelper.h"
#include <QObject>

class View : public QOpenGLWidget
{

    Q_OBJECT
public:
    View(QWidget* parent);
    virtual ~View();

    void setModel(Model* node);

    void initializeGL() override;
    void paintGL() override;

    void paintEvent(QPaintEvent *e) override;
    void resizeEvent(QResizeEvent *e) override;
    bool event(QEvent *e) override;
//    void resizeGL(int w, int h) override;

    void animate();

public slots:
    void setZoomValue(int value);

protected:
    Model* model_;
    PaintHelper paintHelper_;
    int elapsed_;
    int scale_;
};

#endif // VIEW_H
