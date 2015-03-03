#include "Toc.h"
#include "TocControls.h"
#include "TocRoot.h"

using namespace ci;
using namespace ci::app;
using namespace std;

Toc* Toc::_Active = nullptr;
bool Toc::Dragging = false;
Toc::List Toc::_Roots = Toc::List();

Toc::Toc( App* app ) :
    mApp( app ),
    Controls(make_shared<TocControls>(Toc::Ptr(this))),
    Position(100, 100),
    Size(100, 100),
    Parent(nullptr)
{}

Toc::Toc( TocRoot::Ptr toc ) :
    ViewState(toc->ViewState),
    Position(toc->Position),
    Size(toc->Size),
    Controls(toc->Controls),
    mChildren(toc->mChildren),
    mApp(toc->mApp)
{
    if (toc->Active()) {
        _Active = this;
    }
}

Toc::Ptr Toc::Create( ci::app::App* app ) {
    auto result = make_shared<Toc>( app );
    result->Ref = result;
    return result;
}

Toc::Ptr Toc::CreateFromRoot( TocRoot::Ptr toc ) {
    auto result = make_shared<Toc>( toc );
    result->Ref = result;
    return result;
}

Toc::~Toc() {
}

void Toc::InsertToc(Toc::Ptr toc) {
    if (Parent) {
        Parent->mChildren.remove(toc);
    } else {
        _Roots.remove(toc);
    }
    mChildren.push_back(toc);
    toc->Position.x = 10;
    toc->Position.y = 10;
    toc->Parent = Ref;
}

void Toc::InsertToc( TocRoot::Ptr toc ) {
    auto newToc = CreateFromRoot(toc);
    mChildren.push_back(newToc);
    _Roots.remove(toc);
    newToc->Position.x = 10;
    newToc->Position.y = 10;
}

void Toc::Draw() {
    Rectf r = Rectf(0, 0, Size.x, Size.y);
    
    gl::pushModelMatrix();
    gl::translate(Position.x, Position.y);

    if ( Active() ) {
        gl::color( Color( 1.0f, 1.0f, 1.0f ) );
        gl::drawStrokedRect( r );
        
        Controls->Draw();
    } else {
        gl::color( Color( 0.5f, 0.5f, 0.5f ) );
        gl::drawStrokedRect( r );
        
        if (Dragging) {
            Controls->DrawHandle( Color(0.5f, 0.5f, 0.5f ) );
        }
    }
    
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        (*it)->Draw();
    }
    gl::popModelMatrix();
    
}

void Toc::DrawAll() {
    for ( Toc::List::iterator it = _Roots.begin(); it != _Roots.end(); it++ ) {
        (*it)->Draw();
    }
}

void Toc::PopulateFromFile( string name ) {
    
}

bool Toc::onPointerDown( PointerEvent e )
{
    vec2 p = e.localPosition;
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc* toc = it->get();
        PointerEvent evt;
        evt.parentPosition = e.localPosition;
        evt.localPosition = e.localPosition - toc->Position;
        evt.globalPosition = e.globalPosition;
        evt.type = e.type;
        vec2 pt = evt.localPosition;

        if ( toc->Active() && toc->Controls->onPointerDown( evt ) )
        {
            return true;
        }
        
        if ( pt.x <= Size.x &&
             pt.y <= Size.y &&
             pt.x > 0 &&
             pt.y > 0)
        {
            return toc->onPointerDown( evt );
        }
    }
    
   
    if (p.x <= Size.x &&
        p.y <= Size.y &&
        p.x > 0 &&
        p.y > 0)
    {
        if (!Active()) {
            _Active = this;
        } else {
            // This is where drawing happens
        }
        return true;
    }
    
    return false;
    
}

bool Toc::onPointerUp( PointerEvent e)
{

    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc::Ptr toc = *it;
        PointerEvent evt;
        evt.parentPosition = e.localPosition;
        evt.localPosition = e.localPosition - toc->Position;
        evt.globalPosition = e.globalPosition;
        evt.type = e.type;
        vec2 p = evt.localPosition;
        
        if (toc->Active() && toc->Controls->onPointerUp(evt)) {
            return true;
        }

        if ( p.x <= Size.x &&
             p.y <= Size.y &&
             p.x > 0 &&
             p.y > 0)
        {
            return toc->onPointerUp( evt );
        }
    }
    
    return false;
}

bool Toc::onPointerDrag( PointerEvent e )
{
    for ( Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++ ) {
        Toc::Ptr toc = *it;
        PointerEvent evt;
        evt.parentPosition = e.localPosition;
        evt.localPosition = e.localPosition - toc->Position;
        evt.globalPosition = e.globalPosition;
        evt.type = e.type;
        vec2 p = evt.localPosition;
        
        if ( toc->Active() && toc->Controls->onPointerDrag( evt ) ) {
            return true;
        }

        if ( p.x <= Size.x &&
            p.y <= Size.y &&
            p.x > 0 &&
            p.y > 0)
        {
            return toc->onPointerDrag( evt );
        }
    }
    
    return false;
}

bool Toc::onPointerMove( PointerEvent e )
{
    for (Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); it++) {
        Toc::Ptr toc = *it;
        PointerEvent evt;
        evt.parentPosition = e.localPosition;
        evt.localPosition = e.localPosition - toc->Position;
        evt.globalPosition = e.globalPosition;
        evt.type = e.type;
        vec2 p = evt.localPosition;
        
        if ( toc->Active() && toc->Controls->onPointerMove( evt ) ) {
            return true;
        }

        if ( p.x <= Size.x &&
            p.y <= Size.y &&
            p.x > 0 &&
            p.y > 0)
        {
            return toc->onPointerMove( evt );
        }
    }
    
    return false;
}