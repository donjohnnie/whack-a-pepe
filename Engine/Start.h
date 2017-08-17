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
	Vec2 pos;
};