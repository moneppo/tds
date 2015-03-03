//
//  NocControl.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#include <stdio.h>
#include "NocControl.h"

using namespace ci;

//bool NocControl::onPointerDown(const PointerEvent& e)
//{
//    Rectf outline = Rectf(Position.x,
//                          Position.y,
//                          Position.x + Size.x,
//                          Position.y + Size.y);
//    if (outline.contains(e.globalPos)) {
//        if (PointerDown) {
//            mDragging = true;
//            return PointerDown(e);
//        } else return true;
//    }
//    
//    return false;
//}
//
//bool NocControl::onPointerUp(const PointerEvent& e)
//{
//    Rectf outline = Rectf(Position.x,
//                          Position.y,
//                          Position.x + Size.x,
//                          Position.y + Size.y);
//    if (outline.contains(e.globalPos)) {
//        if (PointerUp && mDragging) {
//            mDragging = false;
//            return PointerUp(e);
//        } else return true;
//
//    }
//    
//    return false;
//}
//
//bool NocControl::onPointerDrag(const PointerEvent& e)
//{
//    if (mDragging) {
//        if (PointerDrag) {
//            return PointerDrag(e);
//        } else return true;
//    }
//    
//    return false;
//}
//
//bool NocControl::onPointerMove(const PointerEvent& e)
//{
//    Rectf outline = Rectf(Position.x,
//                          Position.y,
//                          Position.x + Size.x,
//                          Position.y + Size.y);
//    if (outline.contains(e.globalPos)) {
//        if (PointerOver) {
//            return PointerOver(e);
//        } else return true;
//
//    }
//    
//    return false;
//}
