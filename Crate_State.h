#ifndef CRATE_STATE_H
#define CRATE_STATE_H

#include "Crate.h"
#include "Player.h"
#include "Projectile.h"
#include <Zeni/Gamestate.h>
#include <Zeni/Timer.h>
#include <list>

namespace Crate {
    
    class Crate_State : public Zeni::Gamestate_Base {
        struct Controls {
            Controls() : forward(false), left(false), back(false), right(false) {}
            
            bool forward;
            bool left;
            bool back;
            bool right;
        } m_controls;
        
    public:
        Crate_State();
        
        void on_push();
        
        void on_key(const SDL_KeyboardEvent &event);
        void on_mouse_motion(const SDL_MouseMotionEvent &event);
        
        void perform_logic();
        
        void render();
        
    private:
        void partial_step(const float &time_step, const Zeni::Vector3f &velocity);
        
        Zeni::Time_HQ time_passed;
        
        Crate m_tank;
        Player m_player;
		std::list<Projectile*> bullets;
		//std::list<int> tree;


        
        bool m_moved;
        bool m_forward;
        bool m_backward;
        bool m_rotate_left;
        bool m_rotate_right;
		bool m_fire;
    };
    
}

#endif
