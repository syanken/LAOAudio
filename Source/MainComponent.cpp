
#include "MainComponent.h"
#include<cmath>
using namespace juce;
//==============================================================================
OscScreen::OscScreen()
{
    oscA.setBounds(150, 0, 280, 300);
    oscA.setName("oacA");
    oscA.setoscnum(0);
    oscA.initosc();
    oscB.setBounds(430, 0, 280, 300);
    oscB.setoscnum(1);
    oscB.initosc();
    oscB.setName("oacB");

    sub.setBounds(0, 0, 150, 130);
    filter.setBounds(710, 0, 190, 300);
    noise.setBounds(0, 130, 150, 170);

    addAndMakeVisible(oscA);
    addAndMakeVisible(oscB);
    addAndMakeVisible(filter);
    addAndMakeVisible(sub);
    addAndMakeVisible(noise);
    oscA.detuneEvent();
    oscB.detuneEvent();
    oscA.StateButtonEvent();
    oscB.StateButtonEvent();
}

OscScreen::~OscScreen()
{
}

MainComponent::MainComponent(): 
    synthAudioSource(keyboardState),
    keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    setSize (900, 728);
    startTimer(400);
    setLookAndFeel(&otherLookAndFeel);

    oscbutton.setBounds(150, 0, 70, 70);
    oscbutton.setName("osc");
    fxbutton.setBounds(220, 0, 70, 70);
    fxbutton.setName("fx");
    matrixbutton.setBounds(290, 0, 70, 70);
    matrixbutton.setName("matrix");
    globalbutton.setBounds(360, 0, 70, 70);
    globalbutton.setName("global");
    oscbutton.state = true;
    fxbutton.state = false;
    globalbutton.state = false;
    matrixbutton.state = false;
    oscbutton.onClick = [&] {if (!oscscreen.isVisible())
    {
        oscscreen.setVisible(true);
        fxscreen.setVisible(false);
        matrixscreen.setVisible(false);
        globalscreen.setVisible(false);
        oscbutton.state = true;
        fxbutton.state = false;
        globalbutton.state = false;
        matrixbutton.state = false;
        repaint();
    }
    };
    fxbutton.onClick = [&] {if (!fxscreen.isVisible())
    {
        fxscreen.setVisible(true);
        oscscreen.setVisible(false);
        matrixscreen.setVisible(false);
        globalscreen.setVisible(false); 
        fxbutton.state = true;
        oscbutton.state = false;
        globalbutton.state = false;
        matrixbutton.state = false;
        repaint();
    }
    };
    matrixbutton.onClick = [&] {if (!matrixscreen.isVisible())
    {
        matrixscreen.setVisible(true);
        oscscreen.setVisible(false);
        fxscreen.setVisible(false);
        globalscreen.setVisible(false);
        fxbutton.state = false;
        oscbutton.state = false;
        globalbutton.state = false;
        matrixbutton.state = true;
        repaint();
    }
    };
    globalbutton.onClick = [&] {if (!globalscreen.isVisible())
    {
        globalscreen.setVisible(true);
        oscscreen.setVisible(false);
        fxscreen.setVisible(false);
        matrixscreen.setVisible(false);
        fxbutton.state = false;
        oscbutton.state = false;
        globalbutton.state = true;
        matrixbutton.state = false;
        repaint();
    }
    };
    addAndMakeVisible(oscbutton);
    addAndMakeVisible(fxbutton);
    addAndMakeVisible(matrixbutton);
    addAndMakeVisible(globalbutton);

    oscscreen.setBounds(0, 70,900,300);
    fxscreen.setBounds(0, 70, 900, 300);
    matrixscreen.setBounds(0, 70, 900, 300);
    globalscreen.setBounds(0, 70, 900, 300);
   
    addAndMakeVisible(oscscreen);
    addChildComponent(fxscreen);
    addChildComponent(matrixscreen); 
    addChildComponent(globalscreen);
    loadmenu.setBounds(465, 0, 210, 35);
    loadmenu.setText("--init--");
    addAndMakeVisible(loadmenu);
    savebutton.setBounds(430, 0, 35, 35);
    savebutton.setButtonText("s");
    savebutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);
    savebutton.setLookAndFeel(&btlookandfeel);

    rightbutton.setBounds(700, 0, 25, 35);
    leftbutton.setBounds(675, 0, 25, 35);
    leftbutton.setButtonText("<");
    leftbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);
    rightbutton.setButtonText(">");
    rightbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);
    rightbutton.setLookAndFeel(&btlookandfeel);
    leftbutton.setLookAndFeel(&btlookandfeel);
    addAndMakeVisible(savebutton);
    addAndMakeVisible(rightbutton);
    addAndMakeVisible(leftbutton);

    StringArray menulist = { "init LAoAudio","exit"};
    menu.setBounds(760, 0, 40, 35);
    menu.setText("menu");
    menu.addItemList(menulist, 1);

    menu.onChange = [&] {
        if (menu.getSelectedItemIndex() ==0)
        {
            initAll();
        }
        if (menu.getSelectedItemIndex() == 1)
        {
            JUCEApplicationBase::quit();
            
        }
        menu.setText("menu");
    };
    addAndMakeVisible(menu);

    mainvolume.setRange(0.0, 100.0, 0);
    mainvolume.setValue(70.0);
    mainvolume.setBounds(800, -5, 70, 70);
    mainvolume.setDoubleClickReturnValue(true, 70.0, ModifierKeys::altModifier);
    mainvolume.setNumDecimalPlacesToDisplay(1);
    mainvolume.onValueChange = [this] {repaint(880, 0, 100, 70);  };

    addAndMakeVisible(mainvolume);

    keyboardComponent.setBounds(165 ,650,560,78);
    keyboardComponent.setAvailableRange(36,95);

    addAndMakeVisible(keyboardComponent);

    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
    env1button.setBounds(75, 370, 95, 20);
    env2button.setBounds(170, 370, 95, 20);
    env3button.setBounds(265, 370, 95, 20);
    addAndMakeVisible(env1button);
    addAndMakeVisible(env2button);
    addAndMakeVisible(env3button);
    env1button.state = true;
    env2button.state = false;
    env3button.state = false;
    env1button.onClick = [&] {
        if (!env1.isVisible()) {
            env1button.state = true;
            env2button.state = false;
            env3button.state = false;
            env1.setVisible(true);
            env2.setVisible(false);
            env3.setVisible(false);
            repaint();
        }
    };
    env2button.onClick = [&] {
        if (!env2.isVisible()) {
            env2button.state = true;
            env1button.state = false;
            env3button.state = false;
            env2.setVisible(true);
            env1.setVisible(false);
            env3.setVisible(false);
            repaint();
        }
    };
    env3button.onClick = [&] {
        if (!env3.isVisible()) {
            env3button.state = true;
            env2button.state = false;
            env1button.state = false;
            env3.setVisible(true);
            env2.setVisible(false);
            env1.setVisible(false);
            repaint();
        }
    };
    oscscreen.oscA.osccb.onChange = [&] {
        if(oscscreen.oscA.oscstate){
            synthAudioSource.changeSoundandVoice(oscscreen.oscA.osccb.getSelectedItemIndex());
        }
        else
        {
            //synthAudioSource.synth.clearVoices();
            //synthAudioSource.synth.clearVoices();
        }
        oscscreen.oscA.setoscwavenum(oscscreen.oscA.osccb.getSelectedItemIndex());
    };    
    oscscreen.oscB.osccb.onChange = [&] {
        synthAudioSource.changeSoundandVoice(oscscreen.oscB.osccb.getSelectedItemIndex())  ;
        oscscreen.oscB.setoscwavenum(oscscreen.oscB.osccb.getSelectedItemIndex());
    };

    env1button.setName("env1");
    env2button.setName("env2");
    env3button.setName("env3");
    env1.setBounds(75, 390, 285, 260);
    env2.setBounds(75, 390, 285, 260);
    env3.setBounds(75, 390, 285, 260);
    addAndMakeVisible(env1);
    addChildComponent(env2);
    addChildComponent(env3);
}

