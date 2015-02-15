#include "cinder/app/AppBasic.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <vector>
#include "Toc.h"
#include "TocRoot.h"

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
    void keyDown( KeyEvent event );
    void draw();
    
    std::vector<Path2d>	mPaths;
    TocRoot::Ptr m_toc1;
    TocRoot::Ptr m_toc2;

};

void Path2dApp::setup() {
    m_toc1 = make_shared<TocRoot>(this);
    m_toc2 = make_shared<TocRoot>(this);
}

void Path2dApp::update() {
}

void Path2dApp::mouseDown( MouseEvent event )
{
  /*  Path2d p;
    mPaths.push_back(p);
    mPaths.rbegin()->moveTo(event.getPos());*/
}

void Path2dApp::mouseDrag( MouseEvent event )
{
   // mPaths.rbegin()->lineTo(event.getPos());
}

void Path2dApp::mouseUp( MouseEvent event )
{
}

void Path2dApp::keyDown( KeyEvent event )
{
    if( event.getChar() == 'x' )
        mPaths.clear();
}

void Path2dApp::draw()
{
    gl::clear( Color( 0.0f, 0.1f, 0.2f ) );
    gl::enableAlphaBlending();
    
    gl::color( Color( 1.0f, 0.5f, 0.25f ) );
    for(std::vector<Path2d>::iterator p = mPaths.begin(); p != mPaths.end(); p++) {
        if( p->getNumSegments() > 1 ) {
            gl::draw( *p , 100);
            gl::drawLine(vec2(0,0), vec2(1,1));
        
        }
    }
    
    m_toc1->Draw();
    m_toc2->Draw();
}


CINDER_APP_BASIC( Path2dApp, RendererGl )
