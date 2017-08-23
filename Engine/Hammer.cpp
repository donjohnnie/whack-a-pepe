#include "Hammer.h"

void Hammer::draw(Graphics & gfx) const
{
	switch(state)
	{
	case State::Whacking:
		gfx.DrawSprite( int( pos.x ), int( pos.y ), w_hammer, chroma_key );
		break;
	case State::NotWhacking:
		gfx.DrawSprite( int( pos.x ), int( pos.y ), nw_hammer, chroma_key );
		break;
	default:
		break;
	}
}

void Hammer::clamp()
{
	if(pos.x < 0.0f)
	{
		pos.x = 0.0f;
	}
	else if(pos.x + width  >= Graphics::ScreenWidth)
	{
		pos.x = Graphics::ScreenWidth - width - 1;
	}

	if(pos.y < 0.0f)
	{
		pos.y = 0.0f;
	}
	else if(pos.y + height >= Graphics::ScreenHeight)
	{
		pos.y = Graphics::ScreenHeight - height - 1;
	}
}

void Hammer::update(Mouse & ms, float dt)
{
	handle_input(ms);
	clamp();
}

void Hammer::handle_input(Mouse & ms)
{
	Vec2 m_pos = Vec2(float(ms.GetPosX()), float(ms.GetPosY()));
	m_pos = Vec2(m_pos.x - width / 2, m_pos.y - height / 2);
	pos = m_pos;
	if(ms.LeftIsPressed())
	{
		state = State::Whacking;
	}
	else
	{
		state = State::NotWhacking;
	}
}

void Hammer::check_pepe(Pepe & p, Score& score)
{
	if(!p.is_dead() && state == State::Whacking && get_hitbox().IsOverlappingWith(p.get_hitbox()))
	{
		++score;
		p.set_dead();
		p.set_killed();
	}
}

void Hammer::release()
{
	if(state == State::Whacking)
	{
		state = State::NotWhacking;
	}
}

RectF Hammer::get_hitbox() const
{
	return RectF::MakeRect(pos, float(hitbox), float(hitbox));
}
