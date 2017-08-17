#pragma once
#include "Graphics.h"
#include "RectF.h"
#include "Score.h"


class Pepe
{
	enum class State
	{
		Alive,
		Dead,
		Killed
	};
public:
	Pepe() = default;
	Pepe(float x, float y, float lf):
		pos(Vec2(x, y)), lifespan(lf)
	{ }
	Pepe(const Vec2& pos, float lf):
		pos(pos), lifespan(lf)
	{ }

	void update(float dt, Score& score);
	void draw(Graphics& gfx) const;

	RectF get_hitbox() const;
	bool is_dead() const;
	Vec2 get_pos() const;

	void set_dead();
	void set_killed();

private:
	static constexpr int width = 60;
	static constexpr int height = 57;
	static constexpr float dead_time = 1.5f;
	float age = 0.0f;
	Vec2 pos;
	float lifespan;
	State state;
};