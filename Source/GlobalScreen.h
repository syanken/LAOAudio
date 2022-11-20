/*
  ==============================================================================

    global.h
    Created: 12 Nov 2022 9:06:17pm
    Author:  QCWL
    Version: 0.1.20

  ==============================================================================
*/

#pragma once
#include "LaoComponent.h"
#include <JuceHeader.h>

//==============================================================================
/*
*/
class GlobalScreen : public juce::Component
{
public:
    GlobalScreen();
    ~GlobalScreen() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    MySlider chaos1;
    MySlider chaos2;

    StateButton stb[12];

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GlobalScreen)
};
