#include "sprite.h"

#include <sstream>

// Check if sprite is loaded
bool SpriteCache::_has(const std::string& sprite_id)
{
	return _cache.find(sprite_id) != _cache.end();
}

// Load a sprite given its file name without an extension and add it to the cache
bool SpriteCache::_load(const std::string& sprite_id)
{
	std::stringstream ss;

	ss << _path << sprite_id;

	sf::Texture tex;
	if (!tex.loadFromFile(ss.str()))
		return false;

	_cache[sprite_id] = std::make_shared<sf::Texture>(tex);

	return true;
}

std::shared_ptr<sf::Texture> SpriteCache::get(const std::string& sprite_id)
{
	if (!_has(sprite_id))
		_load(sprite_id);

	return _cache.at(sprite_id);
}