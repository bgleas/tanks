#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <Zeni/Collision.h>
#include <Zeni/Model.h>
#include <Zeni/Quaternion.h>
#include <Zeni/Sound.h>
#include <Zeni/Vector3f.h>
#include <utility>

namespace Crate {
    
    class Projectile {
    public:
        Projectile(const Zeni::Point3f &corner_ = Zeni::Point3f(0.0f, 0.0f, 0.0f),
              const Zeni::Vector3f &scale_ = Zeni::Vector3f(1.0f, 1.0f, 1.0f),
              const Zeni::Quaternion &rotation_ = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0.0f, 0.0f, 1.0f), 0.0f));
        Projectile(const Projectile &rhs);
        Projectile & operator=(const Projectile &rhs);
        ~Projectile();
        
        void render();
        
        void collide();
        
        const Zeni::Collision::Parallelepiped & get_body() const {return m_body;}

		void set_velocity(Zeni::Vector3f);
        
		void apply_gravity(float time_step);

		bool stopped();

private:
        void create_body();
        
        // Level 1
        static Zeni::Model * m_model;
        static unsigned long m_instance_count;
        
        Zeni::Sound_Source * m_source;
        
        // Level 2
        Zeni::Point3f m_corner;
        Zeni::Vector3f m_scale;
        Zeni::Quaternion m_rotation;
		Zeni::Vector3f m_velocity;
        
        // Level 3
        Zeni::Collision::Parallelepiped m_body; // not motion so much as collision
        
        // Level 4
        // A stationary Projectile has no controls
    };
    
}

#endif
