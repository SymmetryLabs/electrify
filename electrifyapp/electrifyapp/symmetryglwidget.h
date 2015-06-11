#ifndef WIDGET
#define WIDGET

#include <QOpenGLWidget>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>
#include "model.h"
#include "output.h"

class SymmetryGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    shared_ptr<Model> model;
    shared_ptr<Output> output;
    SymmetryGLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void setModel(shared_ptr<Model> m) { model = m; vtx = new GLfloat[model->pixels.size() * 3]; }
    void setOutput(shared_ptr<Output> o) { output = o; col = new GLfloat[output->colorBuffer.size() * 4]; }
    float *vtx =0;
    float *col= 0;
private:
    QMatrix4x4 m_projection;
    QOpenGLShaderProgram *m_program=0;
    QSize m_viewportSize;
    qreal m_t;
    float *values;
    void populateModel();
    void populateColors();
};

#endif // WIDGET

