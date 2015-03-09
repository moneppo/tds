//
//  Noc.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#include <stdio.h>
#include "Noc.h"

using namespace std;
using namespace ci;

Noc::Ref Noc::_Active = nullptr;

PointerEvent PointerEvent::inherit(vec2 origin) const
{
    return PointerEvent(
        localPos - origin,
        localPos,
        globalPos,
        type);
}

Noc::Noc(ci::app::App* app) :
mApp(app),
Position(100, 100),
Size(100, 100),
Parent(nullptr)
{
    PointerDown = [&](const PointerEvent& e)
    {
        for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
            PointerEvent childEvent = e.inherit((*it)->Position);
            if ((*it)->onPointerDown(childEvent)) {
                return;
            }
        }
        
        if ( e.localPos.x <= Size.x &&
            e.localPos.y <= Size.y &&
            e.localPos.x > 0 &&
            e.localPos.y > 0)
        {
            SetActive();
            Capture(e);
            auto paintStroke = PaintStroke();
            paintStroke.AddPoint(e.localPos);
            mStrokes.push_back(paintStroke);
        }

    };
    
    PointerUp = [&](const PointerEvent& e)
    {
        for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
            PointerEvent childEvent = e.inherit((*it)->Position);
            (*it)->onPointerUp(childEvent);
        }
        
        if ( e.localPos.x <= Size.x &&
            e.localPos.y <= Size.y &&
            e.localPos.x > 0 &&
            e.localPos.y > 0)
        {
            // Stop drawing
        }
    };
    
    PointerDrag = [&](const PointerEvent& e)
    {
        for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
            PointerEvent childEvent = e.inherit((*it)->Position);
            (*it)->onPointerDrag(childEvent);
        }
        
        if (e.localPos.x <= Size.x &&
            e.localPos.y <= Size.y &&
            e.localPos.x > 0 &&
            e.localPos.y > 0)
        {
            mStrokes[mStrokes.size() - 1].AddPoint(e.localPos);
        }
    };
    
    PointerMove = [&](const PointerEvent& e)
    {
        for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
            PointerEvent childEvent = e.inherit((*it)->Position);
            (*it)->onPointerMove(childEvent);
        }
    };
}

Noc::~Noc()
{}

void Noc::Draw(vec2 offset) {
    Rectf r = Rectf(0, 0, Size.x, Size.y);
    gl::pushModelMatrix();
    gl::translate(Position.x, Position.y);
    
    if ( Active() ) {
        gl::color(Color(1.0f, 1.0f, 1.0f));
    } else {
        gl::color(Color(0.5f, 0.5f, 0.5f));
    }
    gl::drawStrokedRect(r);
    
    for (vector<PaintStroke>::iterator it = mStrokes.begin(); it != mStrokes.end(); ++it) {
        it->Draw();
    }
    
    for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++) {
        vec2 base = offset + Position;
        base.y = mApp->getWindowHeight() - (base.y + Size.y);
        gl::scissor(base, Size);
        (*it)->Draw(offset + Position);
    }
    gl::popModelMatrix();
    if (!Parent) {
        gl::scissor(vec2(0,0), mApp->getWindowSize());
    }

}

void Noc::PopulateFromFile(std::string name) {
    
}

void Noc::InsertNoc(Noc::Ref noc) {
    if (noc->Parent) {
        noc->Parent->mChildren.remove(noc);
    }
    
    mChildren.push_back(noc);
    noc->Parent = dynamic_pointer_cast<Noc>(shared_from_this());
}