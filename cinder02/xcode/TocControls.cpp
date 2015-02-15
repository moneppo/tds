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
mMoving(false)
{
    Update();
}

void TocControls::Draw() {
    DrawHandle( Color( 1.0f, 1.0f, 1.0f ) );
        
    vec2 pt1 = {mMaster->Bounds.x2 - 6, mMaster->Bounds.y2 + 6};
    vec2 pt2 = {mMaster->Bounds.x2 + 6, mMaster->Bounds.y2 + 6};
    vec2 pt3 = {mMaster->Bounds.x2 + 6, mMaster->Bounds.y2 - 6};
    gl::drawLine(pt1, pt2);
    gl::drawLine(pt2, pt3);
}

void TocControls::DrawHandle( Color c ) {
    gl::color( c );
    vec2 center = mHandle.getCenter();
    gl::drawSolidCircle(center, mHandle.getHeight() / 2.0f);

}

void TocControls::Update() {
    mHandle = Rectf(mMaster->Bounds.x1 - 24,
                    mMaster->Bounds.y1 - 24,
                    mMaster->Bounds.x1,
                    mMaster->Bounds.y1);
    
    mResize = Rectf(mMaster->Bounds.x2 - 12,
                    mMaster->Bounds.y2 - 12,
                    mMaster->Bounds.x2 + 12,
                    mMaster->Bounds.y2 + 12);
}

bool TocControls::inHandle( vec2 p ) {
    return mHandle.contains(p);
}

bool TocControls::onPointerDown(MouseEvent e) {
    Update();
    vec2 pos = e.getPos();
    
    if (inHandle(pos)) {
        mMoving = true;
        Toc::Dragging = true;
        mRel = pos - mMaster->Bounds.getUpperLeft();
        return true;
    }
    
    if (mResize.contains(pos)) {
        mResizing = true;
         mRel = pos - mMaster->Bounds.getLowerRight();
        return true;
    }
    
    return false;
}

bool TocControls::onPointerUp(MouseEvent e) {
    Update();
    bool wasControlling = mMoving || mResizing;
    
    mMoving = false;
    Toc::Dragging = false;
    mResizing = false;
    
    return wasControlling;
}

bool TocControls::onPointerMove(MouseEvent e) {
    Update();
    return mMoving || mResizing;
}

bool TocControls::onPointerDrag(MouseEvent e) {
    Update();
    if (mMoving) {
        vec2 size = mMaster->Bounds.getSize();
        vec2 pos = e.getPos();
        pos -= mRel;
        mMaster->Bounds.set(pos.x, pos.y, pos.x + size.x, pos.y + size.y);
    }
    
    if (mResizing) {
        vec2 pos = e.getPos();
        pos -= mRel;
        mMaster->Bounds.x2 = pos.x;
        mMaster->Bounds.y2 = pos.y;
    }
    
    return false;
}
