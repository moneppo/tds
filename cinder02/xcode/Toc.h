#ifndef moneppo_toc
#define moneppo_toc

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <list>
#include <stdio.h>

class TocRoot;
class TocControls;

class Toc {
public:
    
    typedef std::shared_ptr<Toc> Ptr;
    typedef std::list<Toc::Ptr> List;
    
    enum State {
        Text,
        Image,
        Settings
    };
    
    Toc( ci::app::App* app );
    Toc( std::shared_ptr<TocRoot> toc );
    
    virtual ~Toc();
    
    virtual void onPointerDown( cinder::app::MouseEvent e );
    virtual void onPointerUp( cinder::app::MouseEvent e );
    virtual void onPointerDrag( cinder::app::MouseEvent e );
    virtual void onPointerMove( cinder::app::MouseEvent e );
    
    void Draw();
    void PopulateFromFile( std::string name );
    void InsertToc( Toc::Ptr toc );
    void InsertToc( std::shared_ptr<TocRoot> toc );
    
    bool Active() { return Toc::_Active == this; }
    
    Toc::State ViewState;
    ci::Rectf Bounds;
    static bool Dragging;
    std::shared_ptr<TocControls> Controls;
    
protected:
    
    static Toc* _Active;

    
    ci::app::App* mApp;
    
    void DrawFrame();
    void DrawControls();
    
    void DrawText();
    void DrawImage();
    void DrawSettings();
    
    Toc::List mChildren;
};

#endif
