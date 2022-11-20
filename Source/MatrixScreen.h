/*
  ==============================================================================

    MatrixScreen.h
    Created: 8 Nov 2022 9:30:35pm
    Author:  QCWL
    Version: 0.1.20

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
using namespace juce;
//==============================================================================
/*
*/
class SliderLookAndFeel4 : public juce::LookAndFeel_V4
{
public:
    SliderLookAndFeel4() {
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
        const Slider::SliderStyle,
        Slider& slider
    )override {
        g.setColour(Colours::lightgrey);
        g.fillRect(x, y + 12, width, 4);
        g.setColour(Colours::red);
        g.fillRect(-10 + sliderPos, (float)(y + 9), 20.0f, 10.0f);
        g.setColour(Colours::green);
        if (slider.getValue()!=100)
        {
            g.fillRect((float)x, (float)y + 12, sliderPos-12, 4.0f);
        }
    };
};

class SliderLookAndFeel3 : public juce::LookAndFeel_V4
{
public:
    SliderLookAndFeel3() {
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
        const Slider::SliderStyle,
        Slider& slider
    )override {
        g.setColour(Colours::lightgrey);
        g.fillRect(x,y+12,width,4);
        g.setColour(Colours::red);
        g.fillRect(-10 + sliderPos , (float)(y+9), 20.0f, 10.0f);
        g.setColour(Colours::green);
        Path p;
        p.startNewSubPath(x + width / 2, y + 12);
        p.lineTo(x + sliderPos-11, y + 12);
        p.lineTo(x + sliderPos-11, y + 16);
        p.lineTo(x + width / 2, y + 16);
        p.lineTo(x + width / 2, y + 12);
        g.fillPath(p);
    };
};

class SliderLookAndFeel2 : public juce::LookAndFeel_V4
{
public:
    SliderLookAndFeel2() {
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
        const Slider::SliderStyle,
        Slider& slider
    )override {
        g.setColour(Colours::red);
        g.fillRect(5.0f, (float)(sliderPos - (sliderPos / 300) * 75), 20.0f, 72.0f);
    };
};

class Matrix : public juce::Component
{
public:
    Matrix();
    ~Matrix() override;
    int num;
    void paint(juce::Graphics&) override;
    
    
    ComboBox source;

    Slider amount;
    TextButton type;
    ComboBox mod;
    ComboBox auxsource;
    Slider output;
    SliderLookAndFeel3 sliderlookandfeel3;
    SliderLookAndFeel4 sliderlookandfeel4;
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Matrix)
};

class MatrixArea :public juce::Component
{
public:
    MatrixArea();
    ~MatrixArea() override;
    Matrix ma[32];
    
    Slider rightslider;
    SliderLookAndFeel2 sliderlookandfeel;
private:

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MatrixArea)

};
class MatrixScreen  : public juce::Component
{
public:
    MatrixScreen();
    ~MatrixScreen() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    ComboBox rightcb;

    MatrixArea matrixarea;


    //Matrix voidma;
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MatrixScreen)
};
