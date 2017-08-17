#include "Score.h"

Score & Score::operator++()
{
	ham++;
	return *this;
}

Score & Score::operator--()
{
	pepe++;
	return *this;
}

void Score::draw(Graphics & gfx) const
{
	gfx.DrawRect(get_rect_ham(), Colors::Red);
	gfx.DrawRect(get_rect_pepe(), Colors::Green);
}

RectF Score::get_rect_ham() const
{
	return RectF::MakeRect(pos, width, ham*height);
}

RectF Score::get_rect_pepe() const
{
	return RectF::MakeRect(Vec2(pos.x + width+1, pos.y), width, pepe*height);
}

int Score::get_ham_score() const
{
	return ham;
}

int Score::get_pepe_score() const
{
	return pepe;
}
