// Copyright 2019 Sergio Retamero.
//
// Author: Sergio Retamero (sergio.retamero@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// See http://creativecommons.org/licenses/MIT/ for more information.
//
// -----------------------------------------------------------------------------
//

#include "PrjIncludes.h"

/** @addtogroup MenuClassDefs
* @{
*/

/**
 *  \file MenuBlock.ino
 *  \brief Defines Menu functions callbacks response for Bank configuration 
 */

// Bank configuration menu. CHANGED FUNCTION NAME AND ORDER.
MenuItem BankList[] = {
    {"<-BACK", gotoMenuSettings, 1},
    {"CV", SelectCVConfig, 1},       // Hidden in Note mode
    {"FADER", SelectFaderConfig, 1}, // Shown only in Indep mode
    {"GATE", SelectGateConfig, 1},   // Hidden on Note MODE
    {"CV-FDR LINK", SelectBankFunction, 1},
    {"SCALE MODE", SelectScale, 1},
    {"CHORD TYPE", SelectChordType, 1},
    {"CHORD PRESET", SelectChordPreset, 1},
    {"SCALE ROOT", selectRootScale, 0},
    {"   CONFIG   ", NULL, 1} //Name changed!!
};
MenuList listBanks(BankList, 9, ListLines);

// Bank configuration menu
MenuItem AuxList[] = {
  { "<-BACK" , gotoMenuSettings,1   }
   , {"AUX A" , SelectAuxAConfig,1   } // Hidden in Note mode
   , {"AUX B", SelectAuxBConfig,1} // SelectCVConfig,1   } //  Shown only in Indep mode
   , {"CONFIG", NULL,1} //Name changed!!
};
MenuList listAux(AuxList, 3, ListLines);


// Function menu. REMOVED NOTE ENTRY   , {"Note" , SelectNoteMode,1   }
MenuItem BankFnList[] = {
  { "<-BACK" , gotoMenuBanks, 1   }
  , {"INDEP." , SelectIndep, 1   }
  , {"SUM" , SelectSum, 1   }
  , {"ATTE", SelectMult, 1}
  , {" CV/FAD LINK ", NULL, 1}
};
MenuList BankFnListMenu(BankFnList, 4, ListLines);


//////////////////////////
// Main Menu entry function
bool gotoMenuBanks()
{
    #ifdef CVTHING
    return SelectCVConfig();
    #else
    #endif

    MenuList *mSelected = NULL;

    PortSelected = 0;
    fullCVDisplay = false;
    if (BankSelected == 8)
        mSelected = &listAux; // Elige menu Aux
    else
        mSelected = &listBanks; // Elige menu normal

    if (BankSelected % 4 != 0)
        listButFn.disableItem(7); // Chords triggered in gates 1 and 5
    else
        listButFn.enableItem(7);

    #ifdef CVTHING
    listBanks.disableItem(2);
    #else
    // Hide Fader when in SUM or MULTIPL
    if (CVControls[BankSelected].Config.Chanfunction == SUM ||
        CVControls[BankSelected].Config.Chanfunction == MULTIPL)
    {
        listBanks.disableItem(2);
    }
    else
        listBanks.enableItem(2);
    #endif

    // Hide Gate when CV is in Note mode
    /*if (CVControls[BankSelected].CVPort.PortCfg.MIDIfunction == PITCHTRIG) {
        listBanks.disableItem (3);
    } else
        listBanks.enableItem (3);
	*/
    myMenu.ClearArea();
    myMenu.setCurrentMenu(mSelected);
    return true;
}


