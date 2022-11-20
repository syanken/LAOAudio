/*
  ==============================================================================

    FxScreen.h
    Created: 8 Nov 2022 9:31:49pm
    Author:  QCWL

  ==============================================================================
*/

#pragma once
#include "LaoComponent.h"
#include <JuceHeader.h>
//==============================================================================

class SliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    SliderLookAndFeel() {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    };
    void drawLinearSlider(Graphics& g,
        int 	x,
        int 	y,
        int 	width,
        int 	height,
        float 	sliderPos,
        float 	minSliderPos,
        float 	maxSliderPos,
        const Slider::SliderStyle ,
        Slider& slider
    )override {
        g.setColour(Colours::red);
        g.fillRect(5.0f, (float)(sliderPos - ( sliderPos/300) * (300 -(slider.getMaximum()-4)* 300 / slider.getMaximum())), 20.0f, (float)(300 - (slider.getMaximum() - 4) * 300 / slider.getMaximum()));
        };
};

class Fx :public Component
{
public:
    Fx();
    ~Fx() override;
    void paint(juce::Graphics& g) override;
    bool fxstate;
    bool fxonstate;
    
    void initFx();
    StateButton fxstatebutton;
    MySlider mixslider;
    ComboBox savecb;
    //void inithyper();

private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Fx)

};

class FxScreen  : public juce::Component
{
public:
    FxScreen();
    void setvi(Fx*fx, StateButton* fxbutton);
    ~FxScreen() override;

    void paint (juce::Graphics& g) override;
    void resized() override;
    void initFxScreen();
    Fx fx1;
    Fx fx2;
    Fx fx3;
    Fx fx4;
    Fx fx5;    
    Fx fx6;
    Fx fx7;
    Fx fx8;
    Fx fx9;
    Fx fx10;
    StateButton fx1button;
    StateButton fx2button;
    StateButton fx3button;
    StateButton fx4button;
    StateButton fx5button;
    StateButton fx6button;
    StateButton fx7button;
    StateButton fx8button;
    StateButton fx9button;
    StateButton fx10button;

    Slider sliderscroll;
    int itemnum;
    double scrollpos;

    Array<Fx* > fxlist[10] = {};  
    Array<StateButton* > fxbuttonlist[10] = {  };
    SliderLookAndFeel sliderlookandfeel;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FxScreen)
};

