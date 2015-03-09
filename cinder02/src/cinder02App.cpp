#include "cinder/app/AppBasic.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <vector>
#include "Noc.h"
#include "HandleControl.h"
#include "PaintStroke.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class Path2dApp : public AppBasic {
public:
    
    Path2dApp() {}
    
    void setup();
    void update();
    
    void mouseDown( MouseEvent event );
    void mouseUp( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseMove( MouseEvent event );
    void keyDown( KeyEvent event );
    void draw();

    Noc::List roots;
    NocControl::List controls;
};

// TODO: RESIZE
//       HIERARCHY DRAWING
//       ROOT AS FULL SCREEN
//       INSERT TOC

void Path2dApp::setup() {
    auto root = make_shared<Noc>(this);
    root->Position = vec2(40,40);
    root->Size = vec2(200,200);
    Noc::Ref child = make_shared<Noc>(this);
    root->InsertNoc(child);
    roots.push_back(root);
    controls.push_back(make_shared<HandleControl>());
    auto newControl = make_shared<NocControl>();
    newControl->Size = vec2(20,20);
    newControl->Position = vec2(0, 0);
    newControl->PointerDown = [=](PointerEvent e){
        if ( e.localPos.x <= newControl->Size.x &&
            e.localPos.y <= newControl->Size.y &&
            e.localPos.x > 0 &&
            e.localPos.y > 0)
        {
            newControl->Capture(e);
        }
    };
    newControl->PointerUp = [=](PointerEvent e) {
        if (newControl->Captured(e)) {
            Noc::Ref root = make_shared<Noc>(this);
            roots.push_back(root);
        }
    };
    controls.push_back(newControl);
    
}

void Path2dApp::update() {
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->Update(0);
    }
}

void Path2dApp::mouseDown( MouseEvent event )
{
    PointerEvent p =
        PointerEvent(vec2(event.getPos()),
                     event.getPos(),
                     event.getPos(),
                     PointerEvent::Left);
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->onPointerDown(p);
    }
    for (Noc::List::iterator it = roots.begin(); it != roots.end(); ++it) {
        PointerEvent rootPoint = p.inherit((*it)->Position);
        (*it)->onPointerDown(rootPoint);
    }
}

void Path2dApp::mouseDrag( MouseEvent event )
{
    PointerEvent p =
        PointerEvent(vec2(event.getPos()),
                 event.getPos(),
                 event.getPos(),
                 PointerEvent::Left);
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->onPointerDrag(p);
    }
    for (Noc::List::iterator it = roots.begin(); it != roots.end(); ++it) {
        PointerEvent rootPoint = p.inherit((*it)->Position);
        (*it)->onPointerDrag(rootPoint);
    }

}

void Path2dApp::mouseUp( MouseEvent event )
{
   PointerEvent p =
        PointerEvent(vec2(event.getPos()),
                 event.getPos(),
                 event.getPos(),
                 PointerEvent::Left);
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->onPointerUp(p);
    }
    for (Noc::List::iterator it = roots.begin(); it != roots.end(); ++it) {
        PointerEvent rootPoint = p.inherit((*it)->Position);
        (*it)->onPointerUp(rootPoint);
    }

}

void Path2dApp::mouseMove( MouseEvent event )
{
    PointerEvent p =
        PointerEvent(vec2(event.getPos()),
                 event.getPos(),
                 event.getPos(),
                 PointerEvent::Left);
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->onPointerMove(p);
    }
    for (Noc::List::iterator it = roots.begin(); it != roots.end(); ++it) {
        PointerEvent rootPoint = p.inherit((*it)->Position);
        (*it)->onPointerMove(rootPoint);
    }
}

void Path2dApp::keyDown( KeyEvent event )
{
}

void Path2dApp::draw()
{
    gl::clear( Color( 0.0f, 0.1f, 0.2f ) );
    gl::enable(GL_SCISSOR_TEST);
    gl::enableAlphaBlending();
    
    for (Noc::List::iterator it = roots.begin(); it != roots.end(); ++it) {
        (*it)->Draw();
    }

    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->Draw();
    }
}


CINDER_APP_BASIC( Path2dApp, RendererGl )
