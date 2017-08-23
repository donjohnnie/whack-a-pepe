#pragma once
#include "Colors.h"
#include <string>

class Surface
{
public:
	Surface( const std::string& filename );
	Surface( int width,int height );
	Surface( const Surface& rhs);
	~Surface();
	Surface& operator=( const Surface& );
	void PutPixel( int x,int y,Color c );
	Color GetPixel( int x,int y ) const;
	int GetWidth() const;
	int GetHeight() const;

	void floodfill( int x, int y, Color target, Color replace );

private:
	Color* pPixels = nullptr;
	int width;
	int height;
};