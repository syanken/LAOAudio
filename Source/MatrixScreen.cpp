/*
  ==============================================================================

    MatrixScreen.cpp
    Created: 8 Nov 2022 9:30:35pm
    Author:  QCWL

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MatrixScreen.h"
using namespace juce;
//==============================================================================
MatrixScreen::MatrixScreen()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    rightcb.setBounds(870, 0, 30, 30);
    rightcb.setText(">");

    addAndMakeVisible(rightcb);
    
    matrixarea.setBounds(0, 30, 900, 270);
    addAndMakeVisible(matrixarea);
}

MatrixScreen::~MatrixScreen()
{

}

void MatrixScreen::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::red);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
       
    g.drawRect(0,0,100,30, 1);  
    g.drawRect(100, 0, 40, 30,1);
    g.drawRect(140, 0, 170,30, 1);
    g.drawRect(310, 0, 170,30, 1);
    g.drawRect(480, 0, 40, 30,1);
    g.drawRect(520, 0, 60, 30,1);
    g.drawRect(580, 0, 100,30, 1);
    g.drawRect(680, 0, 40, 30,1);
    g.drawRect(720, 0, 150,30, 1);
    g.drawRect(870, 0, 30,30, 1);
    
    g.drawText("source",0, 0, 100, 30, Justification::centred);
    g.drawText("curve",100, 0, 40, 30,  Justification::centred);
    g.drawText("amount",140, 0, 170, 30,  Justification::centred);
    g.drawText("destination",310, 0, 170, 30, Justification::centred);
    g.drawText("type",480, 0, 40, 30, Justification::centred);
    g.drawText("mod",520, 0, 60, 30,Justification::centred);
    g.drawText("aux source",580, 0, 100, 30,  Justification::centred);
    g.drawText("curve",680, 0, 40, 30,  Justification::centred);
    g.drawText("output",720, 0, 150, 30,  Justification::centred);

    g.drawRect(870, 30, 30, 270, 1);
}

void MatrixScreen::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

Matrix::Matrix()
{
    StringArray sourcelist = { "---","1","2" };
    StringArray modlist = { "*","*(inv)","bypass" };
    StringArray auxsourcelist =  { "---", "1", "2" };
    num = 0;
    source.setBounds( 0, 0, 100, 33);
    amount.setBounds(140, 10, 170, 23);

    type.setBounds(480, 0, 40, 33);
    mod.setBounds(520, 0, 60, 33);
    auxsource.setBounds(580, 0, 100, 33);
    output.setBounds(720, 0, 150, 33);

    source.addItemList(sourcelist,1);
    auxsource.addItemList(auxsourcelist, 1);
    mod.addItemList(modlist, 1);

    amount.setRange(-100, 100, 0);
    output.setRange(0, 100, 0);
    amount.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    output.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    amount.setDoubleClickReturnValue(true, 0);
    output.setDoubleClickReturnValue(true, 100);
    amount.setNumDecimalPlacesToDisplay(1);
    output.setNumDecimalPlacesToDisplay(1);
    amount.setPopupDisplayEnabled(true, true, this->getParentComponent(), 2000);
    output.setPopupDisplayEnabled(true, true, this->getParentComponent(), 2000);
    amount.setLookAndFeel(&sliderlookandfeel3);
    output.setLookAndFeel(&sliderlookandfeel4);
    //---init
    source.setText("---");
    auxsource.setText("---");
    mod.setText("*");
    amount.setValue(0);
    output.setValue(100);
    type.setButtonText("->");
    //---
    type.onClick = [&] {
        if (type.getButtonText()== "->")
        {
            type.setButtonText("<->");
        }
        else
        {
            type.setButtonText("->");
        }
    };

    addAndMakeVisible(source);
    addAndMakeVisible(amount);
    addAndMakeVisible(type);
    addAndMakeVisible(mod);
    addAndMakeVisible(auxsource);
    addAndMakeVisible(output);
}

Matrix::~Matrix()
{
    amount.setLookAndFeel(nullptr);
    output.setLookAndFeel(nullptr);
}

void Matrix::paint(juce::Graphics& g)
{
    g.setColour(Colours::red);
    g.drawRect(getLocalBounds(), 1);
}

MatrixArea::MatrixArea()
{
    rightslider.setRange(0, 32, 0);
    rightslider.setValue(32);
    rightslider.setLookAndFeel(&sliderlookandfeel);

    rightslider.setBounds(870, 0, 30, 270);
    rightslider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    rightslider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);

    addAndMakeVisible(rightslider);

    for (int i = 0; i < 32; i++)
    {
        ma[i].num = i;
        ma[i].setBounds(0.0f,-33.0f * 24 * (1 - rightslider.getValue() / 32) + 33.0f * i, 870.0f, 33.0f);
        addAndMakeVisible(ma[i]);
    }
    rightslider.onValueChange = [this] {
        for (int i = 0; i < 32; i++)
        {
            ma[i].setBounds(0,  -33 * 24 * (1 - rightslider.getValue() / 32) + 33 * i, 870, 33);

        }
        repaint();
    };
}

MatrixArea::~MatrixArea()
{
    rightslider.setLookAndFeel(nullptr);

}
