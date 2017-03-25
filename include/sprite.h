#ifndef sprite_h
#define sprite_h

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <memory>

static const std::map<char, int> spritemap = {
	{' ', 0}, {'.', 226}, {'-', 210}, {'|', 59}, {'@', 4}, {'+', 30}, {'}', 215}, {'>', 227},
	{'A', 20}, {'B', 36}, {'C', 52}, {'D', 68}, {'E', 84}, {'F', 100}, {'G', 116}, {'H', 132}, {'I', 148}, {'J', 164}, {'K', 180}, {'L', 196}, {'M', 212}, {'N', 228}, {'O', 244}, {'P', 5},
	{'Q', 21}, {'R', 37}, {'S', 53}, {'T', 69}, {'U', 85}, {'V', 101}, {'W', 117}, {'X', 133}, {'Y', 149}, {'Z', 165},

	{'a', 22}, {'b', 38}, {'c', 54}, {'d', 70}, {'e', 86}, {'f', 102}, {'g', 118}, {'h', 134}, {'i', 150}, {'j', 166}, {'k', 182}, {'l', 198}, {'m', 214}, {'n', 230}, {'o', 246}, {'p', 7},
	{'q', 23}, {'r', 39}, {'s', 55}, {'t', 71}, {'u', 87}, {'v', 103}, {'w', 119}, {'x', 135}, {'y', 151}, {'z', 167},
};

class SpriteCache
{
private:
	std::map<std::string, std::shared_ptr<sf::Sprite>> _cache;

	bool _has(const std::string& sprite_id);
	void _load(const std::string& sprite_id);

public:
	std::shared_ptr<sf::Sprite> get_sprite(const std::string& sprite_id);
};

#endif
