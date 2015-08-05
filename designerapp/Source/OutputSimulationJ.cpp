/*
  ==============================================================================

    OutputSimulationJ.cpp
    Created: 3 Aug 2015 5:07:46pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "OutputSimulationJ.h"

//==============================================================================
OutputSimulationJ::OutputSimulationJ(Engine* engine, EngineUi* engineUi, Output* output)
: engine(engine)
, engineUi(engineUi)
, output(output)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    model = engine->getModel();
    vtx = new GLfloat[model->pixels.size() * 3];
    col = new GLfloat[output->colorBuffer.size() * 4];
    
    setOpaque (true);
    openGLContext.setRenderer (this);
    openGLContext.attachTo (*this);
    openGLContext.setContinuousRepainting (true);
    
    populateModel();
}

OutputSimulationJ::~OutputSimulationJ()
{
    openGLContext.detach();
}

void OutputSimulationJ::populateModel()
{
    int i = 0;
    for(auto p : model->pixels) {
        vtx[i++] = (float) p->x;
        vtx[i++] = (float) p->y;
        vtx[i++] = (float) p->z;
    }
}

void OutputSimulationJ::populateColors()
{
    engine->copyColorBuffer(output->colorBuffer);
    
    int i = 0;
    for(auto c : output->colorBuffer) {
        col[i++] = (float) (((c.asRGBA() >> 24) & 255) / 255.0);
        col[i++] = (float) (((c.asRGBA() >> 16) & 255) / 255.0);
        col[i++] = (float) (((c.asRGBA() >> 8) & 255) / 255.0);
        col[i++] = 255.0;
    }
}

void OutputSimulationJ::initializeScene()
{
    shader = new OpenGLShaderProgram(openGLContext);
    shader->addVertexShader(
                               "attribute vec4 vertices;"
                               "attribute vec4 colors;"
                               "\n"
                               "uniform mat4 projectionMatrix;\n"
                               "uniform mat4 viewMatrix;\n"
                               "\n"
                               "varying vec4 cols;"
                               "\n"
                               "void main() {"
                               "    gl_Position = projectionMatrix * viewMatrix * vertices;"
                               "    cols = colors;"
                               "}");
    shader->addFragmentShader("varying vec4 cols;"
                                 "\n"
                                 "void main() {"
                                 "    gl_FragColor = cols;"
                                 "}");
    
    shader->link();
    
    openGLContext.extensions.glGetUniformLocation(shader->getProgramID(), "projectionMatrix");
    projectionMatrix = new OpenGLShaderProgram::Uniform(*shader, "projectionMatrix");
    
    openGLContext.extensions.glGetUniformLocation(shader->getProgramID(), "viewMatrix");
    viewMatrix = new OpenGLShaderProgram::Uniform(*shader, "viewMatrix");
    
    openGLContext.extensions.glGetAttribLocation (shader->getProgramID(), "vertices");
    vertices = new OpenGLShaderProgram::Attribute (*shader, "vertices");
    
    openGLContext.extensions.glGetAttribLocation (shader->getProgramID(), "colors");
    colors = new OpenGLShaderProgram::Attribute (*shader, "colors");
}

Matrix3D<float> OutputSimulationJ::getProjectionMatrix() const
{
    float w = 1.0f / (0.5f + 0.1f);
    float h = w * getLocalBounds().toFloat().getAspectRatio (false);
    return Matrix3D<float>::fromFrustum (-w, w, -h, h, 4.0f, 1000.0f);
}

Matrix3D<float> OutputSimulationJ::getViewMatrix() const
{
    Matrix3D<float> viewMatrix (Vector3D<float> (0.0f, 0.0f, -10.0f));
    Matrix3D<float> rotationMatrix
    = viewMatrix.rotated (Vector3D<float> (-0.3f, 3.14 * 3 / 4, 0.0f));
    
    return rotationMatrix * viewMatrix;
}

#pragma mark - Component

void OutputSimulationJ::paint (Graphics& g)
{
}

#pragma mark - OpenGLRenderer

void OutputSimulationJ::newOpenGLContextCreated()
{
    initializeScene();
}

void OutputSimulationJ::renderOpenGL()
{
    populateColors();
    
    glDisable(GL_DEPTH_TEST);
    
    OpenGLHelpers::clear (Colours::black);
    glClear(GL_COLOR_BUFFER_BIT);
    
    const float desktopScale = (float) openGLContext.getRenderingScale();
    glViewport (0, 0, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()));
    
    shader->use();
    
    projectionMatrix->setMatrix4(getProjectionMatrix().mat, 1, false);
    viewMatrix->setMatrix4(getViewMatrix().mat, 1, false);
    
    openGLContext.extensions.glVertexAttribPointer (vertices->attributeID, 3, GL_FLOAT, GL_FALSE, 0, vtx);
    openGLContext.extensions.glEnableVertexAttribArray (vertices->attributeID);
    
    openGLContext.extensions.glVertexAttribPointer (colors->attributeID, 4, GL_FLOAT, GL_FALSE, 0, col);
    openGLContext.extensions.glEnableVertexAttribArray (colors->attributeID);
    
    glPointSize(5);
    glDrawArrays(GL_POINTS, 0, model->pixels.size());
    
    openGLContext.extensions.glDisableVertexAttribArray (vertices->attributeID);
    openGLContext.extensions.glDisableVertexAttribArray (colors->attributeID);
    
    openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, 0);
    openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
}

void OutputSimulationJ::openGLContextClosing()
{
    shader = nullptr;
    projectionMatrix = nullptr;
    viewMatrix = nullptr;
    vertices = nullptr;
    colors = nullptr;
}