void MainComponent::initAll()
{   
    oscscreen.oscA.initosc();
    oscscreen.oscB.initosc();
    oscscreen.filter.initFilter();
    oscscreen.sub.initSub();
    oscscreen.noise.initNoise();
    mainvolume.setValue(70.0);

    fxscreen.initFxScreen();
    env1.initEnvScreen();
    repaint();
}

void Osc::StateButtonEvent()
{    
    statebutton.onClick = [this]() {
        if (oscstate) {
            statebutton.buttonstate = false;
            osccb.setColour(juce::ComboBox::textColourId,  juce::Colour((uint8)111, 111, 111,0.0f));
            oscstate = false;
            repaint();
        }
        else {
            statebutton.buttonstate = true;
            //int temp = osccb.getSelectedItemIndex();
            //osccb.setSelectedItemIndex(0);
            //osccb.setSelectedItemIndex(temp);
            oscstate = true;
            repaint();
        }
    };
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
    setLookAndFeel(nullptr);
    oscbutton.setLookAndFeel(nullptr);
    fxbutton.setLookAndFeel(nullptr);
    matrixbutton.setLookAndFeel(nullptr);
    globalbutton.setLookAndFeel(nullptr);
    rightbutton.setLookAndFeel(nullptr);
    leftbutton.setLookAndFeel(nullptr);
    savebutton.setLookAndFeel(nullptr);
}

void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.
    synthAudioSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
    synthAudioSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.
    synthAudioSource.releaseResources();
    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll ( juce::Colours::white);

    g.setColour(juce::Colours::red);

    g.drawRect(0, 0, 150, 70);
    g.setFont(36.0f);
    g.drawText("LAOAudio", 0, 0, 150, 70, juce::Justification::centred, true);
    juce::String st[4] = {"osc","fx","matrix","global"};
    g.setFont(14.0f);
    for (int i = 0; i< 4; i++)
    {
        g.drawRect(i * 70.0+150.0, 0.0, 70.0, 70.0, 1.0f);
        g.drawText(st[i], i * 70.0 + 150.0, 0.0, 70.0, 70.0, juce::Justification::centred, true);
    }
    g.drawRect(800.0, 0.0, 100.0, 70.0, 1.0f);
    g.drawText("master", 800, 50, 70, 20, juce::Justification::centred, true);

    g.drawRect(0.0, 370.0, 75.0, 20.0, 1.0f);
    g.drawText("mod", 0.0, 370.0, 75.0, 20.0, juce::Justification::left, true);
    g.drawText("+ ", 0.0, 370.0, 75.0, 20.0, juce::Justification::right, true);
    
    for (int i = 0; i < 7; i++)
    {
        if (i<3)
        {
            g.drawText("env"+ String(i+1), i * 95.0 + 75.0, 370.0, 95.0, 20.0, juce::Justification::centred, true);
        }
        else {
            g.drawText("lfo"+ String(i-2 ), i * 95.0 + 75.0, 370.0, 95.0, 20.0, juce::Justification::centred, true);
        }
        g.drawRect(i * 95.0 + 75.0, 370.0, 95.0, 20.0, 1.0f);
    }
    // You can add your drawing code here!
    g.drawRect(0.0, 370.0, 75.0, 280.0, 1.0f);
    for (int i = 0; i <4; i++)
    {
        g.drawRect(0.0, 390.0+i*65.0, 75.0,65.0, 1.0f);
        g.drawText("+ ", 0.0, 390.0 + i * 65.0, 75.0, 65.0, juce::Justification::right, true);
    }
        //lfodrawblearea
        g.drawRect(360.0, 370.0, 380.0, 180.0, 1.0f);
        g.drawRect(360.0, 370.0, 380.0, 280.0, 1.0f);
        //wdwdwd
        g.drawRect(740.0, 370.0, 80.0, 20.0, 1.0f);
        g.drawRect(820.0, 370.0, 80.0, 20.0, 1.0f);
        g.drawRect(740.0, 370.0, 160.0, 180.0, 1.0f);
        g.drawRect(740.0, 370.0, 160.0, 280.0, 1.0f);
        //keyboard area
        g.drawRect(0.0, 650.0, 900.0, 78.0, 1.0f);
    drawMainVolume(g);
    
   // g.drawText(String(150 + (590 - keyboardComponent.getTotalKeyboardWidth()) / 2), 10.0, 10.0, 200.0, 10.0, juce::Justification::centred, true);
   // keyboardComponent.get
    //g.drawText(String(keyboardComponent.getMidiChannel()), 10.0, 10.0, 200.0, 10.0, juce::Justification::centred, true);
    g.setColour(juce::Colours::green);
    //Path envpath;
    //envpath.startNewSubPath(76.0, 549.0);
    //envpath.lineTo(77, 391);
    //envpath.lineTo(177, 391);
    //envpath.lineTo(178, 549);
    //envpath.lineTo(359, 549);
    //g.strokePath(envpath, juce::PathStrokeType(2.0f));

    Path lfopath;
    lfopath.startNewSubPath(361, 549);
    lfopath.lineTo(550, 391);
    lfopath.lineTo(739, 549);
    g.strokePath(lfopath, juce::PathStrokeType(2.0f));
}

