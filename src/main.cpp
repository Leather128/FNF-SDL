#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <array>
#include <fstream>
#include <list>
#include <bits/stdc++.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

#include "window.h"
#include "system_paths.h"
#include "external/xml_parser.h"
#include "external/json.hpp"

#include "game.h"
#include "sprite.h"
#include "text.h"
#include "fps.h"
#include "conductor.h"
#include "note.h"

Window Game::window;

int Game::width;
int Game::height;
TTF_Font *Game::default_font;
std::map<int, KeyState> Game::keyboard;

double Conductor::song_position;
double Conductor::safe_zone_offset;

using json = nlohmann::json;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		printf("SDL_Init failed, Error: %s\n", SDL_GetError());
	if (!IMG_Init(IMG_INIT_PNG))
		printf("IMG_Init failed, Error: %s\n", SDL_GetError());
	if (TTF_Init() != 0)
		printf("TTF_Init failed, Error: %s\n", SDL_GetError());
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		printf("Mix_OpenAudio failed, Error: %s\n", Mix_GetError());

	Paths::init();

	Game::width = 1280;
	Game::height = 720;

	Game::window = Window("Friday Night Funkin'", Game::width, Game::height);
	Game::init();

	Conductor::safe_zone_offset = (10.0f / 60.0f) * 1000.0f;

	Game::default_font = TTF_OpenFont(Paths::get_system_path("assets/fonts/vcr.ttf").c_str(), 14);

	bool running = true;

	SDL_Event event;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double elapsed = 0;

	FPS *fps = new FPS(0, 0);
	Game::objects.push_back(fps);

	while (running)
	{
		for (int i = 0; i < /*SDL_NUM_SCANCODES*/ 290; i++)
		{
			int key_int = (int)Game::keyboard[i];

			if (key_int > 1)
				Game::keyboard[i] = (KeyState)(key_int - 2);
		}

		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				if (Game::keyboard[event.key.keysym.scancode] != PRESSED)
					Game::keyboard[event.key.keysym.scancode] = JUST_PRESSED;
				break;
			case SDL_KEYUP:
				Game::keyboard[event.key.keysym.scancode] = JUST_RELEASED;
				break;
			default:
				break;
			}
		}

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		elapsed = (double)((NOW - LAST) * 1000.0f / (double)SDL_GetPerformanceFrequency());

		Game::update(elapsed / 1000.0f);

		Game::render();
	}

	Game::window.destroy();
	SDL_Quit();
	Mix_Quit();

	return 0;
}
