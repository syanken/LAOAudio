/*
  ==============================================================================

    LaoComponent.h
    Created: 9 Nov 2022 3:30:34pm
    Author:  QCWL
    Version: 0.1.20

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;
//==============================================================================
class LaoComponent  : public juce::Component
{
public:
    LaoComponent()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~LaoComponent() override
    {
    }

    void paint (juce::Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (juce::Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (juce::Colours::white);
        g.setFont (14.0f);
        g.drawText ("LaoComponent", getLocalBounds(),
                    juce::Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LaoComponent)
};

class MySlider :public Slider
{
public:
    MySlider() {
        setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
        setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 50, 20);
        setPopupDisplayEnabled(true, true, this->getParentComponent(), 2000);
    };
    ~MySlider() {};
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MySlider)
};

class StateButton :public TextButton
{
public:
    StateButton() {
        onClick = [=] {
            if (buttonstate) {
                buttonstate = false;
            }
            else {
                buttonstate = true;
            }
        };
    };

    ~StateButton() {};

    bool buttonstate;
    void paint(Graphics& g) {
        if (buttonstate) {
            g.setColour(Colours::red);
            g.fillRect(getLocalBounds());
        }
        else {
            g.setColour(Colours::green);
            g.fillRect(getLocalBounds());
        }
    };

private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(StateButton)
};

class BarButton :public TextButton
{
public:
    BarButton() {};
    ~BarButton() {};
    bool state;
    void paint(Graphics& g) {
        if (state) {
            g.setColour(Colours::red);
            g.fillRect(getLocalBounds());
            g.drawRect(getLocalBounds());
            g.setColour(Colours::white);
            g.drawText(getName(), getLocalBounds(), Justification::centred);
        }
        else
        {
            g.setColour(Colours::white);
            g.fillRect(getLocalBounds());
            g.setColour(Colours::red);
            g.drawText(getName(), getLocalBounds(), Justification::centred);
            g.drawRect(getLocalBounds());
        }
    };
};