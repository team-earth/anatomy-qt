#include "myqgraphicsview.h"
#include "paintHelper.h"
#include "mainwindow.h"

#include <iostream>
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QOpenGLFunctions>
#include <QGraphicsScene>
#include <QPropertyAnimation>

MyQGraphicsView::MyQGraphicsView(QWidget* parent) :
    //scene_(new QGraphicsScene(parent)),
    QGraphicsView(parent), /*, model_(nullptr),*/ elapsed_(0), scale_(50)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setInteractive(true);
}

//void View::setModel(Model* model)
//{
//    model_ = model;

////    this->
//}

MyQGraphicsView::~MyQGraphicsView()
{
//    // Make sure the context is current and then explicitly
//    // destroy all underlying OpenGL resources.
//    makeCurrent();

//    delete m_texture;
//    delete m_shader;
//    delete m_program;

//    m_vbo.destroy();
//    m_vao.destroy();

//    doneCurrent();
//    std::cout << "OpenGLWidget::~OpenGLWidget()" << std::endl;

}

#if 0
void View::initializeGL()
{
//    m_vao.create();
//    if (m_vao.isCreated())
//        m_vao.bind();

//    m_vbo.create();
//    m_vbo.bind();
//    m_vbo.allocate(...);

//    m_texture = new QOpenGLTexture(QImage(...));

//    m_shader = new QOpenGLShader(...);
//    m_program = new QOpenGLShaderProgram(...);
    QOpenGLWidget::initializeGL();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    setAutoFillBackground(true);
//    qDebug() << "OpenGLWidget::initializeGL()";
}

void View::paintGL()
{
//    m_vao.create();
//    if (m_vao.isCreated())
//        m_vao.bind();

//    m_vbo.create();
//    m_vbo.bind();
//    m_vbo.allocate(...);

//    m_texture = new QOpenGLTexture(QImage(...));

//    m_shader = new QOpenGLShader(...);
//    m_program = new QOpenGLShaderProgram(...);
    QOpenGLWidget::paintGL();
//    qDebug() << "OpenGLWidget::paintGL()";
}

void View::animate()
{
    elapsed_ = (elapsed_ + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}
//! [1]

void View::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::TextAntialiasing);
//    painter.setBackgroundMode(Qt::OpaqueMode);

    paintHelper_.paint(&painter, e, model_->getCenterNode(), scale_);

    painter.end();
//    std::cout << "OpenGLWidget::paintEvent()" << std::endl;
//    QOpenGLWidget::paintEvent(e);
}
void View::resizeEvent(QResizeEvent *e)
{
    std::cout << "OpenGLWidget::resizeEvent()" << std::endl;
    QOpenGLWidget::resizeEvent(e);
}

//bool View::resizeGL()
//{


//}

bool View::event(QEvent *e){
//    qDebug() << "OpenGLWidget::event()" << e->type();
    return QOpenGLWidget::event(e);
}
#endif
void MyQGraphicsView::setZoomValue(int scale)
{
//    painter->translate(v.width()/2, v.height()/2);

    qreal s = scale/100.0;
    QTransform t = QTransform::fromScale(s,s);
//    qDebug() << "valueChanged" << scale << t;

    setTransform(t);
}

//void View::setRotationDegrees(int degrees)
//{
//    qDebug() << "View::setRotationDegrees start" << degrees;

//    QPropertyAnimation * animation = new QPropertyAnimation(this, "rotation");

//    animation->setDuration(1000);

//    animation->setStartValue(20);
//    animation->setEndValue(40);
//    animation->start();

//    qDebug() << "View::setRotationDegrees end" << degrees;

////    QTransform t = transform();
////    t.rotate(degrees);
////    setTransform(t);
//}
