#pragma once
#include "FxScreen.h"
#include "MatrixScreen.h"
#include "LaoComponent.h"
#include "GlobalScreen.h"
#include"SoundsAndVoices.h"
#include <JuceHeader.h>
using namespace juce;

class ButtonDrawableRectangle :public Component
{
public:
    ButtonDrawableRectangle() {
        
    };   
    ButtonDrawableRectangle(int x, int y) {
        setBounds(x, y, 10, 10);
        getParentComponent()->addAndMakeVisible(this);
        //repaint();
    }
    void paint(Graphics& g) {
        g.setColour(Colours::black);
        g.drawRect(getLocalBounds());
        g.fillRect(getLocalBounds());

    }
   
};

class ButtonLookandFeel :public LookAndFeel_V4
{
public:
    ButtonLookandFeel() {
    };
    void drawButtonBackground(Graphics& g,
        Button& tb,
        const Colour& backgroundColour,
        bool 	shouldDrawButtonAsHighlighted,
        bool 	shouldDrawButtonAsDown
    )
    {
        g.setColour(Colours::red);
        g.drawRect(tb.getLocalBounds());
        
    }
};

class UnisonLookAndFeel : public juce::LookAndFeel_V4
{
public:
    UnisonLookAndFeel()
    {
        //setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }
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
    ) {
        g.setColour(Colours::red);
        g.drawRect(10,20,20,20);
        g.drawText(String(slider.getValue()), slider.getLocalBounds(),Justification::centred );
    }
};

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::red);
    }
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 10.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        g.setColour(juce::Colours::red);
        g.drawEllipse(rx, ry, rw, rw, 4.0f);

        juce::Path p;
        auto pointerLength = radius * 0.5f;
        auto pointerThickness = 4.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
        g.fillPath(p);

    }
    void drawComboBox(Graphics& g,
        int 	width,
        int 	height,
        bool 	isButtonDown,
        int 	buttonX,
        int 	buttonY,
        int 	buttonW,
        int 	buttonH,
        ComboBox& combobox
    ) {
        g.setColour(Colours::red);
        g.drawRect(combobox.getLocalBounds());
        g.drawText(combobox.getText(), combobox.getLocalBounds(), Justification::centred);

    }
};

class EnvScreen :public Component {
public:
    EnvScreen();
    ~EnvScreen();
    void paint(juce::Graphics& g) override;
    Point<float> p1;
    Point<float> p2;
    Point<float> p3;
    Point<float> p4;
    Point<float> p5;

    Point<float> m1;
    Point<float> m2;
    Point<float> m3;
    Point<float> m4;

    int length;
    float lastpoint ;
    StateButton lockbutton;
    Slider envlenght;

    MySlider attack;
    MySlider hold;
    MySlider decay;
    MySlider sustain;
    MySlider release;
    Array<Point<float>*> pointlist[1];
    Array<Point<float>*> midlist[1];

    float envFunction(float x, float index);

    void mouseDown(const MouseEvent& event)override;
    void mouseDrag(const MouseEvent& event)override;
    void initEnvScreen();

    float dis;
    int pnum;
    float midindex[4] = {1};
private:

};

class Noise :public Component
{
public:
    Noise();
    void initNoise();
    ~Noise();
    StateButton statebutton;

    StateButton obutton;
    StateButton kbutton;

    ComboBox noisecb;

    MySlider phase;
    MySlider rand;
    MySlider pitch;
    MySlider pan;
    MySlider level;
    TextButton leftbutton;
    TextButton rightbutton;
    ButtonLookandFeel buttonlookandfeel;
    void paint(juce::Graphics& g) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Noise)

};

class Sub :public Component
{
public:
    Sub();
    void initSub();
    ~Sub();
    StateButton statebutton;

    MySlider octave;
    MySlider pan;
    MySlider level;

    UnisonLookAndFeel unisonlookandfeel;

    void paint(juce::Graphics& g) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sub)

};

class Filter :public Component
{
public:
    Filter();
    ~Filter();
    void paint(juce::Graphics& g) override;

    bool filterstate;
    void initFilter();
    TextButton leftbutton;
    TextButton rightbutton;
    StateButton statebutton;
    ComboBox filtercb;

    MySlider cutoff;
    MySlider res;
    MySlider pan;
    MySlider drive;
    MySlider fat;
    MySlider mix;

    StateButton oscAstate;
    StateButton oscBstate;
    StateButton substate;
    StateButton noisestate;
    StateButton keyboardstate;

    ButtonLookandFeel buttonlookandfeel;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Filter)
};

class Osc :public juce::Component
{
public:
    Osc();