void MainComponent::drawMainVolume(juce::Graphics& g)
{
    for (int i = 0; i < mainvolume.getValue()/10; i++)
    {
        g.setColour(juce::Colours::green);
        g.fillRect(880, 62 - 6* i, 10, 4);
    }
}

Osc::Osc()
{
    oscwavenum = 0;
    oscstate = false;
    showdetune = false;
    oscdetune = 0.0;
    itemlist = { "sin","tri","squ","noise" };
    osccb.addItemList(itemlist, 1);
    setOscItemVisible();
    rightbutton.setLookAndFeel(&buttonlookandfeel);
    leftbutton.setLookAndFeel(&buttonlookandfeel);

    statebutton.setBounds(10, 9, 12, 12);

    panslider.setBounds(160, 235, 60, 60);
    panslider.setRange(-50.0, 50.0, 0);
    panslider.setDoubleClickReturnValue(true, 0.0);
    panslider.setNumDecimalPlacesToDisplay(1);
    volumeslider.setBounds(220, 235, 60, 60);
    volumeslider.setRange(0.0, 100.0, 0);
    volumeslider.setDoubleClickReturnValue(true, 70.0);
    volumeslider.setNumDecimalPlacesToDisplay(1);

    unison.setBounds(0, 180, 40, 60);
    unison.setSliderStyle(Slider::SliderStyle::LinearVertical);
    unison.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    unison.setRange(1, 16, 1);
    unison.setLookAndFeel(&unisonlookandfeel);

    detune.setBounds(40, 175, 60, 60);
    detune.setRange(0.00, 1.00, 0);
    detune.setSkewFactorFromMidPoint(0.25);
    detune.setDoubleClickReturnValue(true, 0.25);
    detune.setNumDecimalPlacesToDisplay(2);

    blend.setBounds(100, 175, 60, 60);
    blend.setRange(0, 100, 0);
    blend.setDoubleClickReturnValue(true, 75);
    blend.setNumDecimalPlacesToDisplay(0);

    phase.setBounds(160, 175, 60, 60);
    phase.setRange(0, 360, 0);
    phase.setDoubleClickReturnValue(true, 180);
    phase.setNumDecimalPlacesToDisplay(0);

    rand.setBounds(220, 175, 60, 60);
    rand.setRange(0, 100, 0);
    rand.setDoubleClickReturnValue(true, 100);
    rand.setNumDecimalPlacesToDisplay(0);
    leftbutton.setBounds(230, 30, 20, 20);
    leftbutton.setButtonText("<");
    leftbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    rightbutton.setBounds(250, 30, 20, 20);
    rightbutton.setButtonText(">");
    rightbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    rightbutton.onClick = [this] {
        if (osccb.getSelectedItemIndex() != osccb.getNumItems() - 1)
        {
            osccb.setSelectedItemIndex(osccb.getSelectedItemIndex() + 1);
            repaint();
        }
    };
    leftbutton.onClick = [this] {
        if (osccb.getSelectedItemIndex() != 0)
        {
            osccb.setSelectedItemIndex(osccb.getSelectedItemIndex() - 1);
            repaint();
        }
    };
    osccb.setText("select basic wave...");
    osccb.setBounds(70, 30, 140, 20);
    /*   octave.setBounds(10,50,40,20);
       semitones.setBounds(60,50,40,20);
       cents.setBounds(110,50,40,20);
       coarsepits.setBounds(160,50,70,20);*/
}

void Osc::setoscnum(int oscnum)
{
    this->oscnum = oscnum;
}

void Osc::setoscwavenum(int oscwavenum)
{
    this->oscwavenum = oscwavenum;
    repaint(0, 0, 280, 300);
}

int Osc::getoscnum()
{
    return this->oscnum;
}

int Osc::getoscwavenum()
{
    return oscwavenum;
}

void Osc::drawOscWave( juce::Graphics& g)
{   
    g.setColour(juce::Colours::green);
    switch (getoscwavenum())
    {
    case 0:drawOscSin(g);
        break;
    case 1:drawOscTri(g);
        break;
    case 2:drawOscSqu(g);
        break;
    case 3:drawOscNoi(g);
        break;
    default:break;
    }
}

void Osc::drawDutune(juce::Graphics& g)
{
    g.setColour(juce::Colours::lightgreen);
    if (showdetune) {
        int linenum = unison.getValue();
        if (linenum==1) {
            g.drawLine(140.0 , 179.0, 140.0 , 110.0, 1.0f);
        }else{
            for (int i = 0; i < linenum; i++)
            {
                if (( linenum % 2!=0&&i==(int)linenum/2)||( linenum % 2 == 0&&(i==linenum/2-1|| i ==linenum / 2) )){
                    g.setColour(Colours::red);
                }
                else
                {
                    g.setColour(Colours::yellowgreen);
                }
                g.drawLine(140.0 - oscdetune * 120.0+i*240.0*oscdetune/(linenum-1), 179.0, 140.0 - oscdetune * 120.0+ i * 240.0 * oscdetune /( linenum-1), 110.0, 1.5f);
            }
        }
    }
}

