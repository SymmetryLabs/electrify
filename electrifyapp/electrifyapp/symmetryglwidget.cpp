#include "symmetryglwidget.h"

SymmetryGLWidget::SymmetryGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    setFormat(format);
}
 
void SymmetryGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
}

void SymmetryGLWidget::populateModel()
{
    int i =0;
    for(auto p: model->pixels)
    {
        vtx[i++] = (float) p->x;
        vtx[i++] = (float) p->y;
        vtx[i++] = (float) p->z;
    }
}

void SymmetryGLWidget::populateColors()
{
    int i = 0;
    for(auto c: output->colorBuffer)
    {
        col[i++] = (float) (((c.asRGBA() >> 24) & 255) / 255.0);
        col[i++] = (float) (((c.asRGBA() >> 16) & 255) / 255.0);
        col[i++] = (float) (((c.asRGBA() >> 8) & 255) / 255.0);
        col[i++] = 255.0;
    }
}
 
void SymmetryGLWidget::resizeGL(int w, int h)
{
    m_projection.setToIdentity();
    m_projection.perspective(60.0f, w / float(h), 0.01f, 1000.0f);
}

void SymmetryGLWidget::initializeScene()
{
    initializeOpenGLFunctions();

    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "uniform mat4 mvp_mat;"
                                       "attribute highp vec4 vertices;"
                                       "attribute highp vec4 colors;"
                                       "varying highp vec4 cols;"
                                       "void main() {"
                                       "    gl_Position = mvp_mat * vertices;"
                                       "    cols = colors;"
                                       "}");
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                       "varying highp vec4 cols;"
                                       "void main() {"
                                       "    gl_FragColor = cols;"
                                       "}");

    m_program->bindAttributeLocation("vertices", 0);
    m_program->bindAttributeLocation("colors", 1);
    m_program->link();

    m_program->bind();

    populateModel();

    m_program->setAttributeArray(0, GL_FLOAT, vtx, 3);
    m_program->setAttributeArray(1, GL_FLOAT, col, 4);
    m_program->enableAttributeArray(0);
    m_program->enableAttributeArray(1);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glMatrixMode (GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);
}
 
void SymmetryGLWidget::paintGL()
{
     if (!m_program) {
       initializeScene();
    }

    populateColors();

    // Calculate aspect ratio
    qreal aspect = qreal(m_viewportSize.width()) / qreal( m_viewportSize.height() ?  m_viewportSize.height() : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    QMatrix4x4 projection;
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);

    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(m_t, 0, 1, 0);
    m_t++;
    m_program->setUniformValue(0, projection * matrix );

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(5);
    glDrawArrays(GL_POINTS, 0, model->pixels.size());
}
