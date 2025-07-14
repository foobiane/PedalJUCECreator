#pragma once

#include <JuceHeader.h>

#include "../EditorPanel/EditorPanel.h"
#include "../EditorPanel/EditorComponents.h"

class OptionsPanel : public juce::Component, public SelectedComponentListener {
    public:
        OptionsPanel(EditorPanel* editorPanel, float x, float y, float panelWidth, float panelHeight);

        virtual void onSelectionChange() override;

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

    private:
        float panelWidth;
        float panelHeight;

        BasicEditorComponent* previouslySelectedComponent = nullptr;

        EditorPanel* editorPanel;
};