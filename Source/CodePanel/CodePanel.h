#pragma once

#include <JuceHeader.h>

#include "../EditorPanel/EditorPanel.h"

#include <string>

class CodePanel : public juce::Component, public EditorComponentListener {
    public:
        CodePanel(EditorPanel* editorPanel, float x, float y, float panelWidth, float panelHeight);

        std::string generateCodeForAllEditorComponents();

        virtual void paint(juce::Graphics& g) override;
        virtual void resized() override;

        virtual void onEditorComponentChange() override;

    private:
        float panelWidth;
        float panelHeight;

        juce::TextEditor codeBox;

        EditorPanel* editorPanel;
};