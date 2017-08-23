#include "End.h"

void End::draw(Graphics & gfx) const
{
	if( state == State::Won )
	{
		gfx.DrawSprite( int(pos.x), int(pos.y), sprite_won, chroma_key );
	}
	else if( state == State::Lost )
	{
		gfx.DrawSprite( int(pos.x), int(pos.y), sprite_lost, chroma_key );
	}
}

void End::set_state_lost()
{
	state = State::Lost;
}

void End::set_state_won()
{
	state = State::Won;
}
