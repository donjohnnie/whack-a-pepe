#include "Pepe.h"

void Pepe::update(float dt, Score& score)
{
	if(state == State::Alive)
	{
		if(age >= lifespan)
		{
			set_dead();
			--score;
		}
		else
		{
			age += dt;
		}
	}
	else
	{
		if(age < dead_time)
		{
			age += dt;
		}
	}
}

void Pepe::draw(Graphics & gfx) const
{
	if( state == State::Alive )
	{
		gfx.DrawSprite( int( pos.x ), int( pos.y ), alive_pepe, chroma_key );
	}
	else if(state == State::Killed)
	{
		if( age < dead_time )
		{
			gfx.DrawSprite( int( pos.x ), int( pos.y ), killed_pepe, chroma_key );
		}
	}
}

RectF Pepe::get_hitbox() const
{
	return RectF::MakeRect(pos, float(width), float(height));
}

bool Pepe::is_dead() const
{
	return state == State::Dead ||
		state == State::Killed;
}

Vec2 Pepe::get_pos() const
{
	return pos;
}

void Pepe::set_killed()
{
	state = State::Killed;
}

void Pepe::set_dead()
{
	state = State::Dead;
	age = 0.0f;
}