void Osc::setOscItemVisible() {
    addAndMakeVisible(volumeslider);
    addAndMakeVisible(panslider);
    addAndMakeVisible(blend);
    addAndMakeVisible(detune);
    addAndMakeVisible(rand);
    addAndMakeVisible(phase);
    addAndMakeVisible(osccb);
    addAndMakeVisible(statebutton);
    addAndMakeVisible(leftbutton);
    addAndMakeVisible(rightbutton);
    addAndMakeVisible(unison);
    //addAndMakeVisible(octave);
    //addAndMakeVisible(semitones);
    //addAndMakeVisible(cents);
    //addAndMakeVisible(coarsepits);
}

Osc::~Osc()
{
     unison.setLookAndFeel(nullptr);
     leftbutton.setLookAndFeel(nullptr);
     rightbutton.setLookAndFeel(nullptr);
}

void Osc::initosc()
{       
    oscwavenum = 0;
    oscstate = true;
    showdetune = false;
    oscdetune=0.0;
    statebutton.buttonstate = true;
    panslider.setValue(0.0);
    volumeslider.setValue(70);
    detune.setValue(0.25);
    blend.setValue(75);
    phase.setValue(180);
    rand.setValue(100);
    unison.setValue(1);

    osccb.setColour(juce::ComboBox::backgroundColourId, juce::Colours::white);
    osccb.setSelectedItemIndex(0); 

    leftbutton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);

    rightbutton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);

}

void Osc::drawOscSin(juce::Graphics& g)
{
    juce::Path wavePath;
    wavePath.startNewSubPath(10.0 , 125.0);
    for (int i = 0; i < 260; i++)
    {
        wavePath.lineTo(i + 10.0 , 125 + 54 * std::sin(i * 3.141592653589793238 * 2 / 260));
    }
    g.strokePath(wavePath, juce::PathStrokeType(2.0f));
    g.drawLine(10.0 , 125.0, 270.0 , 125.0, 1.0f);
}

void Osc::drawOscTri(juce::Graphics& g)
{
    g.drawLine(10.0, 125.0, 140.0 , 70.0, 2.0f);
    g.drawLine(140.0  , 180.0, 270.0 , 125.0, 2.0f);
    g.drawLine(140.0, 70.0, 140.0, 180.0, 2.0f);
    g.drawLine(10.0, 125.0, 270.0, 125.0, 1.0f);
}

void Osc::drawOscSqu(juce::Graphics& g)
{
    juce::Path wavePath;
    wavePath.startNewSubPath(12.0 , 125.0);
    wavePath.lineTo(13.0 , 70.0);
    wavePath.lineTo(139.0 , 70.0);
    wavePath.lineTo(141.0 , 180.0);
    wavePath.lineTo(267.0 , 180.0);
    wavePath.lineTo(268.0 , 125.0);
    g.strokePath(wavePath, juce::PathStrokeType(2.0f));
    g.drawLine(10.0 , 125.0, 270.0, 125.0, 1.0f);
}

void Osc::drawOscNoi(juce::Graphics& g)
{
    Random r;
    juce::Path wavePath;
    wavePath.startNewSubPath(12.0 , 125.0);
    for (int i = 0; i < 260; i++)
    {
        wavePath.lineTo(i+12.0 , 125 +  r.nextInt(110)-54);
    }
    g.strokePath(wavePath, juce::PathStrokeType(2.0f));
    g.drawLine(10.0, 125.0, 250.0 , 125.0, 1.0f);

}

void Osc::paint(juce::Graphics& g)
{
    drawOscWave(g);
    drawDutune(g);
    if (!oscstate)
    {
        g.setColour(juce::Colour(111, 111, 111));
        g.setOpacity(0.8f);

        g.fillRect(11, 31, getWidth()-22, 148);
    }
    g.setColour(Colours::red);
    g.drawRect(getLocalBounds());
    g.drawRect(10, 30, 260, 150);
    g.drawRect(10, 70, 260, 110);
    g.drawText(getName(), 10, 5, 260, 20, juce::Justification::centred, true);

    g.drawRect(0, 180, 40, 60);
    g.drawText("unison", 0, 220, 40, 20, juce::Justification::centred, true);
    g.drawRect(40, 180, 60, 60);
    g.drawText("detune", 40, 220, 60, 20, juce::Justification::centred, true);
    g.drawRect(100, 180, 60, 60);
    g.drawText("blend", 100, 220, 60, 20, juce::Justification::centred, true);
    g.drawRect(160, 180, 60, 60);
    g.drawText("phase", 160, 220, 60, 20, juce::Justification::centred, true);
    g.drawRect(220, 180, 60, 60);
    g.drawText("rand", 220, 220, 60, 20, juce::Justification::centred, true);

    g.drawRect(0, 240, 60, 60);
    g.drawRect(60, 240, 100, 60);
    g.drawRect(160, 240, 60, 60);
    g.drawRect(220, 240, 60, 60);
    g.drawText("wt pos", 0, 280, 60, 20, juce::Justification::centred, true);
    g.drawText("???", 60, 280, 100, 20, juce::Justification::centred, true);
    g.drawText("pan", 160, 280, 60, 20, juce::Justification::centred, true);
    g.drawText("level", 220, 280, 60, 20, juce::Justification::centred, true);

}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