////////////////////////////////
// Bank configuration functions
//Activate otr deactivate Gate menu items here.
bool SelectGateConfig()
{
    PortSelected = 1;
    myMenu.ClearArea();

    listGate.disableItem(3);
    listGate.disableItem(4);
    listGate.disableItem(5);
    listGate.disableItem(6);
    listGate.disableItem(7);
    listGate.disableItem(8);

    // Show clock Div
    if (CVControls[BankSelected].GateBut.PortCfg.MIDIfunction == GATECLOCK)
    {
        listGate.enableItem(8);
    }

    // Show Note# when note gate
    // Show  Show Note# when note latch
    if (CVControls[BankSelected].GateBut.PortCfg.MIDIfunction == TRIGGER ||
        CVControls[BankSelected].GateBut.PortCfg.MIDIfunction == LATCH)
    {
        listGate.enableItem(3);
    }

    // Show CC# when note gate
    // Show  Show CC# when note latch
    if (CVControls[BankSelected].GateBut.PortCfg.MIDIfunction == CCBUT ||
        CVControls[BankSelected].GateBut.PortCfg.MIDIfunction == CCLATCH)
    {
        listGate.enableItem(4);
        listGate.enableItem(5);
    }

    myMenu.setCurrentMenu(&listGate);
    return true;
}

bool SelectAuxAConfig()
{
    PortSelected = 2;
    return SelectCVConfig();
}

bool SelectAuxBConfig()
{
    PortSelected = 3;
    return SelectCVConfig();
}

bool gotoMenuSettings()
{
    fullCVDisplay = true;
    gotoGloblaMenu = false;
    gotoGlobalCal = false;
    myMenu.ClearArea();
    myMenu.setCurrentMenu(&list1);

    GlobalCalEnabled = false;
    return true;
}

bool SelectCVConfig()
{
    if (BankSelected == 8)
    {
        if (PortSelected < 2)
            return true;
    }
    else
        PortSelected = 2;

    #ifdef CVTHING
        listAnag.enableItem(14);
        listAnag.enableItem(15);
        listAnag.enableItem(16);
    #endif
    if( CVControls[BankSelected].CVPort.PortCfg.IsDigitalFunc() ||
            CVControls[BankSelected].CVPort.PortCfg.MIDIfunction == PITCHTRIG)
        listAnag.enableItem(4);
    else listAnag.disableItem(4);

    listAnag.disableItem(6);
    listAnag.disableItem(7);
    listAnag.disableItem(8);
    listAnag.disableItem(9);
    listAnag.disableItem(10);
    listAnag.disableItem(11);
    listAnag.disableItem(12);
    // Show clock Div
    if (CVControls[BankSelected].CVPort.PortCfg.MIDIfunction == ANAGCLOCK)
    {
        listAnag.enableItem(8);
    }
    // Show NRPN
    if (CVControls[BankSelected].CVPort.PortCfg.MIDIfunction == ANAGNRPN14bits ||
        CVControls[BankSelected].CVPort.PortCfg.MIDIfunction == ANAGNRPN7bits)
    {
        listAnag.enableItem(12);
        listAnag.enableItem(10);
        listAnag.enableItem(9);
    }
    if (CVControls[BankSelected].CVPort.PortCfg.MIDIfunction == PITCH)
    {
        listAnag.enableItem(11);
    }
    myMenu.ClearArea();
    myMenu.setCurrentMenu(&listAnag);
    return true;
}

bool SelectFaderConfig()
{
    PortSelected = 3;
    listAnag2.disableItem(3);
    listAnag2.disableItem(4);
    listAnag2.disableItem(5);
    listAnag2.disableItem(6);

    // Show NRPN
    if (CVControls[BankSelected].Slider.PortCfg.MIDIfunction == ANAGNRPN7bits)
    {
        listAnag2.enableItem(4);
    }
    if (CVControls[BankSelected].Slider.PortCfg.MIDIfunction == ANAGNRPN14bits)
    {
        listAnag2.enableItem(4);
        listAnag2.enableItem(5);
    }
    if (CVControls[BankSelected].Slider.PortCfg.MIDIfunction == PITCH)
    {
        listAnag2.enableItem(6);
    }
    myMenu.ClearArea();
    myMenu.setCurrentMenu(&listAnag2);
    return true;
}

