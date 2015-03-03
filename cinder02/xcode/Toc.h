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

struct PointerEvent {
    typedef enum {
      Left,
      Right,
      Tip,
      Eraser,
      Touch
    } Type;
    ci::vec2 localPosition;
    ci::vec2 globalPosition;
    ci::vec2 parentPosition;
    Type type;
};

class Toc {
public:
    
    friend class TocControls;
    
    typedef std::shared_ptr<Toc> Ptr;
    typedef std::list<Toc::Ptr> List;
    
    static Ptr Create( ci::app::App* app );
    static Toc::Ptr CreateFromRoot( std::shared_ptr<TocRoot> toc );
    
    enum State {
        Text,
        Image,
        Settings
    };
    
    Toc( ci::app::App* app );
    Toc( std::shared_ptr<TocRoot> toc );
    
    virtual ~Toc();
    
    virtual bool onPointerDown( PointerEvent e );
    virtual bool onPointerUp( PointerEvent e );
    virtual bool onPointerDrag( PointerEvent e );
    virtual bool onPointerMove( PointerEvent e );
    
    static void DrawAll();
    
    void Draw();
    void PopulateFromFile( std::string name );
    void InsertToc( Toc::Ptr toc );
    void InsertToc( std::shared_ptr<TocRoot> toc );
    
    template<typename F>
    void ApplyToAll(F method) {
        for (Toc::List::iterator it = _Roots.begin(); it != _Roots.end(); ++it) {
            method(*it);
            (*it)->ApplyToChildren(method);
        }
    }
    
    template<typename F>
    void ApplyToChildren(F method) {
        for (Toc::List::iterator it = mChildren.begin(); it != mChildren.end(); ++it) {
            method(*it);
            (*it)->ApplyToChildren(method);
        }
    }
    
    bool Active() { return Toc::_Active == this; }
    
    Toc::State ViewState;
    ci::vec2 Position;
    ci::vec2 Size;
    static bool Dragging;
    Toc::Ptr Parent;
    Toc::Ptr Ref;
    std::shared_ptr<TocControls> Controls;

protected:
    
    static Toc* _Active;
    static Toc::List _Roots;

    ci::app::App* mApp;
    
    void DrawFrame();
    void DrawControls();
    
    void DrawText();
    void DrawImage();
    void DrawSettings();
    
    Toc::List mChildren;
};

#endif
