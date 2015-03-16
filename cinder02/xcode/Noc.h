//
//  Noc.h
//  cinder02
//
//  Created by Michael Oneppo on 3/1/15.
//
//

#ifndef cinder02_Noc_h
#define cinder02_Noc_h

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/Path2d.h"
#include "cinder/gl/gl.h"
#include <list>
#include <stdio.h>

#include "EventReceiver.h"
#include "PaintStroke.h"

class Noc : public EventReceiver {

public:
    typedef std::shared_ptr<Noc> Ref;
    typedef std::list<Noc::Ref> List;

    Noc(ci::app::App* app);
    
    static Noc::Ref CreateRoot(ci::app::App* app);
    
    virtual ~Noc();
    
    void Draw(ci::Rectf clip);
    void PopulateFromFile(std::string name);
    void InsertNoc(Noc::Ref noc);
    void Scissor(ci::Rectf r);
    
    bool Active() {
        return _Active == shared_from_this();
    }
    
    void SetActive() {
        _Active = std::dynamic_pointer_cast<Noc> (shared_from_this());
    }
    
    static Noc::Ref GetActive() {
        return _Active;
    }
    
    ci::vec2 GlobalPosition() {
        ci::vec2 result = Position;
        Noc::Ref p = Parent;
        while(p) {
            result += p->Position;
            p = p->Parent;
        }
        
        return result;
    }
    
    void SetGlobalPosition(ci::vec2 pos) {
        ci::vec2 result = pos;
        Noc::Ref p = Parent;
        while(p) {
            result -= p->Position;
            p = p->Parent;
        }
        
        Position = result;
    }
    
    static Noc::Ref Root() {
        return _Root;
    }
    
    template<typename F>
    void ApplyToChildren(F func)
    {
        for (Noc::List::iterator it = mChildren.begin(); it != mChildren.end(); ++it)
        {
            func(*it);
            (*it)->ApplyToChildren(func);
        }
    }

    
    Noc::List Children() {return mChildren;}
    
    ci::vec2 Position;
    ci::vec2 Size;
    Noc::Ref Parent;
    
protected:
    static Noc::Ref _Active;
    static Noc::Ref _Root;
    ci::app::App* mApp;
    Noc::List mChildren;
    std::vector<PaintStroke> mStrokes;
    
};



#endif
