#ifndef VIEW_H
#define VIEW_H


#include <QOpenGLWidget>
#include "paintHelper.h"
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
//    Q_PROPERTY(qreal my_rotation READ my_rotation WRITE setMyRotation)

public:
    View(QWidget* parent);
    virtual ~View();



//    void setModel(Model* node);

//    void initializeGL() override;
//    void paintGL() override;

//    void paintEvent(QPaintEvent *e) override;
//    void resizeEvent(QResizeEvent *e) override;
//    bool event(QEvent *e) override;
//    void resizeGL(int w, int h) override;

//    void animate();

//    int my_rotation() const { qDebug() << "my_rotation()"; return rotation_; }
//    void setMyRotation(int r)
//    {
//        qDebug() << "setRotation" << r;
//        rotation_ = r; /*prepareGeometryChange();*/
//        QTransform t = transform();
//        t.rotate(r);
//        setTransform(t);
//    }
//    int rotation_;

public slots:
    void setZoomValue(int value);
//    void setRotationDegrees(int degrees);

protected:
    std::unique_ptr<QGraphicsScene> scene_;

//    Model* model_;
    PaintHelper paintHelper_;
    int elapsed_;
    int scale_;
};

#endif // VIEW_H
