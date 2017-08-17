/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	xDist(70, 730),
	yDist(70, 530),
	pepe_lifespan(0.3f, 0.6f),
	rng(e()),
	hammer(400, 400),
	score(Vec2(0, 0)),
	start(Vec2(200, 200)),
	end(Vec2(350, 200))
{ }

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const auto dt = ft.Mark();
	hammer.update(wnd.mouse, dt);
	for(auto& pepe : pepes)
	{
		pepe.update(dt, score);
		hammer.check_pepe(pepe, score);
	}
	spawn_pepes(dt);
}

void Game::spawn_pepes(float dt)
{
	if(started)
	{
		if(!game_over)
		{
			if(pepes.size() <= max_pepes)
			{
				time += dt;
				if(time >= spawn_time)
				{
					if(pepes.size() == 0)
					{
						pepes.push_back(Pepe(xDist(rng), yDist(rng), pepe_lifespan(rng)));
						wnd.mouse.set_left_false();
					}
					else
					{
						Vec2 pos;
						do
						{
							pos.x = xDist(rng);
							pos.y = yDist(rng);

						} while((pos - pepes.back().get_pos()).GetLengthSq() < 160 * 160);
						pepes.push_back(Pepe(pos, pepe_lifespan(rng)));
						wnd.mouse.set_left_false();
					}
					spawn_time += d_spawn;
				}
			}
			else
			{
				if(score.get_ham_score() / 2 <= score.get_pepe_score())
				{
					end.set_state_lost();
				}
				else
				{
					end.set_state_won();
				}
				game_over = true;
			}
		}
	}
	else
	{
		if(wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			started = true;
		}
	}
}

void Game::ComposeFrame()
{
	if(started)
	{
		if(!game_over)
		{
			for(auto& pepe : pepes)
			{
				pepe.draw(gfx);
			}
			score.draw(gfx);
			hammer.draw(gfx);
		}
		else
		{
			end.draw(gfx);
		}
	}
	else
	{
		start.draw(gfx);
	}
}