bool SelectBankFunction()
{
    myMenu.ClearArea();
    myMenu.setCurrentMenu(&BankFnListMenu);
    return true;
}


////////////////////////////////
// Bank function configuration
bool SelectIndep() {
  CVControls[BankSelected].Config.Chanfunction = INDEP;
  return gotoMenuBanks();
  /*myMenu.ClearArea();
    myMenu.setCurrentMenu(&listBanks);
    return true;*/
}

bool SelectNoteMode() {
  CVControls[BankSelected].Config.Chanfunction = NOTEMODE;
  // When NoteMode selected, CV use PITCHTRIG, Fader use Velocity and Gate is TRIGGER
  CVControls[BankSelected].CVPort.PortCfg.SetMIDIFunc(PITCHTRIG);
  CVControls[BankSelected].Slider.PortCfg.SetMIDIFunc(VELOCITY);
  CVControls[BankSelected].GateBut.PortCfg.SetMIDIFunc(TRIGGER);

  return gotoMenuBanks();
  /*myMenu.ClearArea();
    myMenu.setCurrentMenu(&listBanks);
    return true;*/
}

bool SelectSum() {
  CVControls[BankSelected].Slider.PortCfg.SetMIDIFunc(CVControls[BankSelected].CVPort.PortCfg.MIDIfunction);
  CVControls[BankSelected].Config.Chanfunction = SUM;
  return gotoMenuBanks();
  /*  myMenu.ClearArea();
    myMenu.setCurrentMenu(&listBanks);
    return true;*/
}


bool SelectMult() {
  CVControls[BankSelected].Config.Chanfunction = MULTIPL;
  CVControls[BankSelected].Slider.PortCfg.SetMIDIFunc(PERCENT);
  return gotoMenuBanks();
  /*  myMenu.ClearArea();
    myMenu.setCurrentMenu(&listBanks);
    return true;*/
}

///////////////////////////////////////////////
// Scales and Chords
bool setActiveChord()
{
    CVControls[BankSelected].Chord.setChord(myMenu.getItemStatus());
    return gotoMenuBanks();
}

// Fiil in note name in text
void DrawNoteSelection(char *outb, long val, uint16_t padpos)
{
    strncpy(outb, NotesNamesScale[val], padpos);
    //for (size_t i = strlen(NotesNamesScale[val]); i < padpos; i++){
    //    outb[i] = 0;
    //}
    outb[padpos] = 0;
    theOLED->println(outb);
}

bool selectRootScale()
{
    long val = CVControls[BankSelected].Chord.getScaleRoot();
    bool ret = myMenu.EncoderChangeLong("Scale Root:", val, 0, 11, 2, 0, 45, DrawNoteSelection);
    CVControls[BankSelected].Chord.setScaleRoot( val);
    return ret;
}


bool setActiveScale()
{

    if (SetValState == 0){
        SetValState++;
        CVControls[BankSelected].Chord.setScale(myMenu.getItemStatus());
        if(myMenu.getItemStatus()!=0) // When non full Scale selected, set major triad chord by defaut 
            CVControls[BankSelected].Chord.setChord(MAJOR);
        //myMenu.ClearArea();
        }
    if (SetValState == 1)
    {
        if (!selectRootScale())
            return false; // Select MSB
        else
            SetValState = 0;
    }

    myMenu.ClearArea();
    return SelectChordType();
}


bool SelectScale()
{
    myMenu.setCurrentMenu("SCALE MODE", ScaleLongNames, LASTSCALE-1, setActiveScale);
    return true;
}

bool SelectChordType()
{
    myMenu.ClearArea();
    if(CVControls[BankSelected].Chord.getScale()==FULL_SCALE)
        myMenu.setCurrentMenu("CHORD", ChordNames, LASTCHORD-1, setActiveChord);
    else
        myMenu.setCurrentMenu("CHORD", ChordNames, diatonicNumberOfChords+1, setActiveChord);
    return true;
}


