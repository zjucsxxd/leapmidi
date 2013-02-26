/*
 *  MIDIListener.cpp
 *  LeapMIDI
 *
 *  Created by Mischa Spiegelmock on 11/28/12.
 *  Copyright (c) 2012 int80. All rights reserved.
 *
 */

#include "MIDIListener.h"

using namespace std;

namespace leapmidi {
    
Listener::Listener() {
    BallGesturePtr ballGesture = make_shared<BallGesture>();
    _gestureRecognizers.push_back(dynamic_pointer_cast<Gesture>(ballGesture));
}

void Listener::onFrame(const Leap::Controller &controller) {    
    // use current active gesture recognizers to locate gestures
    // and then trigger appropriate note/controls
    // feed frames to recognizers
    vector<GesturePtr> recognizers = gestureRecognizers();
    for (vector<GesturePtr>::iterator gesture = recognizers.begin(); gesture != recognizers.end(); ++gesture) {
        // get controls recognized from gestures
        vector<ControlPtr> gestureControls; // controls from this gesture
        (*gesture)->recognizedControls(controller, gestureControls);
        
        if (! gestureControls.size())
            continue;
        
        // call gesture recognized callback
        onGestureRecognized(controller, *gesture);
        
        for (vector<ControlPtr>::iterator ctl = gestureControls.begin(); ctl != gestureControls.end(); ++ctl) {
            onControlUpdated(controller, *gesture, *ctl);
        }
    }
}
    
// do something productive with these in your application's Listener subclass
void Listener::onGestureRecognized(const Leap::Controller &controller, GesturePtr gesture) {}
void Listener::onControlUpdated(const Leap::Controller &controller, GesturePtr gesture, ControlPtr control) {
    cout << "recognized control index " << control->controlIndex()
    << " (" << control->description() << ")"
    << ", raw value: "
    << control->rawValue() << " mapped value: " << control->mappedValue() << endl;
}
    
}