Filter::Filter()
{
    StringArray filterlist = { "1","2","3" };

    statebutton.setBounds(10, 9, 12, 12);
    filtercb.setBounds(50, 30, 90, 20);
    filtercb.setText("select filter wave...");
    filtercb.addItemList(filterlist, 1);
    filtercb.setSelectedItemIndex(0);
    leftbutton.setBounds(140, 30, 20, 20);
    leftbutton.setButtonText("<");
    leftbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    rightbutton.setBounds(160, 30, 20, 20);
    rightbutton.setButtonText(">");
    rightbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);

    rightbutton.setLookAndFeel(&buttonlookandfeel);
    leftbutton.setLookAndFeel(&buttonlookandfeel);
    addAndMakeVisible(statebutton);
    addAndMakeVisible(filtercb);    
    addAndMakeVisible(leftbutton);
    addAndMakeVisible(rightbutton);
    rightbutton.onClick = [this] {
        if (filtercb.getSelectedItemIndex() != filtercb.getNumItems() - 1)
        {
            filtercb.setSelectedItemIndex(filtercb.getSelectedItemIndex() + 1);
            repaint();
        }
    };
    leftbutton.onClick = [this] {
        if (filtercb.getSelectedItemIndex() != 0)
        {
            filtercb.setSelectedItemIndex(filtercb.getSelectedItemIndex() - 1);
            repaint();
        }
    };
    statebutton.onClick = [this]() {
        if (filterstate) {
            statebutton.buttonstate = false;
            filtercb.setColour(juce::ComboBox::textColourId, juce::Colours::white);
            filterstate = false;
            repaint();
        }
        else {
            statebutton.buttonstate = true;
            filtercb.setColour(juce::ComboBox::textColourId, juce::Colour((uint8)111, 111, 111, 0.0f));
            filterstate = true;
            repaint();
        }
    };
    cutoff.setBounds(35, 175, 60, 60);
    res.setBounds(85, 175, 60, 60);
    pan.setBounds(135, 175, 60, 60);
    drive.setBounds(35, 235, 60, 60);
    fat.setBounds(85, 235, 60, 60);
    mix.setBounds(135, 235, 60, 60);
    addAndMakeVisible(cutoff);
    addAndMakeVisible(res);
    addAndMakeVisible(pan);
    addAndMakeVisible(drive);
    addAndMakeVisible(fat);
    addAndMakeVisible(mix);
    cutoff.setRange(8, 22090, 1);
    res.setRange(0,100,1);
    pan.setRange(0, 100, 1);
    drive.setRange(0, 100, 1);
    fat.setRange(0, 100, 1);
    mix.setRange(0, 100, 1);
    initFilter();
    cutoff.setSkewFactorFromMidPoint(425);

    oscAstate.setBounds(10, 185, 10, 10);
    oscBstate.setBounds(10, 205, 10, 10);
    substate.setBounds(10, 235, 10, 10);
    noisestate.setBounds(10, 255, 10, 10);
    keyboardstate.setBounds(10, 285, 10, 10);
    addAndMakeVisible(oscAstate);
    addAndMakeVisible(oscBstate);
    addAndMakeVisible(substate);
    addAndMakeVisible(noisestate);
    addAndMakeVisible(keyboardstate);
}

Filter::~Filter()
{
    filtercb.setLookAndFeel(nullptr);
    rightbutton.setLookAndFeel(nullptr);
    leftbutton.setLookAndFeel(nullptr);

}

void Filter::paint(juce::Graphics& g)
{
    g.setColour(Colours::red);
    g.drawRect(0, 0, 190, 300);
    g.drawRect(10, 30, 170, 20);
    g.drawRect(10, 70, 170, 110);
    g.drawText("filter", 10, 5, 170, 20, juce::Justification::centred, true);
 
    StringArray list = {"cutoff","res","pan","drive","fat","mix"};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++) {
            g.drawRect(40+50*i, 180+60*j, 50, 60);
            g.drawText(list[i+j*3], 40 + 50 * i, 220 + 60 * j, 50, 20, Justification::centred);
        }
    }
    //g.drawRect(10, 180, 30, 20);
    //g.drawRect(10, 200, 30, 20);
    //g.drawRect(10, 230, 30, 20);
    //g.drawRect(10, 250, 30, 20);
    //g.drawRect(10, 280, 30, 20);
    g.drawText("A", 20, 180, 20, 20, Justification::centred);
    g.drawText("B", 20, 200, 20, 20, Justification::centred);
    g.drawText("N", 20, 230, 20, 20, Justification::centred);
    g.drawText("S", 20, 250, 20, 20, Justification::centred);
    g.drawText("K", 20, 280, 20, 20, Justification::centred);
    if (!filterstate)
    {
        g.setColour(juce::Colour(111, 111, 111));
        g.setOpacity(0.8f);
        g.fillRect(11, 71, 168, 108);
    }
}

void Filter::initFilter()
{
    filterstate = false;
    statebutton.buttonstate = false;
    cutoff.setValue(425);
    res.setValue(10);
    pan.setValue(50);
    drive.setValue(0);
    fat.setValue(0);
    mix.setValue(100);
}

void Osc::detuneEvent()
{   
    detune.onDragStart = [&] {showdetune = true; };
    detune.onDragEnd = [&] {showdetune = false; repaint(); };
    detune.onValueChange = [&] {
        oscdetune = detune.getValue();
        repaint(); };   
    unison.onDragStart = [&] {showdetune = true; };
    unison.onDragEnd = [&] {showdetune = false; repaint(); };
    unison.onValueChange = [&] {
        oscdetune = detune.getValue();
        repaint(); };
}

void OscScreen::paint(Graphics& g )
{
}

Sub::Sub()
{
    statebutton.setBounds(10, 9, 12, 12);
    addAndMakeVisible(statebutton);
    octave.setBounds(5, 60, 40, 60);
    pan.setBounds(45, 55, 60, 60);
    level.setBounds(95, 55, 60, 60);
    octave.setSliderStyle(Slider::SliderStyle::LinearVertical);
    octave.setRange(-4, 4, 1);
    octave.setLookAndFeel(&unisonlookandfeel);
    pan.setRange(-100, 100, 1);
    level.setRange(0, 100, 1);
    addAndMakeVisible(octave);
    addAndMakeVisible(pan);
    addAndMakeVisible(level);
    statebutton.onClick = [this] {             
        if (statebutton.buttonstate) {
            statebutton. buttonstate = false;
        }
    else {
            statebutton.buttonstate = true;
        }repaint();
    };

    initSub();
}

void Sub::initSub()
{
    statebutton.buttonstate = false;
    octave.setValue(0);
    pan.setValue(0);
    level.setValue(70);
}

Sub::~Sub()
{
    octave.setLookAndFeel(nullptr);

}

