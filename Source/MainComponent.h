#pragma once

#include <JuceHeader.h>

#include "Editor/EditorPanel.h"

#include <string>

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 400;

class MainComponent : public juce::Component {
    public:
        MainComponent();
        ~MainComponent() override;

        void paint (juce::Graphics&) override;
        void resized() override;

        EditorPanel editorPanel;

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
