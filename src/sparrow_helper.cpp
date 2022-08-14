#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <map>
#include <string>

#include "external/xml_parser.h"

#include "sparrow_helper.h"
#include "system_paths.h"

/**
 * @brief Returns a std::map<std::string, SDL_Rect> of animation frame names to their coordinates
 * on a spritesheet (with ones with an appended _offsets after for storing offsets)
 * 
 * @TODO: Possibly change the _offests system to a custom container of 2 SDL_Rect(s)?
 * 
 * @param sparrow_path 
 * @return std::map<std::string, SDL_Rect> 
 */
std::map<std::string, SDL_Rect> SparrowHelper::get_sparrow(std::string sparrow_path)
{
    std::map<std::string, SDL_Rect> map = {};

    if (sparrow_path.ends_with(".xml"))
        sparrow_path = sparrow_path.substr(0, sparrow_path.find_last_of(".xml") - 3);

    XMLNode main_node = XMLNode::openFileHelper(Paths::get_system_path(sparrow_path + ".xml").c_str(), "TextureAtlas");

    int frame_count = main_node.nChildNode("SubTexture");

    for (int i = 0; i < frame_count; i++)
	{
		XMLNode frame_data = main_node.getChildNode("SubTexture", i);

		SDL_Rect frame_rect = {
            std::atoi(frame_data.getAttribute("x")),
            std::atoi(frame_data.getAttribute("y")),
            std::atoi(frame_data.getAttribute("width")),
            std::atoi(frame_data.getAttribute("height"))};

        if (frame_data.isAttributeSet("frameX"))
        {
            SDL_Rect frame_offset_rect = {
                std::atoi(frame_data.getAttribute("frameX")),
                std::atoi(frame_data.getAttribute("frameY")),
                std::atoi(frame_data.getAttribute("frameWidth")),
                std::atoi(frame_data.getAttribute("frameHeight"))};

            map[std::string(frame_data.getAttribute("name")) + "_offsets"] = frame_offset_rect;
        }
        else
        {
            SDL_Rect frame_offset_rect = {
                0,
                0,
                frame_rect.w,
                frame_rect.h};

            map[std::string(frame_data.getAttribute("name")) + "_offsets"] = frame_offset_rect;
        }

        map[frame_data.getAttribute("name")] = frame_rect;
	}

    return map;
}