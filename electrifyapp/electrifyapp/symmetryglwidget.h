#ifndef WIDGET
#define WIDGET

#include <QOpenGLWidget>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

#include "model.h"
#include "output.h"
#include "engine.h"

class SymmetryGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    Engine* engine;
    Model* model;
    Output* output;

    SymmetryGLWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void setModel(Model* m) { model = m; vtx = new GLfloat[model->pixels.size() * 3]; }
    void setOutput(Output* o) { output = o; col = new GLfloat[output->colorBuffer.size() * 4]; }
    float *vtx = 0;
    float *col = 0;
private:
    QMatrix4x4 m_projection;
    QOpenGLShaderProgram *m_program=0;
    QSize m_viewportSize;
    qreal m_t;
    void populateModel();
    void populateColors();
    void initializeScene();
};

#endif // WIDGET