void Sub::paint(juce::Graphics& g)
{

    g.setColour(juce::Colours::red);
    g.drawRect(0, 0, 150, 130);
    g.drawText("sub", 10, 5, 130, 20, juce::Justification::centred);
    g.drawRect(10, 30, 130, 20);
    for (int i = 0; i < 6; i++)
    {
        g.drawRect(15 + 20 * i, 30, 20, 20);
    }
    g.drawRect(0, 60, 50, 60);
    g.drawRect(50, 60, 50, 60);
    g.drawRect(100, 60, 50, 60);
    g.drawText("octave", 0, 100, 50, 20, Justification::centred);
    g.drawText("pan", 50, 100, 50, 20, Justification::centred);
    g.drawText("level",100, 100, 50, 20, Justification::centred);
    if (!statebutton.buttonstate) {
        g.setColour(juce::Colour(111, 111, 111));
        g.setOpacity(0.8f);
        g.fillRect   (10, 30, 130, 20);
     
    }
}

Noise::Noise()
{
    StringArray noiselist = {"1","2","3"};
    statebutton.setBounds(10, 9, 12, 12);
    addAndMakeVisible(statebutton);
    statebutton.onClick = [this] {
        if (statebutton.buttonstate) {
            statebutton.buttonstate = false;
        }
        else {
            statebutton.buttonstate = true;
        }repaint();
    };
    noisecb.setBounds(10, 30, 90, 20);
    noisecb.addItemList(noiselist, 1);
    noisecb.setColour(juce::ComboBox::textColourId, juce::Colour((uint8)111, 111, 111, 0.0f));
    addAndMakeVisible(noisecb);
    obutton.setBounds(10, 60, 10, 10);
    kbutton.setBounds(10, 90, 10, 10);
    addAndMakeVisible(obutton);
    addAndMakeVisible(kbutton);
    phase.setBounds(45, 45, 60, 60);
    rand.setBounds(95, 45, 60, 60); 
    pitch.setBounds(-5, 105, 60, 60);
    pan.setBounds(45, 105, 60, 60);
    level.setBounds(95, 105, 60, 60);    
    phase.setRange(0,100,1);
    rand.setRange(0, 100, 1);
    pitch.setRange(0, 100, 1);
    pan.setRange(-100, 100, 1);
    level.setRange(0, 100, 1);
    leftbutton.setBounds(100, 30, 20, 20);
    rightbutton.setBounds(120, 30, 20, 20);
    addAndMakeVisible(phase);
    addAndMakeVisible(rand);
    addAndMakeVisible(pan);
    addAndMakeVisible(pitch);
    addAndMakeVisible(level);
    addAndMakeVisible(leftbutton);
    addAndMakeVisible(rightbutton);
    leftbutton.setButtonText("<");
    leftbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);
    rightbutton.setButtonText(">");
    rightbutton.setColour(juce::TextButton::textColourOffId, juce::Colours::red);
    rightbutton.setLookAndFeel(&buttonlookandfeel);
    leftbutton.setLookAndFeel(&buttonlookandfeel);
    rightbutton.setLookAndFeel(&buttonlookandfeel);
    rightbutton.onClick = [this] {
        if (noisecb.getSelectedItemIndex() != noisecb.getNumItems() - 1)
        {
            noisecb.setSelectedItemIndex(noisecb.getSelectedItemIndex() + 1);
            repaint();
        }
    };
    leftbutton.onClick = [this] {
        if (noisecb.getSelectedItemIndex() != 0)
        {
            noisecb.setSelectedItemIndex(noisecb.getSelectedItemIndex() - 1);
            repaint();
        }
    };
    initNoise();
}

void Noise::initNoise()
{
    statebutton.buttonstate = false;    
    phase.setValue(0);
    rand.setValue(0);
    pitch.setValue(50);
    pan.setValue(0);
    level.setValue(25);
    noisecb.setSelectedItemIndex(0);

}

Noise::~Noise()
{
    leftbutton.setLookAndFeel(nullptr);
    rightbutton.setLookAndFeel(nullptr);
}

void Noise::paint(juce::Graphics& g)
{
    g.setColour(Colours::red);
    g.drawRect(0, 0, 150, 170);
    g.drawText("noise", 10, 5, 130, 20, Justification::centred);
    //g.drawRect(10, 30, 130, 20);
    g.drawText("o", 25, 60, 10, 10, Justification::centred);
    g.drawText("k", 25, 90, 10, 10, Justification::centred);

    StringArray list = { " ","phase","rand","pitch","pan","level" };
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 2; j++) {
            g.drawRect( 50 * i, 50 + 60 * j, 50, 60);
            g.drawText(list[i + j * 3],50 * i, 90 + 60 * j, 50, 20, Justification::centred);
        }
    }


    if (!statebutton.buttonstate)
    {
        g.setColour(juce::Colour(111, 111, 111));
        g.setOpacity(0.8f);
        g.fillRect(10, 30, 130, 20);
    }
}

