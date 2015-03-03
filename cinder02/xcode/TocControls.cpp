//
//  TocControls.cpp
//  cinder02
//
//  Created by Michael Oneppo on 2/15/15.
//
//

#include "TocControls.h"

using namespace ci;
using namespace ci::app;
using namespace std;

TocControls::TocControls(Toc::Ptr master) :
mMaster(master),
mResizing(false),
mMoving(false),
mInsertHover(false),
mHandle(-24, -24, 0, 0)
{}

void TocControls::Draw() {
    DrawHandle( Color( 1.0f, 1.0f, 1.0f ) );
    
    vec2 pt1 = {mMaster->Size.x - 6, mMaster->Size.y + 6};
    vec2 pt2 = {mMaster->Size.x + 6, mMaster->Size.y + 6};
    vec2 pt3 = {mMaster->Size.x + 6, mMaster->Size.y - 6};
    gl::drawLine(pt1, pt2);
    gl::drawLine(pt2, pt3);
    

}

void TocControls::DrawHandle( Color c ) {
    gl::color( c );
    vec2 center = mHandle.getCenter();
    if (mInsertHover) {
        gl::drawSolidCircle(center, (mHandle.getHeight() + 10) / 2.0f);
    } else {
        gl::drawSolidCircle(center, mHandle.getHeight() / 2.0f);
    }
}

bool TocControls::CheckAndInsert(vec2 p, Toc::Ptr toc) {
    
    if (mMaster == toc) return false;
    
    if(inHandle(p)) {
        mMaster->InsertToc(toc);
        return true;
    }
    
    for (Toc::List::iterator it = mMaster->mChildren.begin(); it != mMaster->mChildren.end(); it++) {
        vec2 localPoint = p - mMaster->Position;
        if ((*it)->Controls->CheckAndInsert(localPoint, toc)) {
            return true;
        }
    }
    
    return false;
}

bool TocControls::inHandle( vec2 p ) {
    return mHandle.contains(p);
}

bool TocControls::inResize( vec2 p ) {
    mResize = Rectf(mMaster->Size.x - 12,
                    mMaster->Size.y - 12,
                    mMaster->Size.x + 12,
                    mMaster->Size.y + 12);

    return mResize.contains(p);
}

bool TocControls::onPointerDown(PointerEvent e) {
    
    if (inHandle(e.localPosition)) {
        mMoving = true;
        Toc::Dragging = true;
        mStart = e.localPosition;

        return true;
    }
    
    if (inResize(e.localPosition)) {
        mResizing = true;
        mStart = e.localPosition - mMaster->Size;
        return true;
    }
    
    return false;
}

bool TocControls::onPointerUp(PointerEvent e) {
    bool wasControlling = mMoving || mResizing;
    
    if (mMoving) {
        for (Toc::List::iterator it = mMaster->_Roots.begin(); it != mMaster->_Roots.end(); it++) {
            vec2 pt = e.globalPosition - (*it)->Position;
            if ((*it)->Controls->CheckAndInsert(pt, mMaster)) {
                break;
            }
        }
    }

    mMoving = false;
    Toc::Dragging = false;
    mResizing = false;
    
    return wasControlling;
}

bool TocControls::onPointerMove(PointerEvent e) {
    return mMoving || mResizing;
}

bool TocControls::onPointerDrag(PointerEvent e) {
    if (mMoving) {
        mMaster->Position = e.parentPosition;
    }
    
    if (mResizing) {
        mMaster->Size = e.localPosition;
    }
    return false;
}
