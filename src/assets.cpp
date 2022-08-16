#include "external/xml_parser.h"

#include "assets.h"
#include "game.h"
#include "system_paths.h"

std::map<std::string, int> Assets::assets_use_counts;
std::map<std::string, SDL_Texture *> Assets::image_cache;
std::map<std::string, Mix_Chunk *> Assets::sound_cache;
std::map<std::string, TTF_Font *> Assets::font_cache;

SDL_Texture *Assets::get_image(std::string path)
{
    if (!Assets::image_cache.contains(path) || Assets::image_cache[path] == nullptr)
    {
        SDL_Texture *texture = Game::window.load_texture(Paths::get_system_path(path + ".png"));
        Assets::image_cache[path] = texture;
    }

    Assets::assets_use_counts[path] += 1;

    return Assets::image_cache[path];
}

std::map<std::string, SDL_Rect> Assets::get_sparrow(std::string sparrow_path)
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