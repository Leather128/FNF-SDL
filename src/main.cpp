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

bool note_sort(Note *a, Note *b)
{
    return (abs(Conductor::song_position - a->strum_time) < abs(Conductor::song_position - b->strum_time));
}

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

	std::vector<Sprite *> strums;

	std::vector<std::string> directions;
	// bruh
	directions.push_back(std::string("left"));
	directions.push_back(std::string("down"));
	directions.push_back(std::string("up"));
	directions.push_back(std::string("right"));

	int note_width = 0;

	for (int i = 0; i < 4; i++)
	{
		Sprite *strum = new Sprite(0, Game::height - 150, "assets/images/notes/default", true);
		strum->scale = 0.7;

		strum->add_animation_by_prefix("static", directions[i] + " static0", 24, false);

		strum->add_animation_by_prefix("pressed", directions[i] + " press0", 24, false);
		strum->play_animation("pressed", true);
		strum->center_offset("pressed", "static", strum->animations["pressed"].frames.size() - 1);

		strum->add_animation_by_prefix("confirm", directions[i] + " confirm0", 24, false);
		strum->play_animation("confirm", true);
		strum->center_offset("confirm", "static");

		SDL_Rect old_offset = strum->animations["confirm"].offset;

		if (i == 0)
			strum->add_offset("confirm", {old_offset.x + -2, old_offset.y + -5, 0, 0});
		else
			strum->add_offset("confirm", {old_offset.x + -10, old_offset.y + -10, 0, 0});

		strum->play_animation("static", true);

		if (i == 0)
			note_width = strum->width * strum->scale;

		strum->x += (note_width)*i;

		strum->x += 90;
		strum->x += (Game::width / 2) * 0.5;

		Game::objects.push_back(strum);
		strums.push_back(strum);
	}

	std::string path = "assets/songs/bopeebo";
	std::string file_name = "hard";

	json song_data;
	std::ifstream file(Paths::get_system_path(path + "/" + file_name + ".json"));
	file >> song_data;
	song_data = song_data["song"];

	std::vector<Note *> waiting_notes;
	std::vector<Note *> notes;

	Sprite *strum;

	for (int section_i = 0; section_i < (int)song_data["notes"].size(); section_i++)
	{
		json section = song_data["notes"][section_i];

		for (int note_i = 0; note_i < (int)section["sectionNotes"].size(); note_i++)
		{
			json note_data = section["sectionNotes"][note_i];

			float strum_time = (float)note_data[0];
			int note_dir = (int)note_data[1] % 4;
			float sustain_length = (float)note_data[2];

			strum = strums[note_dir];

			Note *note = new Note(strum->x, -2000, "assets/images/notes/default", strum_time, note_dir, sustain_length);
			note->add_animation_by_prefix("note", directions[note_dir] + "0", 24, true);
			note->add_animation_by_prefix("hold", directions[note_dir] + " hold0", 24, true);
			note->add_animation_by_prefix("hold-end", directions[note_dir] + " hold end0", 24, true);

			note->play_animation("note", true);
			note->strum = strum;

			note->scale = 0.7f;

			waiting_notes.push_back(note);
		}
	}

	std::sort(waiting_notes.begin(), waiting_notes.end(), note_sort);

	// stop, you have violated the law!
	strum = nullptr;

	FPS *fps = new FPS(0, 0);
	Game::objects.push_back(fps);

	KeyState keys[4] = {RELEASED, RELEASED, RELEASED, RELEASED};

	Mix_Music *inst = Mix_LoadMUS(Paths::get_system_path("assets/songs/bopeebo/Inst.ogg").c_str());
	Mix_Music *voices = Mix_LoadMUS(Paths::get_system_path("assets/songs/bopeebo/Voices.ogg").c_str());

	Mix_VolumeMusicStream(inst, 64);
	Mix_VolumeMusicStream(voices, 64);

	Mix_PlayMusicStream(inst, -1);
	Mix_PlayMusicStream(voices, -1);

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

		keys[0] = Game::keyboard[SDL_SCANCODE_D];
		keys[1] = Game::keyboard[SDL_SCANCODE_F];
		keys[2] = Game::keyboard[SDL_SCANCODE_J];
		keys[3] = Game::keyboard[SDL_SCANCODE_K];

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		elapsed = (double)((NOW - LAST) * 1000.0f / (double)SDL_GetPerformanceFrequency());
		Conductor::song_position += elapsed;

		while (waiting_notes.size() > 0 && waiting_notes.front()->strum_time - Conductor::song_position <= 2500)
		{
			Game::objects.push_back(waiting_notes.front());
			notes.push_back(waiting_notes.front());
			waiting_notes.erase(waiting_notes.begin());
		}

		for (int i = 0; i < (int)strums.size(); i++)
		{
			Sprite *strum = strums[i];

			if (keys[i] == JUST_PRESSED)
			{
				strum->play_animation("pressed", true);

				for (int x = 0; x < (int)notes.size(); x++)
				{
					Note *note = notes[x];

					if (note->note_direction == i)
					{
						if (note->strum_time > Conductor::song_position - Conductor::safe_zone_offset && note->strum_time < Conductor::song_position + Conductor::safe_zone_offset)
						{
							note->~Note();
							strum->play_animation("confirm", true);
						}
					}
				}
			}
			else if (keys[i] == JUST_RELEASED)
				strum->play_animation("static", true);
			
			if ((int)keys[i] > 1)
				keys[i] = (KeyState)((int)keys[i] - 2);
		}

		Game::update(elapsed / 1000.0f);

		Game::render();
	}

	Game::window.destroy();
	SDL_Quit();
	Mix_Quit();

	return 0;
}
