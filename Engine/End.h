#pragma once
#include "Graphics.h"
#include "Vec2.h"

class End
{
	enum class State
	{
		Won,
		Lost
	};
public:
	End() = default;
	End(const Vec2& pos):
		pos(pos)
	{ }

	void draw(Graphics& gfx) const;
	void set_state_lost();
	void set_state_won();

private:
	Vec2 pos;
	State state;
};