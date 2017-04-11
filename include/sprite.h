#ifndef sprite_h
#define sprite_h

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

class SpriteCache
{
private:
	const std::string _path = "resources/tex/";
	std::unordered_map<std::string, std::shared_ptr<sf::Texture>> _cache;

	bool _has(const std::string& sprite_id);
	bool _load(const std::string& sprite_id);

public:
	std::shared_ptr<sf::Texture> get(const std::string& sprite_id);
};

#endif
