#ifndef WIDGET
#define WIDGET

#include <QOpenGLWidget>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

class Widget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    Widget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    QMatrix4x4 m_projection;
    QOpenGLShaderProgram *m_program;
    QSize m_viewportSize;
    qreal m_t;
    float *values;
};

#endif // WIDGET

