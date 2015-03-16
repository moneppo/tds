//
//  DecoratorControl.cpp
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#include "DecoratorControl.h"

using namespace ci;
using namespace std;

void DecoratorControl::Update(float t)
{
    Noc::Ref n = mFollowActive ? Noc::GetActive() : mNoc;
    if (!n) return;
    vec2 pos = n->GlobalPosition();
    vec2 size = n->Size;
    if (mOffset.x < 0) {
        Position.x = pos.x - mOffset.x * (size.x + Size.x) + size.x;
    } else {
        Position.x = pos.x + mOffset.x * (size.x + Size.x) - Size.x;
    }
    
    if (mOffset.y < 0) {
        Position.y = pos.y - mOffset.y * (size.y + Size.y) + size.y;
    } else {
        Position.y = pos.y + mOffset.y * (size.y + Size.y) - Size.y;
    }
}

void DecoratorControl::Draw()
{
    if (mFollowActive && !Noc::GetActive())
        return;
    
    NocControl::Draw();
}