bool SelectChordPreset()
{
    byte FIRSTBLK = BankSelected;

    // First block: CV (Note V/Oct) + Fader (+/-1 Octave) + Gate (Trigger Note)
    CVControls[FIRSTBLK].Config.Chanfunction = SUM;
    CVControls[FIRSTBLK].CVPort.PortCfg.SetMIDIFunc(PITCHTRIG);
    CVControls[FIRSTBLK].Slider.PortCfg.SetMIDIFunc(NOANFFUNC);
    CVControls[FIRSTBLK].Slider.PortCfg.Ranges.SetMIDI(-12, 24); // +/- 1 Octave
    CVControls[FIRSTBLK].Slider.PortCfg.ClipLow = -12;
    CVControls[FIRSTBLK].Slider.PortCfg.ClipHigh = 12;
    CVControls[FIRSTBLK].GateBut.PortCfg.SetMIDIFunc(TRIGGER);
    // Default CScale/Chord configuration
    CVControls[FIRSTBLK].Chord.setScale(Ionian_SCALE); // Major scale
    CVControls[FIRSTBLK].Chord.setScaleRoot(0);        // C-major scale
    CVControls[FIRSTBLK].Chord.setChord(MAJOR);        // Major triad
    CVControls[FIRSTBLK].Chord.setInvDrop(NO_INVDROP); // root voicing


    // Block: CV (CHORDINVERSION) + Fader (CHORDINVERSION)
    CVControls[FIRSTBLK + 1].Config.Chanfunction = INDEP;
    CVControls[FIRSTBLK + 1].CVPort.PortCfg.SetMIDIFunc(CHORDINVERSION);
    CVControls[FIRSTBLK + 1].CVPort.PortCfg.DestCtrl = FIRSTBLK;
    CVControls[FIRSTBLK + 1].Slider.PortCfg.SetMIDIFunc(CHORDINVERSION);
    CVControls[FIRSTBLK + 1].Slider.PortCfg.DestCtrl = FIRSTBLK;
    //CVControls[FIRSTBLK+1].Slider.PortCfg.Ranges.SetMIDI(-12, 24);
    //CVControls[FIRSTBLK+1].GateBut.PortCfg.SetMIDIFunc(TRIGGER);

    // Block: CV (SCALEROOT) + Fader (SCALEROOT)
    CVControls[FIRSTBLK + 2].Config.Chanfunction = INDEP;
    CVControls[FIRSTBLK + 2].CVPort.PortCfg.SetMIDIFunc(SCALEROOT);
    CVControls[FIRSTBLK + 2].CVPort.PortCfg.DestCtrl = FIRSTBLK;
    CVControls[FIRSTBLK + 2].Slider.PortCfg.SetMIDIFunc(SCALEROOT);
    CVControls[FIRSTBLK + 2].Slider.PortCfg.DestCtrl = FIRSTBLK;
    //CVControls[FIRSTBLK+1].Slider.PortCfg.Ranges.SetMIDI(-12, 24);
    //CVControls[FIRSTBLK+1].GateBut.PortCfg.SetMIDIFunc(TRIGGER);

    // Block: CV (SCALE_DEF) + Fader (SCALE_DEF)
    CVControls[FIRSTBLK + 3].Config.Chanfunction = INDEP;
    CVControls[FIRSTBLK + 3].CVPort.PortCfg.SetMIDIFunc(SCALE_DEF);
    CVControls[FIRSTBLK + 3].CVPort.PortCfg.DestCtrl = FIRSTBLK;
    CVControls[FIRSTBLK + 3].Slider.PortCfg.SetMIDIFunc(SCALE_DEF);
    CVControls[FIRSTBLK + 3].Slider.PortCfg.DestCtrl = FIRSTBLK;
    //CVControls[FIRSTBLK+1].Slider.PortCfg.Ranges.SetMIDI(-12, 24);
    //CVControls[FIRSTBLK+1].GateBut.PortCfg.SetMIDIFunc(TRIGGER);

    return gotoMenuBanks();
}


/** @} */
