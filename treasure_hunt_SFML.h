#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "SFML/Graphics.hpp"

enum class tiles
{
	k_not_dug,
	k_empty_dug,
	k_treasure
};

constexpr int map_height = 5;
constexpr int map_length = 5;
constexpr int map_size = map_length * map_height;



class map {

public:

	int treasure;

	std::array<tiles, map_size> tile_map;

	void initialize();
	void place_treasure();
	bool dig(int& tries, int mouse_x, int mouse_y);
	void grid_actualize(sf::RenderWindow& window, std::array<sf::Sprite, map_size>& sprite_map);
	void grid_draw(sf::RenderWindow& window, int& tries, int max_tries, std::array<sf::Sprite, map_size>& arr);
	void end_draw(sf::RenderWindow& window, bool victory, float& counter, float& dt);
};

#endif // TREASURE_HUNT_H
