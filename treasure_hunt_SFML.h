#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H

#include "SFML/Graphics.hpp"

enum class Tiles
{
	k_not_digged,
	k_empty_digged,
	k_treasure
};

constexpr int map_height = 5;
constexpr int map_lenght = 5;
constexpr int map_size = map_lenght * map_height;



class Map {

public:

	int treasure;

	std::array<Tiles, map_size> map;
	void Initialize();
	void Place_treasure();
	bool Dig(int& tries, int mouse_x, int mouse_y);
	void Grid_actualize(sf::RenderWindow& window, std::array<sf::Sprite, map_size>& arr);
	void Grid_draw(sf::RenderWindow& window, int& tries, int max_tries, std::array<sf::Sprite, map_size>& arr);
	void End_draw(sf::RenderWindow& window, bool victory_, float& counter_, float& dt_);
};

#endif // TREASURE_HUNT_H
