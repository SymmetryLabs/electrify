/*
  ==============================================================================

    ProjectDocument.h
    Created: 12 Oct 2015 5:40:11pm
    Author:  Kyle Fleming

  ==============================================================================
*/

#ifndef PROJECTDOCUMENT_H_INCLUDED
#define PROJECTDOCUMENT_H_INCLUDED

#include "BlueprintUiGlobals.h"

class Model;
class BlueprintProject;

class UiSession;

//==============================================================================
/*
 This class implements the desktop window that contains an instance of
 our MainContentNode class.
 */
class ProjectDocument : public FileBasedDocument {

public:
    explicit ProjectDocument(UiSession& session);

    void loadNew();
    void loadDemoDocument();

protected:
    String getDocumentTitle() override;
    Result loadDocument(const File& file) override;
    Result saveDocument(const File& file) override;
    File getLastDocumentOpened() override;
    void setLastDocumentOpened(const File& file) override;
    
private:
    UiSession& session;

    unique_ptr<Model> createModel() const;
    unique_ptr<BlueprintProject> createNewProject() const;
    unique_ptr<BlueprintProject> createDemoProject() const;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ProjectDocument)
};

#endif  // PROJECTDOCUMENT_H_INCLUDED
