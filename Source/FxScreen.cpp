/*
  ==============================================================================

    FxScreen.cpp
    Created: 8 Nov 2022 9:31:49pm
    Author:  QCWL

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FxScreen.h"
//==========

FxScreen::FxScreen()
{

    scrollpos = 1;
    String list[10] = { "hyper","distortion","flanger","phaser","chorus","delay","compressor","reverb","eq","filter" };
    fxlist->add(&fx1);
    fxlist->add(&fx2);
    fxlist->add(&fx3); 
    fxlist->add(&fx4);
    fxlist->add(&fx5);
    fxlist->add(&fx6);
    fxlist->add(&fx7);
    fxlist->add(&fx8);
    fxlist->add(&fx9);
    fxlist->add(&fx10);
    fxbuttonlist->add(&fx1button);
    fxbuttonlist->add(&fx2button);
    fxbuttonlist->add(&fx3button);
    fxbuttonlist->add(&fx4button);
    fxbuttonlist->add(&fx5button);
    fxbuttonlist->add(&fx6button);
    fxbuttonlist->add(&fx7button);
    fxbuttonlist->add(&fx8button);
    fxbuttonlist->add(&fx9button);
    fxbuttonlist->add(&fx10button);

    sliderscroll.setLookAndFeel(&sliderlookandfeel);
    sliderscroll.setBounds(860, 0, 40, 300);
    sliderscroll.setSliderStyle(Slider::SliderStyle::LinearVertical);
    sliderscroll.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    sliderscroll.setRange(0, 1, 0);
    sliderscroll.setValue(sliderscroll.getMaximum());
    sliderscroll.onValueChange = [this] {

        scrollpos = sliderscroll.getValue();
        itemnum = 0;
        for (int j = 0; j < 10; j++)
        {
            if (fxlist->operator[](j)->fxonstate) {
                itemnum++;
            }
        }

        int index = 0;
        for (int j = 0; j < 10; j++)
        {
            if (fxlist->operator[](j)->fxonstate) {
                fxlist->operator[](j)->setBounds(180, -75 * (1 - scrollpos/ sliderscroll.getMaximum()) * (itemnum - 4) +75* index, 680, 75);
                fxlist->operator[](j)->setVisible(true);
                index++;
            }
        }
        repaint();
    };
    addChildComponent(sliderscroll);

    for (int i = 0;i<10; i++)
    {
        addChildComponent(fxlist->operator[](i));
        fxlist->operator[](i)->setName(list[i]);
        fxlist->operator[](i)->savecb.setText(fxlist->operator[](i)->getName());
        fxbuttonlist->operator[](i)->setBounds(20,18 + i * 28, 20, 12);
        fxbuttonlist->operator[](i)->buttonstate = false;
        addAndMakeVisible(fxbuttonlist->operator[](i));
        fxbuttonlist->operator[](i)->onClick = [=] {
            setvi(fxlist->operator[](i), fxbuttonlist->operator[](i));
            int num = 0;
            for (int j = 0; j < 10; j++)
            {
                if (fxlist->operator[](j)->fxonstate) {
                    num++;
                }
            }
            if (num > 4)
            {
                sliderscroll.setVisible(true);
                scrollpos = sliderscroll.getValue();
                sliderscroll.setRange(0,num , 0);
            }
            else {
                sliderscroll.setVisible(false);
                scrollpos = 1;
                sliderscroll.setRange(0, 1, 0);
            }
            int index = 0;
            for (int j = 0; j<10;j++)
            {
                if (fxlist->operator[](j)->fxonstate) {
                    fxlist->operator[](j)->setBounds(180, -75 * (1- scrollpos/sliderscroll.getMaximum())* (num-4) + 75 * index, 680, 75);
                    fxlist->operator[](j)->setVisible(true);    
                    index++;
                }
                repaint();
            }
        };
    }

    fxlist->operator[](8)->mixslider.setVisible(false);
}

void FxScreen::setvi(Fx *fx,StateButton* fxbutton)
{
    if (fx->isVisible())
    {
        fx->setVisible(false);
        fx->fxonstate = false;
        fxbutton->buttonstate = false;
    }
    else {
        fx->setVisible(true);
        fx->fxonstate = true;
        fxbutton->buttonstate = true;
    }
}

FxScreen::~FxScreen()
{  
    sliderscroll.setLookAndFeel(nullptr);
}

void FxScreen::paint (juce::Graphics& g)
{
    String list[10] = { "hyper/dimension","distortion","flanger","phaser","chorus","delay","compressor","reverb","eq","filter" };
    g.setColour(juce::Colours::red);

    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.drawRect(0,0,180,300);
    g.drawRect(10, 10, 160, 280);
    for (int i = 0; i < 10; i++)
    {
        
        g.drawRect(10, 10 + i * 28, 160, 28);
        g.drawText(list[i], 45, 10 + i * 28, 130, 28, Justification::left);
    }
 
    g.drawRect(860, 0, 40, 300);

    //g.drawText(String(getWidth()), 500, 200, 100, 100,Justification::centred);
}

void FxScreen::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}

void FxScreen::initFxScreen()
{
    scrollpos = 1;
    sliderscroll.setValue(1);
    sliderscroll.setVisible(false);
    for (int  i = 0; i < 10; i++)
    {
        fxlist->operator[](i)->initFx();
        fxlist->operator[](i)->setVisible(false);
        fxbuttonlist->operator[](i)->buttonstate = false;
    }
    repaint();
}

Fx::Fx()
{   
    initFx();
    fxstatebutton.setBounds(655,25,25,25);

    savecb.setBounds(0, 25, 100, 25);
    savecb.addItem("save this effect setting...", 1);
    savecb.setColour(juce::ComboBox::textColourId, juce::Colour((uint8)111, 111, 111, 0.0f));

    savecb.onChange = [=] {
        savecb. setText(getName(),Justification::left);
    };
    addAndMakeVisible(savecb);

    mixslider.setBounds(590, 0, 60, 60);
    mixslider.setRange(0, 100, 0);
    //mixslider.setDoubleClickReturnValue(true, 70.0);
    mixslider.setNumDecimalPlacesToDisplay(0);
    addAndMakeVisible(mixslider);

    addAndMakeVisible(fxstatebutton);
    fxstatebutton.onClick = [this]() {
        if (fxstate) {
            fxstate = false;
            fxstatebutton.buttonstate = false;
            repaint();
        }
        else {
            fxstate = true;
            fxstatebutton.buttonstate = true;
            repaint();
        }
    };
}

Fx::~Fx()
{
   
}

void Fx::paint(juce::Graphics& g)
{
    if (!fxstate) {
        g.fillAll(Colour(111, 111, 111));
    }
    g.setColour(Colours::red);
    g.drawRect(getLocalBounds(), 1);

    if (getName()!="eq") {
        g.drawText("mix", 590, 55, 60, 20, Justification::centred);
    }
}

void Fx::initFx()
{
    fxstate = true;
    fxonstate = false;       
    fxstatebutton.buttonstate = true;
}
