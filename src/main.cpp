#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "window.h"
#include "paths.h"

#include "xmlParser.h"

#include "memory_usage.h"

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		printf("Oh yeah btw SDL_Init just failed :3 %s\n", SDL_GetError());
	if (!IMG_Init(IMG_INIT_PNG))
		printf("Oops IMG_Init failed! %s\n", SDL_GetError());
	if (TTF_Init() != 0)
		printf("Oh no! TTF_Init failed! %s\n", SDL_GetError());

	Uint64 start_tick = SDL_GetTicks64();
	Uint64 end_tick = 0;

	Paths::init();

	XMLNode xMainNode = XMLNode::openFileHelper(Paths::get_system_path("assets/images/characters/bfAssets.xml").c_str(), "TextureAtlas");

	int anims = xMainNode.nChildNode("SubTexture");

	std::vector<SDL_Rect> bf_frames = {};
	std::vector<SDL_Rect> bf_frame_offsets = {};

	for (int i = 0; i < anims; i++)
	{
		XMLNode animNode = xMainNode.getChildNode("SubTexture", i);

		if (std::string(animNode.getAttribute("name")).rfind("BF idle dance0", 0) == 0)
		{
			SDL_Rect frame_rect = {
				std::atoi(animNode.getAttribute("x")),
				std::atoi(animNode.getAttribute("y")),
				std::atoi(animNode.getAttribute("width")),
				std::atoi(animNode.getAttribute("height"))};

			if (animNode.isAttributeSet("frameX"))
			{
				SDL_Rect frame_offset_rect = {
					std::atoi(animNode.getAttribute("frameX")),
					std::atoi(animNode.getAttribute("frameY")),
					std::atoi(animNode.getAttribute("frameWidth")),
					std::atoi(animNode.getAttribute("frameHeight"))};

				bf_frame_offsets.push_back(frame_offset_rect);
			}
			else
			{
				SDL_Rect frame_offset_rect = {
					0,
					0,
					frame_rect.w,
					frame_rect.h};

				bf_frame_offsets.push_back(frame_offset_rect);
			}

			bf_frames.push_back(frame_rect);
		}
	}

	end_tick = SDL_GetTicks64();

	printf("took game %i ms to process xml data!\n", (int)(end_tick - start_tick));

	Window window("Friday Night Funkin'", 1280, 720);

	SDL_Texture *bf_assets = window.load_texture(Paths::get_system_path("assets/images/characters/bfAssets.png"));
	
	TTF_Font *Sans = TTF_OpenFont(Paths::get_system_path("assets/fonts/vcr.ttf").c_str(), 14);
	SDL_Color White = {255, 255, 255};

	end_tick = SDL_GetTicks64();

	std::string fps_text = "FPS: 0";

	SDL_Surface *surfaceMessage = NULL;
	SDL_Texture *Message = NULL;

	SDL_Rect message_rect = {10, 3, 0, 0};

	double current_frame_time = 0;
	std::vector<double> frame_times = {};
	int fps = 0;

	double last_framerate_check = -1000;

	std::vector<std::string> scans = {};
	std::vector<double> scan_times = {};

	double bf_last_anim_time = 0;
	double bf_anim_interval = 1000 / 24;
	int bf_anim_frame = 0;

	SDL_Rect bf_pos = {0, 0, 0, 0};
	SDL_Rect *bf_src = &bf_frames[bf_anim_frame];

	bf_pos.w = bf_src->w;
	bf_pos.h = bf_src->h;

	bool running = true;

	SDL_Event event;

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double elapsed = 0;

	end_tick = SDL_GetTicks64();

	double bf_fly_time = 0;

	printf("took game %i ms to start!\n", (int)(end_tick - start_tick));

	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				running = false;
			
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.repeat == 0)
				{
					scans.push_back(std::to_string(event.key.keysym.scancode));
					scan_times.push_back(current_frame_time);
				}
			}
		}

		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();

		elapsed = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());

		bf_fly_time += (elapsed / 1000.0f) * 1.5f;
		current_frame_time += elapsed;

		if (current_frame_time > bf_last_anim_time + bf_anim_interval)
		{
			bf_anim_frame++;
			bf_last_anim_time = current_frame_time;

			bf_anim_frame = bf_anim_frame % bf_frames.size();
		}

		frame_times.push_back(current_frame_time);

		while (frame_times.size() > 0 && frame_times[0] < current_frame_time - 1000)
		{
			frame_times.erase(frame_times.begin());
		}

		while (scan_times.size() > 0 && scan_times[0] < current_frame_time - 1000)
		{
			scan_times.erase(scan_times.begin());
			scans.erase(scans.begin());
		}

		fps = frame_times.size();

		window.clear();

		if (current_frame_time > last_framerate_check + 1000)
		{
			std::stringstream stream;
			stream << "FPS: " << fps << "\nMemory: " << (int)(getCurrentRSS() / 104857.6f)/10.0f << "mb / " << (int)(getPeakRSS() / 104857.6f)/10.0f << "mb";

			for (int i = 0; i < (int)scans.size(); i++)
			{
				stream << "\n" << scans[i];
			}

			fps_text = stream.str();
			
			last_framerate_check = current_frame_time;

			if (surfaceMessage != NULL)
				SDL_FreeSurface(surfaceMessage);
			if (Message != NULL)
				SDL_DestroyTexture(Message);

			surfaceMessage = TTF_RenderText_Blended_Wrapped(Sans, fps_text.c_str(), White, 1280);
			Message = SDL_CreateTextureFromSurface(window.renderer, surfaceMessage);

			SDL_QueryTexture(Message, NULL, NULL, &message_rect.w, &message_rect.h);
		}

		bf_pos.x = (Uint64)(360 + (cos(bf_fly_time) * 360.0f));
		bf_pos.y = (Uint64)(120 + (sin(2.0f * bf_fly_time) * 120.0f));

		bf_src = &bf_frames[bf_anim_frame];

		bf_pos.w = bf_src->w;
		bf_pos.h = bf_src->h;

		bf_pos.x -= bf_frame_offsets[bf_anim_frame].x;
		bf_pos.y -= bf_frame_offsets[bf_anim_frame].y;

		for (int i = 0; i < 1; i++)
		{
			if (bf_pos.y < 720)
				window.render(bf_assets, bf_src, &bf_pos);
			else
				break;

			bf_pos.x += 25;

			if (bf_pos.x != bf_pos.x % 1280)
			{
				bf_pos.x = 0;
				bf_pos.y += 150;
			}
		}

		window.render(Message, &message_rect);

		window.display();
	}

	window.destroy();
	SDL_Quit();

	return 0;
}
