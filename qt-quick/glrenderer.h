#ifndef GLRENDERER_H
#define GLRENDERER_H

#include <QtQuick/QQuickItem>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions>

class GLRendererRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLRendererRenderer() : m_t(0), m_program(0) { }
    ~GLRendererRenderer();

    void setT(qreal t) { m_t = t; }
    void setViewportSize(const QSize &size) { m_viewportSize = size; }

public slots:
    void paint();

private:
    QSize m_viewportSize;
    qreal m_t;
    QOpenGLShaderProgram *m_program;
};

class GLRenderer : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal t READ t WRITE setT NOTIFY tChanged)

public:
    GLRenderer();

    qreal t() const { return m_t; }
    void setT(qreal t);

signals:
    void tChanged();

public slots:
    void sync();
    void cleanup();

private slots:
    void handleWindowChanged(QQuickWindow *win);

private:
    qreal m_t;
    GLRendererRenderer *m_renderer;
};

#endif // GLRenderer_H