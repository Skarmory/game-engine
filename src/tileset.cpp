#include "tileset.h"

#include <iostream>
#include <sstream>

#include "environment.h"

//const Tileset& TilesetLoader::load(const std::string& tileset)
//{
//	std::stringstream ss;
//	std::string ts_path;
//	ss << _path << tileset;
//	ts_path = ss.str();
//
//	rapidxml::file<> file(ts_path.c_str());
//	rapidxml::xml_document<> data;
//
//	data.parse<0>(file.data);
//
//	Tileset ts;
//	int position = 0;
//
//	auto node = data.first_node();
//	auto child_node = node->first_node();
//	while (child_node)
//	{
//		if (child_node->name() == "count")
//		{
//			ts = Tileset(atoi(child_node->value()));
//		}
//		if (child_node->name() == "tiles")
//		{
//			auto tile = child_node->first_node();
//			while (tile)
//			{
//				auto tdata = tile->first_node();
//				if (tdata->first_node()->name() == "tex")
//				{
//					std::shared_ptr<sf::Sprite> sprite =  Environment::get().get_sprite_cache()->get_sprite(tdata->first_node()->value());
//					ts.add(position, sprite);
//					position++;
//				}
//			}
//		}
//
//		child_node = child_node->next_sibling();
//	}
//
//	return ts;
//}