/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Hammer.h"
#include "FrameTimer.h"
#include "Pepe.h"
#include <vector>
#include <random>
#include "Start.h"
#include "End.h"


class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */

	void spawn_pepes(float dt, End& end);

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	std::random_device e;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist;
	std::uniform_real_distribution<float> yDist;
	std::uniform_real_distribution<float> pepe_lifespan;
	static constexpr int max_pepes = 30;
	static constexpr float d_spawn = 0.8f;
	float spawn_time = d_spawn;
	float time = 0.0f;

	Hammer hammer;
	std::vector<Pepe> pepes;
	Score score;
	Start start;
	End end;
	bool started = false;
	bool game_over = false;
	/********************************/
	/*  User Variables              */
	/********************************/
};