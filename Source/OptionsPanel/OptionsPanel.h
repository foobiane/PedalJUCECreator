#pragma once

#include <JuceHeader.h>

#include "../EditorPanel/EditorPanel.h"
#include "../EditorPanel/EditorComponents.h"

class OptionsPanel : public juce::Component, public SelectedComponentListener {
    public:
        OptionsPanel(EditorPanel* editorPanel, double x, double y, double panelWidth, double panelHeight);

        virtual void onSelectionChange() override;

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

    private:
        double panelWidth;
        double panelHeight;

        BasicEditorComponent* previouslySelectedComponent = nullptr;

        EditorPanel* editorPanel;
};