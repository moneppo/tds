#include "cinder/app/AppBasic.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <vector>
#include "Noc.h"
#include "HandleControl.h"
#include "ResizeControl.h"
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

    Noc::Ref root;
    NocControl::List controls;
};

// TODO: INSERT TOC

void Path2dApp::setup() {
    root = Noc::CreateRoot(this);
    controls.push_back(make_shared<HandleControl>());
    controls.push_back(make_shared<ResizeControl>());
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
            Noc::Ref n = make_shared<Noc>(this);
            root->InsertNoc(n);
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
    
    root->onPointerDown(p);
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
    
    root->onPointerDrag(p);

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
    root->onPointerUp(p);

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
    root->onPointerMove(p);
}

void Path2dApp::keyDown( KeyEvent event )
{
}

void Path2dApp::draw()
{
    gl::clear( Color( 0.0f, 0.1f, 0.2f ) );
    gl::enable(GL_SCISSOR_TEST);
    gl::enableAlphaBlending();
    
    root->Draw(getWindowBounds());
    
    gl::scissor(vec2(0,0), getWindowSize());

    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->Draw();
    }
}


CINDER_APP_BASIC( Path2dApp, RendererGl )
