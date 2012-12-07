//
//  MIDIControl.h
//  leapmidi
//
//  Created by Mischa Spiegelmock on 12/5/12.
//  Copyright (c) 2012 int80. All rights reserved.
//

// This represents a MIDI control value. Each control value must have a unique, consistent
// control number and value mapped into the range of 0-127.

#ifndef __leapmidi__MIDIControl__
#define __leapmidi__MIDIControl__

#include <iostream>
#include "MIDITypes.h"

namespace LeapMIDI {
    namespace Control {
        class Base {
        public:
            // create a recognized control with raw input value from recognizer
            Base(midi_bodypart_index handIndex, midi_bodypart_index fingerIndex, midi_control_value_raw rawValue);
            
            virtual midi_control_value_raw rawValue() { return _rawValue; };
            
            // map a raw value from [minRawValue,maxRawValue] into the range [0,127]
            virtual midi_control_value mappedValue();
            
            // min/max raw value, for mapping to MIDI value
            virtual midi_control_value_raw minRawValue() { throw "minRawValue() not implemented"; };
            virtual midi_control_value_raw maxRawValue() { throw "maxRawValue() not implemented"; };

            // MIDI control code index
            virtual midi_control_index controlIndex() { throw "controlIndex() not implemented"; };
            
            virtual midi_bodypart_index handIndex()   { return _handIndex; };
            virtual midi_bodypart_index fingerIndex() { return _fingerIndex; };
            
        protected:
            midi_bodypart_index _handIndex, _fingerIndex;
            midi_control_value_raw _rawValue;
        };
    }
}

#endif /* defined(__leapmidi__MIDIControl__) */
