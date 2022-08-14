#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer_ext.h>

#include "window.h"
#include "system_paths.h"
#include "external/xml_parser.h"

#include "game.h"
#include "sprite.h"
#include "text.h"
#include "fps.h"

#include "sparrow_helper.h"

Window Game::window;

int Game::width;
int Game::height;
TTF_Font *Game::default_font;

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		printf("DL_Init failed, Error: %s\n", SDL_GetError());
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
	
	Game::default_font = TTF_OpenFont(Paths::get_system_path("assets/fonts/vcr.ttf").c_str(), 14);

	bool running = true;

	SDL_Event event;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double elapsed = 0;

	Mix_Music *inst = Mix_LoadMUS(Paths::get_system_path("assets/songs/bopeebo/Inst.ogg").c_str());
	Mix_Music *voices = Mix_LoadMUS(Paths::get_system_path("assets/songs/bopeebo/Voices.ogg").c_str());

	Mix_VolumeMusicStream(inst, 64);
	Mix_VolumeMusicStream(voices, 64);

	Mix_PlayMusicStream(inst, -1);
	Mix_PlayMusicStream(voices, -1);

	Sprite *test = new Sprite(0, 0, "assets/images/test");
	test->set_size(0, 720);
	Game::objects.push_back(test);

	FPS *fps = new FPS(0, 0);
	Game::objects.push_back(fps);

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
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
