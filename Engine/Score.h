#pragma once
#include "RectF.h"
#include "Graphics.h"

class Score
{
public:
	Score() = default;
	Score(const Vec2& pos):
		pos(pos)
	{ }

	Score& operator++();
	Score& operator--();

	void draw(Graphics& gfx) const;

	RectF get_rect_ham() const;
	RectF get_rect_pepe() const;

	int get_ham_score() const;
	int get_pepe_score() const;

private:
	static constexpr int width = 10;
	static constexpr int height = 5;
	Vec2 pos;
	int ham = 0;
	int pepe = 0;
};