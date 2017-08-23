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
	Pepe( float x, float y, float lf ):
		pos( Vec2( x, y ) ), lifespan( lf )
	{ }
	Pepe( const Vec2& pos, float lf ):
		pos( pos ), lifespan( lf )
	{ }

	void update( float dt, Score& score );
	void draw( Graphics& gfx ) const;
	void set_dead();
	void set_killed();

	RectF get_hitbox() const;
	Vec2 get_pos() const;

	bool is_dead() const;
private:
	static constexpr int width = 60;
	static constexpr int height = 57;
	static constexpr float dead_time = 1.5f;
	static constexpr Color chroma_key = Colors::Black;

	Vec2 pos;
	float age = 0.0f;
	float lifespan;
	State state = State::Alive;

	Surface alive_pepe = Surface( "pepe.bmp" );
	Surface killed_pepe = Surface( "deadpepe.bmp" );
};