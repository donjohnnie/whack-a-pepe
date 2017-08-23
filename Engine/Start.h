#pragma once
#include "Graphics.h"
#include "Vec2.h"


class Start
{
public:
	Start() = default;
	Start(const Vec2& pos):
		pos(pos)
	{ }

	void draw(Graphics& gfx) const;

private:
	static constexpr Color chroma_key = Color( 22, 23, 22 );

	Vec2 pos;

	Surface sprite_start = Surface( "diamondpepe.bmp" );
};