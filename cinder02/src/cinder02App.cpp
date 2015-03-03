#include "cinder/app/AppBasic.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <vector>
#include "Noc.h"
#include "HandleControl.h"

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

void Path2dApp::setup() {
    root = make_shared<Noc>(this);
    root->Size.x = 400;
    root->Size.y = 400;
    Noc::Ref child = make_shared<Noc>(this);
    root->InsertNoc(child);
    controls.push_back(make_shared<HandleControl>());
}

void Path2dApp::update() {
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->Update(0);
    }
}

void Path2dApp::mouseDown( MouseEvent event )
{
    PointerEvent p =
        PointerEvent(vec2(event.getPos()) - root->Position,
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
        PointerEvent(vec2(event.getPos()) - root->Position,
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
        PointerEvent(vec2(event.getPos()) - root->Position,
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
        PointerEvent(vec2(event.getPos()) - root->Position,
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
    
    root->Draw();
    for (NocControl::List::iterator it = controls.begin(); it != controls.end(); ++it) {
        (*it)->Draw();
    }
}


CINDER_APP_BASIC( Path2dApp, RendererGl )
