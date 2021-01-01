#include "openglwidget.h"
#include "paintHelper.h"

#include <iostream>
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QOpenGLFunctions>

OpenGLWidget::OpenGLWidget(QWidget* parent) :
    QOpenGLWidget(parent), node_(nullptr), elapsed_(0)
{
    std::cout << "OpenGLWidget::OpenGLWidget()" << std::endl;
}

void OpenGLWidget::setModel(Node* node)
{
    node_ = node;

//    this->
}

OpenGLWidget::~OpenGLWidget()
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
    std::cout << "OpenGLWidget::~OpenGLWidget()" << std::endl;

}

void OpenGLWidget::initializeGL()
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
    qDebug() << "OpenGLWidget::initializeGL()";
}

void OpenGLWidget::paintGL()
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
    qDebug() << "OpenGLWidget::paintGL()";
}

void OpenGLWidget::animate()
{
    elapsed_ = (elapsed_ + qobject_cast<QTimer*>(sender())->interval()) % 1000;
    update();
}
//! [1]

void OpenGLWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);

    paintHelper_.paint(&painter, e, elapsed_);

    painter.end();
    std::cout << "OpenGLWidget::paintEvent()" << std::endl;
//    QOpenGLWidget::paintEvent(e);
}
void OpenGLWidget::resizeEvent(QResizeEvent *e)
{
    std::cout << "OpenGLWidget::resizeEvent()" << std::endl;
    QOpenGLWidget::resizeEvent(e);

}
bool OpenGLWidget::event(QEvent *e){
    qDebug() << "OpenGLWidget::event()" << e->type();
    return QOpenGLWidget::event(e);
}
