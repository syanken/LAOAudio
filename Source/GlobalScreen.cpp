/*
  ==============================================================================

    global.cpp
    Created: 12 Nov 2022 9:06:17pm
    Author:  QCWL
    Version: 0.1.20

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GlobalScreen.h"

//==============================================================================
GlobalScreen::GlobalScreen()
{
    chaos1.setBounds(40, 20, 60, 60);
    chaos2.setBounds(205, 20, 60, 60);

    addAndMakeVisible(chaos1);
    addAndMakeVisible(chaos2);

    for (int i = 0; i < 12; i++)
    {
        stb[i].setBounds(350, 22 * i + 30, 12, 12);
        addAndMakeVisible(stb[i]);
    }
}

GlobalScreen::~GlobalScreen()
{
}

void GlobalScreen::paint (juce::Graphics& g)
{
    g.setColour (juce::Colours::red);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.drawRect(0, 0, 330, 100);
    g.setFont(20.0f);
    g.drawText("chaos >>>>>>>>>>>>>>>>>>",20, 0, 300, 25,Justification::centredLeft);
    g.drawText("unison >>>>oscA>>>>oscB>>>>", 20, 100, 300, 25, Justification::centredLeft);
    g.drawText("preferences >>>>>>>>>>>>>>", 350, 0, 300, 25, Justification::centredLeft);
    g.drawText("osc settings >>>>>>>>>", 680, 0, 300, 25, Justification::centredLeft);

    g.setFont(14.0f);
    g.drawText("rate1", 40, 75, 60, 25, Justification::centred);
    g.drawText("rate2", 205, 75, 60, 25, Justification::centred);

    g.drawText("build 0.1.20   date 2022.11.20", 680, 250, 220, 30, Justification::centred);
    g.setFont(10.0f);
    g.drawText("(The last version of the first major version)", 660, 270, 260, 30, Justification::centred);

    g.drawRect(0, 100, 330, 200);

    g.drawRect(330, 0, 330, 300);

    g.drawRect(660, 0, 240, 150);
    g.drawRect(660, 150, 240, 150);    
    
    g.setFont(36.0f);
    g.drawText("LAOAudio", 680, 150, 220, 120, Justification::centred);

}

void GlobalScreen::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
