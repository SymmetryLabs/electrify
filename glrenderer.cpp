
#include "glrenderer.h"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLContext>

GLRenderer::GLRenderer()
    : m_t(0)
    , m_renderer(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void GLRenderer::setT(qreal t)
{
    if (t == m_t)
        return;
    m_t = t;
    emit tChanged();
    if (window())
        window()->update();
}

void GLRenderer::handleWindowChanged(QQuickWindow *win)
{
    if (win) {
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);
        connect(win, SIGNAL(sceneGraphInvalidated()), this, SLOT(cleanup()), Qt::DirectConnection);
        // If we allow QML to do the clearing, they would clear what we paint
        // and nothing would show.
        win->setClearBeforeRendering(false);
    }
}

void GLRenderer::cleanup()
{
    if (m_renderer) {
        delete m_renderer;
        m_renderer = 0;
    }
}

GLRendererRenderer::~GLRendererRenderer()
{
    delete m_program;
}

void GLRenderer::sync()
{
    if (!m_renderer) {
        m_renderer = new GLRendererRenderer();
        connect(window(), SIGNAL(beforeRendering()), m_renderer, SLOT(paint()), Qt::DirectConnection);
    }
    m_renderer->setViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setT(m_t);
}

void GLRendererRenderer::paint()
{
    if (!m_program) {
        initializeOpenGLFunctions();

        m_program = new QOpenGLShaderProgram();
        m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           "attribute highp vec4 vertices;"
                                           "uniform mat4 mvp_matrix;"
                                           "varying highp vec3 coords;"
                                           "void main() {"
                                           "    gl_Position = mvp_matrix * vertices;"
                                           "    coords = vertices.xyz;"
                                           "}");
        m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                           "varying highp vec3 coords;"
                                           "void main() {"
                                           "    gl_FragColor = vec4(coords.x,coords.y,coords.z,1.0);"
                                           "}");

        m_program->bindAttributeLocation("vertices", 0);
        m_program->link();

    }
    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
        -1.0,-1.0,-1.0, // triangle 1 : begin
                   -1.0,-1.0, 1.0,
                   -1.0, 1.0, 1.0, // triangle 1 : end
                   1.0, 1.0,-1.0, // triangle 2 : begin
                   -1.0,-1.0,-1.0,
                   -1.0, 1.0,-1.0, // triangle 2 : end
                   1.0,-1.0, 1.0,
                   -1.0,-1.0,-1.0,
                   1.0,-1.0,-1.0,
                   1.0, 1.0,-1.0,
                   1.0,-1.0,-1.0,
                   -1.0,-1.0,-1.0,
                   -1.0,-1.0,-1.0,
                   -1.0, 1.0, 1.0,
                   -1.0, 1.0,-1.0,
                   1.0,-1.0, 1.0,
                   -1.0,-1.0, 1.0,
                   -1.0,-1.0,-1.0,
                   -1.0, 1.0, 1.0,
                   -1.0,-1.0, 1.0,
                   1.0,-1.0, 1.0,
                   1.0, 1.0, 1.0,
                   1.0,-1.0,-1.0,
                   1.0, 1.0,-1.0,
                   1.0,-1.0,-1.0,
                   1.0, 1.0, 1.0,
                   1.0,-1.0, 1.0,
                   1.0, 1.0, 1.0,
                   1.0, 1.0,-1.0,
                   -1.0, 1.0,-1.0,
                   1.0, 1.0, 1.0,
                   -1.0, 1.0,-1.0,
                   -1.0, 1.0, 1.0,
                   1.0, 1.0, 1.0,
                   -1.0, 1.0, 1.0,
                   1.0,-1.0, 1.0
    };
    m_program->setAttributeArray(0, GL_FLOAT, values, 3);
    m_program->setUniformValue("t", (float) m_t);

    glViewport(0, 0, m_viewportSize.width(), m_viewportSize.height());
    glMatrixMode (GL_PROJECTION);
    glMatrixMode(GL_MODELVIEW);

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
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(45,0,1,0);
    m_program->setUniformValue("mvp_matrix", projection * matrix );

    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glDrawArrays(GL_TRIANGLES, 0, 12*3);





    m_program->disableAttributeArray(0);
    m_program->release();
}
