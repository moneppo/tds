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
Noc::Ref Noc::_Root = nullptr;

PointerEvent PointerEvent::inherit(vec2 origin) const
{
    return PointerEvent(
        localPos - origin,
        localPos,
        globalPos,
        type);
}

Noc::Ref Noc::CreateRoot(ci::app::App* app)
{
    auto result = make_shared<Noc>(app);
    result->Position = vec2(0,0);
    result->Size = app->getWindowSize();
    _Root = result;
    return result;
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
            (*it)->onPointerDown(childEvent);
            if (_Capture[childEvent.type] != nullptr)
                return;
        }
        
       
        if ( e.localPos.x <= Size.x &&
            e.localPos.y <= Size.y &&
            e.localPos.x > 0 &&
            e.localPos.y > 0)
        {
            Capture(e);
            
            
            auto paintStroke = PaintStroke();
            paintStroke.AddPoint(e.localPos);
            mStrokes.push_back(paintStroke);
            
            SetActive();
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
        
        
        if (Captured(e) &&
            e.localPos.x <= Size.x &&
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

void Noc::Scissor(Rectf scissorRect) {
    float h = mApp->getWindowHeight();
    vec2 p = {scissorRect.x1, h - scissorRect.y2};
    gl::scissor(p, scissorRect.getSize());
   // gl::color(1,0,0,.1);
   // gl::drawSolidRect({-10000, -10000, 10000, 10000});
}

void Noc::Draw(Rectf clip) {
    gl::pushModelMatrix();
    gl::translate(Position.x, Position.y);
    
    if ( Active() ) {
        gl::color(Color(1.0f, 1.0f, 1.0f));
    } else {
        gl::color(Color(0.5f, 0.5f, 0.5f));
    }
    
    gl::drawStrokedRect(Rectf(0, 0, Size.x, Size.y));
    
    Rectf localClip = Rectf(Position + clip.getUpperLeft(),
                            Position + clip.getUpperLeft() + Size);
    Rectf newClip = localClip.getClipBy(clip);
    Scissor(newClip);
    
    for (vector<PaintStroke>::iterator it = mStrokes.begin(); it != mStrokes.end(); ++it) {
        it->Draw();
    }
    
    for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++) {
        (*it)->Draw(newClip);
    }
    
    gl::popModelMatrix();
    Scissor(clip);
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