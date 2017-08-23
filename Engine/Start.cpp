#include "Start.h"

void Start::draw( Graphics & gfx ) const
{
	gfx.DrawSprite( int(pos.x), int(pos.y), sprite_start, chroma_key );
}