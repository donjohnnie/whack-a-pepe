#include "Surface.h"
#include "ChiliWin.h"
#include <cassert>
#include <fstream>

Surface::Surface( const std::string & filename )
{
	std::ifstream in( filename, std::ios::binary );
	assert( in );

	BITMAPFILEHEADER bm_fileheader;
	in.read( reinterpret_cast<char*>(&bm_fileheader), sizeof( bm_fileheader ) );

	BITMAPINFOHEADER bm_infoheader;
	in.read( reinterpret_cast<char*>(&bm_infoheader), sizeof( bm_infoheader ) );

	assert( bm_infoheader.biBitCount == 24 || bm_infoheader.biBitCount == 32 );
	assert( bm_infoheader.biCompression == BI_RGB );

	width = bm_infoheader.biWidth;
	int y;
	int end;
	int dy;
	if( bm_infoheader.biHeight < 0 )
	{
		height = -bm_infoheader.biHeight;
		y = 0;
		end = height;
		dy = 1;
	}
	else
	{
		height = bm_infoheader.biHeight;
		y = height - 1;
		end = -1;
		dy = -1;
	}

	pPixels = new Color[width*height];
	in.seekg( bm_fileheader.bfOffBits );

	const int padding = (4 - (width * 3) % 4) % 4;

	for( ; y != end; y += dy )
	{
		for( int x = 0; x < width; x++ )
		{
			PutPixel( x, y, Color( in.get(), in.get(), in.get() ) );
			if( bm_infoheader.biBitCount == 32 )
			{
				in.seekg( 1, std::ios::cur );
			}
		}
		if( bm_infoheader.biBitCount == 24 )
		{
			in.seekg( padding, std::ios::cur );
		}
	}
	in.close();
}

Surface::Surface( int width, int height ):
	width( width ),
	height( height ),
	pPixels( new Color[width*height] )
{ }

Surface::Surface( const Surface& rhs ):
	Surface( rhs.width, rhs.height )
{
	int lim = width*height;
	for( int i = 0; i < lim; i++ )
	{
		pPixels[i] = rhs.pPixels[i];
	}
}

Surface::~Surface()
{
	delete[] pPixels;
	pPixels = nullptr;
}

Surface & Surface::operator=( const Surface & rhs )
{
	delete[] pPixels;
	width = rhs.width;
	height = rhs.height;
	pPixels = new Color[width*height];

	const int lim = width*height;
	for( int i = 0; i < lim; i++ )
	{
		pPixels[i] = rhs.pPixels[i];
	}
	return *this;
}

void Surface::PutPixel( int x, int y, Color c )
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < width );
	assert( y < height );
	pPixels[y * width + x] = c;
}

Color Surface::GetPixel( int x, int y ) const
{
	assert( x >= 0 );
	assert( y >= 0 );
	assert( x < width );
	assert( y < height );
	return pPixels[y*width + x];
}

int Surface::GetWidth() const
{
	return width;
}

int Surface::GetHeight() const
{
	return height;
}

void Surface::floodfill( int x, int y, Color target, Color replace )
{
	if( x < 0 || y < 0 || x >= width || y >= height ) return;
	if( target == replace ) return;
	if( GetPixel( x, y ) != target ) return;
	PutPixel( x, y, replace );
	floodfill( x, y - 1, target, replace );
	floodfill( x, y + 1, target, replace );
	floodfill( x - 1, y, target, replace );
	floodfill( x + 1, y, target, replace );
}


//Flood - fill( node, target - color, replacement - color ):
//	1. If target - color is equal to replacement - color, return.
//	2. If the color of node is not equal to target - color, return.
//	3. Set the color of node to replacement - color.
//	4. Perform Flood - fill( one step to the south of node, target - color, replacement - color ).
//	Perform Flood - fill( one step to the north of node, target - color, replacement - color ).
//	Perform Flood - fill( one step to the west of node, target - color, replacement - color ).
//	Perform Flood - fill( one step to the east of node, target - color, replacement - color ).
//	5. Return.