#pragma once

#include <JuceHeader.h>

#include "EditorPanel/EditorPanel.h"
#include "OptionsPanel/OptionsPanel.h"
#include "CodePanel/CodePanel.h"

#include <string>

const double WINDOW_WIDTH = 1200;
const double WINDOW_HEIGHT = 600;

class MainComponent : public juce::Component {
    public:
        MainComponent();
        ~MainComponent() override;

        void paint (juce::Graphics&) override;
        void resized() override;

        EditorPanel editorPanel;
        OptionsPanel optionsPanel;
        CodePanel codePanel;

        juce::Viewport optionsPanelViewport;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