EnvScreen::EnvScreen()
{
    initEnvScreen();
    pointlist->add(&p1);
    pointlist->add(&p2);
    pointlist->add(&p3);
    pointlist->add(&p4);
    pointlist->add(&p5);
   midlist->add(&m1);
   midlist->add(&m2);
   midlist->add(&m3);
   midlist->add(&m4);

    lockbutton.setBounds(270, 0, 15, 15);
    addAndMakeVisible(lockbutton);

    lockbutton.onClick = [this]() {
        if (lockbutton.buttonstate) {
            lockbutton.buttonstate = false;
            lastpoint = 1;
            length = (2 +50*envlenght.getValue());
            envlenght.setVisible(true);
            repaint();
        }
        else {
            lockbutton.buttonstate = true;
            length = 260;
            lastpoint = p5.getX();
            envlenght.setVisible(false);
            repaint();
        }
    };

    envlenght.setBounds(270, 15, 15, 145);
    envlenght.setSliderStyle(Slider::LinearVertical);
    addAndMakeVisible(envlenght);

    envlenght.onValueChange = [&] {
        length = 2 + 50 * envlenght.getValue();
        repaint();
    };

    attack.setBounds(-5, 180, 60, 60);
    hold.setBounds(45, 180, 60, 60);
    decay.setBounds(112.5, 180, 60, 60);
    sustain.setBounds(162.5, 180, 60, 60);
    release.setBounds(230, 180, 60, 60);
    sustain.setRange(0, 100, 1);

    addAndMakeVisible(attack);
    addAndMakeVisible(hold);
    addAndMakeVisible(decay);
    addAndMakeVisible(sustain);
    addAndMakeVisible(release);

    attack.setRange(0.0,32 , 0.0001);
    hold.setRange(0.0, 32, 0.0001);
    decay.setRange(0.0, 32, 0.0001);
    release.setRange(0.0001, 32, 0.0001);   
    attack.setSkewFactorFromMidPoint(1);
    hold.setSkewFactorFromMidPoint(1);
    decay.setSkewFactorFromMidPoint(1);
    release.setSkewFactorFromMidPoint(1);


    attack.onValueChange = [&] {
        Array<Point<float>*> templist[1];
        for (int i = 0; i < pointlist->size(); i++)
        {
            templist->add(pointlist->getUnchecked(i));
        }
        float tempvalue = p2.getX();
        pointlist->getUnchecked(1)->setX(attack.getValue());
        for (int i = 2; i < pointlist->size(); i++)
        {
            pointlist->getUnchecked(i)->setX(attack.getValue()-tempvalue + templist->getUnchecked(i)->getX());
        }
        m1.setX((p1.getX() + p2.getX()) / 2);
        m2.setX((p2.getX() + p3.getX()) / 2);
        m3.setX((p3.getX() + p4.getX()) / 2);
        m4.setX((p4.getX() + p5.getX()) / 2);

        if (lockbutton.buttonstate) {
            lastpoint = p5.getX();
        }
        repaint();
    };   
    hold.onValueChange = [&] {
       // p3.setX(hold.getValue() * (p4.getX() - p2.getX()) +p2.getX());
        Array<Point<float>*> templist[1];
        for (int i = 0; i < pointlist->size(); i++)
        {
            templist->add(pointlist->getUnchecked(i));
        }
        float tempvalue = p3.getX();
        pointlist->getUnchecked(2)->setX(hold.getValue()+ p2.getX());
        for (int i = 3; i < pointlist->size(); i++)
        {
            pointlist->getUnchecked(i)->setX(hold.getValue() + p2.getX() - tempvalue + templist->getUnchecked(i)->getX());
        }
        m1.setX((p1.getX() + p2.getX()) / 2);
        m2.setX((p2.getX() + p3.getX()) / 2);
        m3.setX((p3.getX() + p4.getX()) / 2);
        m4.setX((p4.getX() + p5.getX()) / 2);
        if (lockbutton.buttonstate) {
            lastpoint = p5.getX();
        }
        repaint();
    };    
    decay.onValueChange = [&] {
       // p4.setX(decay.getValue() * (p5.getX() - p3.getX()) +p3.getX());
        Array<Point<float>*> templist[1];
        for (int i = 0; i < pointlist->size(); i++)
        {
            templist->add(pointlist->getUnchecked(i));
        }
        float tempvalue = p4.getX();
        pointlist->getUnchecked(3)->setX(decay.getValue() + p3.getX());
        for (int i = 4; i < pointlist->size(); i++)
        {
            pointlist->getUnchecked(i)->setX(decay.getValue() + p3.getX() - tempvalue + templist->getUnchecked(i)->getX());
        }
        if (lockbutton.buttonstate) {
            lastpoint = p5.getX();
        }
        m1.setX((p1.getX() + p2.getX()) / 2);
        m2.setX((p2.getX() + p3.getX()) / 2);
        m3.setX((p3.getX() + p4.getX()) / 2);
        m4.setX((p4.getX() + p5.getX()) / 2);
        repaint();
 
    };    
    sustain.onValueChange = [&] {
        p4.setY(sustain.getValue()/100);
        m3.setY(1 -(1- powf(0.5, midindex[2]) )* (p3.getY() - p4.getY()));
        m4.setY(powf(0.5, midindex[3])* p4.getY());
        repaint();
    };

    release.onValueChange = [&] {
        p5.setX(release.getValue() + p4.getX());
        m1.setX((p1.getX() + p2.getX())/ 2) ;
        m2.setX((p2.getX() + p3.getX())/ 2) ;
        m3.setX((p3.getX() + p4.getX())/ 2) ;
        m4.setX((p4.getX() + p5.getX())/ 2) ;
        if (lockbutton.buttonstate) {
            lastpoint = p5.getX();
        }
        repaint();
    };
    initEnvScreen();
}

EnvScreen::~EnvScreen()
{
}

