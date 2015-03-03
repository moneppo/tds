//
//  EventReceiver.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/2/15.
//
//


#include "EventReceiver.h"

using namespace std;

EventReceiver::Ref EventReceiver::_Capture[PointerEvent::POINTER_EVENT_TYPE_SIZE];
EventReceiver::Vector EventReceiver::_Stack = EventReceiver::Vector();

bool EventReceiver::onPointerDown(const PointerEvent& e)
{
    if (_Capture[e.type] == nullptr && PointerDown) {
        PointerDown(e);
    }
    
    return _Capture[e.type] != nullptr;
}

void EventReceiver::onPointerUp(const PointerEvent& e)
{
    if (_Capture[e.type].get() == this && PointerUp) {
        PointerUp(e);
    }
    
    _Capture[e.type] = nullptr;
}

void EventReceiver::onPointerDrag(const PointerEvent& e)
{
    if (_Capture[e.type].get() == this && PointerDrag) {
        PointerDrag(e);
    }
}

void EventReceiver::onPointerMove(const PointerEvent& e)
{
    if (PointerMove) PointerMove(e);
}

void EventReceiver::Capture(const PointerEvent& e)
{
    _Capture[e.type] = shared_from_this();
}