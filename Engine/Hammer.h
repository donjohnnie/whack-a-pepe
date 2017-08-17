#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Mouse.h"
#include "Pepe.h"
#include "Score.h"

class Hammer
{
	enum class State
	{
		Whacking,
		NotWhacking
	};
public:
	Hammer() = default;
	Hammer(float x, float y):
		pos(Vec2(x, y))
	{ }

	void draw(Graphics& gfx) const;
	void draw_nw(Graphics& gfx) const;
	void draw_w(Graphics& gfx) const;
	void clamp();
	void update(Mouse& ms, float dt);
	void handle_input(Mouse& ms);
	void check_pepe(Pepe& m, Score& score);
	void release();

	RectF get_hitbox() const;

private:
	static constexpr int width = 103;
	static constexpr int height = 103;
	static constexpr int hitbox = 65;
	Vec2 pos;
	State state = State::NotWhacking;
	Score score;
};