void EnvScreen::paint(juce::Graphics& g)
{
    g.drawRect(getLocalBounds());
    //env drawable area
    
    g.drawText(String(attack.getValue())+"s", 0, 160, 50, 20, Justification::centred);
    g.drawText(String(hold.getValue()) + "s", 50, 160, 50, 20, Justification::centred);
    g.drawText(String(decay.getValue()) + "s", 117.5, 160, 50, 20, Justification::centred);
    g.drawText(String(sustain.getValue()) + "db", 167.5, 160, 50, 20, Justification::centred);
    g.drawText(String(release.getValue()) + "s", 235, 160, 50, 20, Justification::centred);

    g.drawRect(0, 0, 285,160);
    g.drawRect(0, 160, 50,100);
    g.drawRect(50, 160, 50,100);
    g.drawRect(117.5, 160, 50,100);
    g.drawRect(167.5, 160, 50,100);
    g.drawRect(235, 160, 50,100);    
    
    g.drawText("attack", 0, 240, 50, 20,Justification::centred);
    g.drawText("hold", 50, 240, 50, 20, Justification::centred);
    g.drawText("decay", 117.5, 240, 50, 20, Justification::centred);
    g.drawText("sustain", 167.5, 240, 50, 20, Justification::centred);
    g.drawText("release",235, 240, 50,20, Justification::centred);
    double linenumindex = 1;

    g.setFont(10);
    int sum = 0;
    for (int i = 0; 5 + i * length/ lastpoint < 260; i++)
    {
        sum++;
    }
    for (int i = 0; i < sum; i++)
    {
        if (sum<4*pow(2,i))
        {
            linenumindex = pow(2, i-2);
            break;
        }
    }

    for (int i = 0;5+i* length * linenumindex  / lastpoint <260; i++)
    {
        g.drawLine(5+ length * i * linenumindex / lastpoint,0,5+ length * i *linenumindex / lastpoint,150);
        g.drawText(String(i * linenumindex),-5+ length * i * linenumindex / lastpoint, 150.0, 30.0, 10.0, Justification::centred);
    }
    g.setFont(14.0f);

    g.setColour(Colours::purple);

    g.drawRect(270, 0, 15, 160);
    g.setColour(Colours::purple);

    Path p;
    p.startNewSubPath(5 + length * pointlist->getUnchecked(0)->getX() / lastpoint, 5 + 150 * (1 - pointlist->getUnchecked(0)->getY()));
    for (int i = 0; i < pointlist->size()-1; i++)
    {
        float x1 = 5 + length * pointlist->getUnchecked(i)->getX() / lastpoint;
        float x2 = 5 + length * pointlist->getUnchecked(i+1)->getX() / lastpoint;
        float y1 =pointlist->getUnchecked(i)->getY();
        float y2 =pointlist->getUnchecked(i + 1)->getY();
        float index = midindex[i];
        for (int j =x1+1; j <= x2; j++)
        {            
            if (y1 < y2) {
                float y = envFunction((j - x1) / (x2 - x1), index) * (y2 - y1)+(1-y2);
                p.lineTo(j, 5 + 150 * y);
            }
            else
            {
                float y = envFunction((-j + x1) / (x2 - x1)+1, index) * (y1- y2)+ (1 - y1);
                p.lineTo(j, 5 + 150 * y);
            }
        }
    }
    g.strokePath(p, PathStrokeType(2.0f));
    for (int i = 0; i < midlist->size(); i++)
    {
        if (i == pnum - 6) {
            g.setColour(Colours::red);
        }
        else
        {
            g.setColour(Colours::purple);
        }
        float x1 = 1 + length * midlist->getUnchecked(i)->getX() / lastpoint;
        float y1 = 1 + 150 * (1 - midlist->getUnchecked(i)->getY());
        g.fillEllipse(x1, y1, 8.0f, 8.0f);
    }
    for (int i = 0; i < pointlist->size(); i++)
    {
        if (i == pnum - 1) {
            g.setColour(Colours::red);
        }
        else
        {
            g.setColour(Colours::purple);
        }
        float x1 = 1 + length * pointlist->getUnchecked(i)->getX() / lastpoint;
        float y1 = 1 + 150 * (1 - pointlist->getUnchecked(i)->getY());

        //g.drawRect(x1, y1, 8.0f, 8.0f, 2.0f);
        g.fillRect(x1, y1, 8.0f, 8.0f);
    }
}

float EnvScreen::envFunction(float x, float index) {

    return 1-powf(x, index);
}

void EnvScreen::mouseDown(const MouseEvent& event)
{
    dis= 25;
    pnum = 0;
    for (int i = 0; i < pointlist->size(); i++)
    {
        float x1 = 5 + length * pointlist->getUnchecked(i)->getX() / lastpoint;
        float y1 = 5 + 150 * (1 - pointlist->getUnchecked(i)->getY());
        Point<float> mousepoint(event.getMouseDownX(), event.getMouseDownY());
        Point<float> point(x1,y1);
        if (dis > mousepoint.getDistanceSquaredFrom(point))
        {
            dis = mousepoint.getDistanceSquaredFrom(point);
            pnum = i+1;
        }           
    }
    for (int i = 0; i < midlist->size(); i++)
    {
        float x1 = 5 + length * midlist->getUnchecked(i)->getX() / lastpoint;
        float y1 = 5 + 150 * (1 - midlist->getUnchecked(i)->getY());
        Point<float> mousepoint(event.getMouseDownX(), event.getMouseDownY());
        Point<float> point(x1,y1);
        if (dis > mousepoint.getDistanceSquaredFrom(point))
        {
            dis = mousepoint.getDistanceSquaredFrom(point);
            pnum = i+6;
        }           
    }

}

void EnvScreen::mouseDrag(const MouseEvent& event)
{
    if (pnum)
    {
        double mousex = lastpoint * (event.x - 5) / length;
        double mousey = (150-(event.y-5))*2/3;
        switch (pnum)
        {

        case 1: 
            break;
        case 2:
            attack.setValue(mousex);
            break;
        case 3 : 
            hold.setValue(mousex - p2.getX());
            break;
        case 4:
             decay.setValue(mousex - p3.getX());
             sustain.setValue(mousey);
            break;
        case 5: 
            release.setValue(mousex-p4.getX());
            break;        
        case 6: 
            if (mousey>0&&mousey<100)
            {
            midindex[0] = log10f(mousey/100)/log10f(0.5);
            midlist->getUnchecked(0)->setY(powf(0.5, midindex[0]));
            repaint();        
            }
        break; 
        case 7: 

            break;        
        case 8: 
            if (mousey > 0 && mousey < 100) {
                midindex[2] = log10f(mousey / 100) / log10f(0.5);
                m3.setY(p4.getY()+( powf(0.5, midindex[2]) * (p3.getY() - p4.getY())));
                repaint();
            }
            break;
        case 9: 
            if (mousey > 0 && mousey < 100) {
            midindex[3] = log10f(mousey / 100) / log10f(0.5);
            m4.setY(powf(0.5, midindex[3]) * p4.getY());
            repaint();
            }
            break;
        
        default:break;
        }

    }
}

void EnvScreen::initEnvScreen()
{
    for (int i = 0; i < 4; i++)
    {
        midindex[i] = 1;

    }
    lastpoint = 1;
    lockbutton.buttonstate = false;
    length = 260;
    attack.setValue(0.0005);
    hold.setValue(0);
    decay.setValue(1);
    release.setValue(0.015);
    sustain.setValue(100);
    p1.setXY(0, 0);
    p2.setXY(0.0005, 1);
    p3.setXY(0.0005, 1);
    p4.setXY(1.0, 1);
    p5.setXY(1.015, 0);
    envlenght.setValue(5);

    m1.setXY((p1.getX() + p2.getX()) / 2, powf(0.5, midindex[0]));
    m2.setXY((p2.getX() + p3.getX()) / 2, powf(1, 1));
    m3.setXY((p3.getX() + p4.getX()) / 2, 1 - (1 - powf(0.5, midindex[2]) * (p3.getY() - p4.getY())));
    m4.setXY((p4.getX() + p5.getX()) / 2, powf(0.5, midindex[3]) * p4.getY());
}