    ~Osc();
   // int posArr[6] = { 160 ,442,722, 10,10,130 };
    void initosc();
    void drawOscSin(juce::Graphics& g);
    void drawOscTri(juce::Graphics& g);
    void drawOscSqu(juce::Graphics& g);
    void drawOscNoi(juce::Graphics& g);
    void paint(juce::Graphics& g) override;
    void setoscnum(int oscnum);
    void setoscwavenum(int oscwavenum);
    int getoscnum(); 
    int getoscwavenum();
    void drawOscWave( juce::Graphics& g);
    void drawDutune(juce::Graphics& g);

    void setOscItemVisible();
    void StateButtonEvent();
    void detuneEvent();
    bool oscstate;
    bool showdetune;
    double oscdetune;
    MySlider volumeslider;
    MySlider panslider;
    MySlider detune;
    MySlider blend;
    MySlider phase;
    MySlider rand;
    TextButton leftbutton;
    TextButton rightbutton;

    StateButton statebutton;
    ComboBox osccb;
    StringArray itemlist;

    Slider unison;
    Slider octave;
    Slider semitones;
    Slider cents;
    Slider coarsepits;
    UnisonLookAndFeel unisonlookandfeel;
    ButtonLookandFeel buttonlookandfeel;
private:
    int oscnum;
    int oscwavenum;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Osc)
};

class OscScreen : public juce::Component
{
public:
    OscScreen();
    ~OscScreen();
    void paint(Graphics& g)override;

    //Osc sub;
    //Osc noise;
    Osc oscA;
    Osc oscB;
    Sub sub;
    Noise noise;
    Filter filter;

private:
    StateButton substatebutton;
    StateButton noisestatebutton;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OscScreen)
};

class SynthAudioSource : public juce::AudioSource
{
public:
    SynthAudioSource(juce::MidiKeyboardState& keyState)
        : keyboardState(keyState)
    {
        
        for (auto i = 0; i < 1; ++i)                // [1]
            synth.addVoice(new SineWaveVoice());
        
        synth.addSound(new SineWaveSound());       // [2]
    }
    void prepareToPlay(int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        synth.setCurrentPlaybackSampleRate(sampleRate); // [3]
    }
    //void setUsingSineWaveSound()
    //{
    //    synth.clearSounds();
    //}
    void releaseResources() override {}

    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override
    {
        bufferToFill.clearActiveBufferRegion();

        juce::MidiBuffer incomingMidi;
        keyboardState.processNextMidiBuffer(incomingMidi, bufferToFill.startSample,
            bufferToFill.numSamples, true);       // [4]

        synth.renderNextBlock(*bufferToFill.buffer, incomingMidi,
            bufferToFill.startSample, bufferToFill.numSamples); // [5]
    }
    void changeSoundandVoice(int globaloscindex ) {           
        synth.clearSounds();
        synth.clearVoices();
        switch (globaloscindex)
        {
        case 0:
            for (auto i = 0; i < 1; ++i)                // [1]
                synth.addVoice(new SineWaveVoice());

            synth.addSound(new SineWaveSound());
            break;        
        case 1:
            for (auto i = 0; i < 1; ++i)                // [1]
                synth.addVoice(new TriWaveVoice());

            synth.addSound(new TriWaveSound());
            break;        
        case 2:
            for (auto i = 0; i < 1; ++i)                // [1]
                synth.addVoice(new SquWaveVoice());

            synth.addSound(new SquWaveSound());
            break;
        case  3:
                for (auto i = 0; i < 1; ++i)                // [1]
                    synth.addVoice(new SquWaveVoice());

                synth.addSound(new SquWaveSound());
                for (auto i = 0; i < 1; ++i)                // [1]
                    synth.addVoice(new TriWaveVoice());

                synth.addSound(new TriWaveSound());
                synth.addVoice(new SineWaveVoice());

                synth.addSound(new SineWaveSound());
                break;
        default:
            break;
        }
    }
    Synthesiser synth;
private:
    MidiKeyboardState& keyboardState;

};

class MainComponent  : public juce::AudioAppComponent, private juce::Timer
{
public:
    //==============================================================================
    MainComponent();
    void initAll();

    ~MainComponent() override;
    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;

    void drawMainVolume(juce::Graphics& g);

     void resized() override;
     MySlider mainvolume;
     ComboBox menu;    
     ComboBox loadmenu;
     TextButton savebutton;
     BarButton oscbutton;
     BarButton fxbutton;
     BarButton matrixbutton;
     BarButton globalbutton;
     BarButton env1button;
     BarButton env2button;
     BarButton env3button;
     ButtonLookandFeel btlookandfeel;
     OtherLookAndFeel otherLookAndFeel;
     Label  testlabel;

     OscScreen oscscreen;
     FxScreen fxscreen;
     MatrixScreen matrixscreen;
     GlobalScreen globalscreen;

     EnvScreen env1;
     EnvScreen env2;
     EnvScreen env3;

     TextButton leftbutton;
     TextButton rightbutton;
private:
    void timerCallback() override
    {
        keyboardComponent.grabKeyboardFocus();
        stopTimer();
    }
    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;
    SynthAudioSource synthAudioSource;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

