/*
  ==============================================================================

    OutputSimulationView.h
    Created: 3 Aug 2015 5:07:46pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef OUTPUTSIMULATIONJ_H_INCLUDED
#define OUTPUTSIMULATIONJ_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

#include <model.h>
#include <output.h>
#include <engine.h>
#include <observes.h>

#include "UiSession.h"

//==============================================================================
/*
*/
class OutputSimulationView : public Component, public OpenGLRenderer, private Observes
{
public:
    explicit OutputSimulationView(UiSession& session);
    ~OutputSimulationView();
    
    UiSession& session;
    Output& output;

private:
    
    OpenGLContext openGLContext;
    
    ScopedPointer<OpenGLShaderProgram> shader;
    
    ScopedPointer<OpenGLShaderProgram::Uniform> projectionMatrix;
    ScopedPointer<OpenGLShaderProgram::Uniform> viewMatrix;
    
    vector<float> vtx;
    vector<float> col;
    
    ScopedPointer<OpenGLShaderProgram::Attribute> vertices;
    ScopedPointer<OpenGLShaderProgram::Attribute> colors;
    
    void populateModel();
    void populateColors();
    void initializeScene();
    Matrix3D<float> getProjectionMatrix() const;
    Matrix3D<float> getViewMatrix() const;
    
    void paint (Graphics&) override;
    
    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OutputSimulationView)
};


#endif  // OUTPUTSIMULATIONJ_H_INCLUDED
