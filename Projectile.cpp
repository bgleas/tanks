#include <zenilib.h>

#include "Projectile.h"

using namespace Zeni;
using namespace Zeni::Collision;

namespace Crate {
    

    
    Projectile::Projectile(const Point3f &corner_,
                 const Vector3f &scale_,
                 const Quaternion &rotation_)
    : m_source(new Sound_Source(get_Sounds()["collide"])),
    m_corner(corner_),
    m_scale(scale_),
    m_rotation(rotation_)
    {
        if(!m_instance_count)
            m_model = new Model("models/bullet.3ds");
        ++m_instance_count;

		m_velocity = Vector3f(0.0f, 0.0f, 0.0f);
        
        create_body();
    }
    
    Projectile::Projectile(const Projectile &rhs)
    : m_source(new Sound_Source(get_Sounds()["collide"])),
    m_corner(rhs.m_corner),
    m_scale(rhs.m_scale),
    m_rotation(rhs.m_rotation)
    {
        ++m_instance_count;
        
        create_body();
    }
    
    Projectile & Projectile::operator=(const Projectile &rhs) {
        m_corner = rhs.m_corner;
        m_scale = rhs.m_scale;
        m_rotation = rhs.m_rotation;
        
        create_body();
        
        return *this;
    }
    
    Projectile::~Projectile() {
        delete m_source;
        
        if(!--m_instance_count) {
            delete m_model;
            m_model = 0lu;
        }
    }

	void Projectile::set_velocity(Vector3f vel)
	{
		m_velocity = vel;
	}

	void Projectile::apply_gravity(float time_step)
	{
		float grav_strength = 1.0f * (1 - (m_corner.z / 10000));
		Vector3f gravity(0.0f, 0.0f, -1.0f * grav_strength);
		m_velocity += gravity;
		m_corner += m_velocity * time_step;

		//Bounce
		if (m_corner.z < 0)
		{
			m_velocity = -0.5f * m_velocity;
		}
		if (m_corner.z < 0 && abs(m_velocity.z) <= 0.5f )
		{
			m_corner.z = 0;
			m_velocity.z = 0;
		}
		
	}

	bool Projectile::stopped()
	{
		if (m_corner.z == 0.0f && abs(m_velocity.z) <= 0.5f)
		{
			return true;
		}
		return false;

	}
    
    void Projectile::render() {
        const std::pair<Vector3f, float> rotation = m_rotation.get_rotation();
        
        m_model->set_translate(m_corner);
        m_model->set_scale(m_scale);
        m_model->set_rotate(rotation.second, rotation.first);
        
        m_model->render();
    }
    
    void Projectile::collide() {
        if(!m_source->is_playing())
            m_source->play();
    }
    
    void Projectile::create_body() {
        m_body = Parallelepiped(m_corner,
                                m_rotation * m_scale.get_i(),
                                m_rotation * m_scale.get_j(),
                                m_rotation * m_scale.get_k());
        
        m_source->set_position(m_corner + m_rotation * m_scale / 2.0f);
    }
    
    Model * Projectile::m_model = 0;
    unsigned long Projectile::m_instance_count = 0lu;
    
}
