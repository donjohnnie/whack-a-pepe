#pragma once
#include "Vec2.h"


class RectF
{
public:
	RectF() = default;
	RectF( float left_in,float right_in,float top_in,float bottom_in );
	RectF( const Vec2& topLeft,const Vec2& bottomRight );
	RectF( const Vec2& topLeft,float width,float height );
	bool IsOverlappingWith( const RectF& other ) const;

	
	static const RectF FromCenter(const Vec2 & center, float halfWidth, float halfHeight)
	{
		halfWidth /= 2.0f;
		halfHeight /= 2.0f;
		const Vec2 half(halfWidth, halfHeight);
		return RectF(center - half, center + half);
	}

	static const RectF MakeRect(const Vec2& v, float width, float height)
	{
		return RectF(v.x, v.x + width, v.y, v.y + height);
	}

public:
	float left;
	float right;
	float top;
	float bottom;
};