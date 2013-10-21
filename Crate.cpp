#include <zenilib.h>

#include "Crate.h"

using namespace Zeni;
using namespace Zeni::Collision;

namespace Crate {
    

    
    Crate::Crate(const Point3f &corner_,
                 const Vector3f &scale_,
                 const Quaternion &rotation_)
    : m_source(new Sound_Source(get_Sounds()["collide"])),
    m_corner(corner_),
    m_scale(scale_),
    m_rotation(rotation_)
    {
        if(!m_instance_count)
            m_model = new Model("models/tank.3ds");
        ++m_instance_count;

		cannon_rotation = m_rotation;
		cannon_power = 200.0f;
        
        create_body();
    }
    
    Crate::Crate(const Crate &rhs)
    : m_source(new Sound_Source(get_Sounds()["collide"])),
    m_corner(rhs.m_corner),
    m_scale(rhs.m_scale),
    m_rotation(rhs.m_rotation)
    {
        ++m_instance_count;
        
        create_body();
    }
    
    Crate & Crate::operator=(const Crate &rhs) {
        m_corner = rhs.m_corner;
        m_scale = rhs.m_scale;
        m_rotation = rhs.m_rotation;
        
        create_body();
        
        return *this;
    }
    
    Crate::~Crate() {
        delete m_source;
        
        if(!--m_instance_count) {
            delete m_model;
            m_model = 0lu;
        }
    }
    
    void Crate::render() {
        const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
        
        m_model->set_translate(m_corner);
        m_model->set_scale(m_scale);
        m_model->set_rotate(rotation.second, rotation.first);
        
        m_model->render();
    }
    
    void Crate::collide() {
        if(!m_source->is_playing())
            m_source->play();
    }
    
    void Crate::create_body() {
        m_body = Parallelepiped(m_corner,
                                m_rotation * m_scale.get_i(),
                                m_rotation * m_scale.get_j(),
                                m_rotation * m_scale.get_k());
        
        m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
    }
    
    void Crate::move_forward(){
		
		float angle = m_rotation.get_rotation().second;

		float dist_x = -3.0f * cos(angle);
		float dist_y = 3.0f * sin(angle);
		        
		m_corner.x += dist_x;
		m_corner.y += dist_y;
    }

    void Crate::move_back(){
		float angle = m_rotation.get_rotation().second;

		float dist_x = -3.0f * cos(angle);
		float dist_y = 3.0f * sin(angle);
		        
		m_corner.x -= dist_x;
		m_corner.y -= dist_y;
    }
    
    void Crate::turn_left(){
        m_rotation = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0, 0, 1), 3.14/30) * m_rotation;
        cannon_rotation = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0, 0, 1), 3.14/30) * cannon_rotation;
        
    }
    
    void Crate::turn_right(){
        m_rotation = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0, 0, 1), -3.14/30) * m_rotation;
        cannon_rotation = Zeni::Quaternion::Axis_Angle(Zeni::Vector3f(0, 0, 1), -3.14/30) * cannon_rotation;
    }
    
	
	Projectile * Crate::fire(){
		Projectile *proj = new Projectile(m_corner, Vector3f(15.0f, 15.0f, 15.0f));
		float projectile_angle = cannon_rotation.get_rotation().second;
		Vector3f initial_velocity(-1.0f * cannon_power*cos(projectile_angle), cannon_power*sin(projectile_angle), cannon_power*sin(3.14/2));
		proj->set_velocity(initial_velocity);
		return proj;
	}
	

    
    
    Model * Crate::m_model = 0;
    unsigned long Crate::m_instance_count = 0lu;
    
}
