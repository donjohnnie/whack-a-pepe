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
	static constexpr Color chroma_key = Color( 22, 23, 22 );

	Vec2 pos;
	State state;

	Surface sprite_won = Surface( "gamewon.bmp" );
	Surface sprite_lost = Surface( "gamelost.bmp" );

};