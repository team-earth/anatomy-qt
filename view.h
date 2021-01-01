#ifndef VIEW_H
#define VIEW_H


#include <QOpenGLWidget>
#include "model.h"
#include "paintHelper.h"

class View : public QOpenGLWidget
{
public:
    View(QWidget* parent);
    virtual ~View();

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

#endif // VIEW_H
