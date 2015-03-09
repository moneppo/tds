//
//  EventReceiver.h
//  cinder02
//
//  Created by Michael Oneppo on 3/2/15.
//
//

#ifndef __cinder02__EventReceiver__
#define __cinder02__EventReceiver__

#include <stdio.h>

struct PointerEvent {
    typedef enum {
        Left = 0,
        Right = 1,
        Tip = 2,
        Eraser = 3,
        Touch0 = 4,
        Touch1 = 5,
        Touch2 = 6,
        Touch3 = 7,
        Touch4 = 8,
        POINTER_EVENT_TYPE_SIZE = 9
    } Type;
    
    typedef std::function<void(const PointerEvent& e)> Handler;
    
    PointerEvent(ci::vec2 local, ci::vec2 parent, ci::vec2 global, Type t) :
    localPos(local),
    globalPos(global),
    parentPos(parent),
    type(t)
    {}
    
    PointerEvent inherit(ci::vec2 origin) const;
    
    ci::vec2 localPos;
    ci::vec2 globalPos;
    ci::vec2 parentPos;
    Type type;
};

class EventReceiver : public std::enable_shared_from_this<EventReceiver> {
public:
    virtual ~EventReceiver() {}
    
    typedef std::shared_ptr<EventReceiver> Ref;
    typedef std::deque<EventReceiver::Ref> Vector;
    
    bool onPointerDown(const PointerEvent& e);
    void onPointerUp(const PointerEvent& e);
    void onPointerDrag(const PointerEvent& e);
    void onPointerMove(const PointerEvent& e);
    
    void Capture(const PointerEvent& e);
    bool Captured(const PointerEvent& e);
    
    PointerEvent::Handler PointerUp;
    PointerEvent::Handler PointerDown;
    PointerEvent::Handler PointerDrag;
    PointerEvent::Handler PointerMove;
    
protected:
    static EventReceiver::Ref _Capture[PointerEvent::POINTER_EVENT_TYPE_SIZE];
    static EventReceiver::Vector _Stack;
};

#endif /* defined(__cinder02__EventReceiver__) */
