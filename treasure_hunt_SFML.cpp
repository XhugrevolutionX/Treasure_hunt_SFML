#include <iostream>
#include <array>
#include "treasure_hunt_SFML.h"
#include "SFML/Graphics.hpp"

sf::Texture ground;
sf::Texture dug_ground;
sf::Texture chest;

int ground_size_x;
int ground_size_y;
int ground_size;
void map::initialize()
{
	tile_map.fill(tiles::k_not_dug);

	ground.loadFromFile("Assets\\Ground.png");
	dug_ground.loadFromFile("Assets\\Dug_ground.png");
	chest.loadFromFile("Assets\\Chest.png");

	ground_size_x = ground.getSize().x * 5 + 5;
	ground_size_y = ground.getSize().y * 5 + 5;
	ground_size = ground_size_x * ground_size_y;
}
void map::place_treasure()
{
	treasure = std::rand() % tile_map.size();
}
bool map::dig(int& tries, int mouse_x, int mouse_y)
{
	int x = (mouse_x / ground_size_x);
	int y = (mouse_y / ground_size_x);
	int idx = x + (map_length * y);
	bool victoire = false;

	if (tile_map.at(idx) == tiles::k_empty_dug)
	{
		system("cls");
		std::cout << "Chosen tile already dug !!\n";
	}
	else if (idx == treasure)
	{
		tile_map.at(idx) = tiles::k_treasure;
		victoire = true;
		tries++;
	}
	else
	{
		tile_map.at(idx) = tiles::k_empty_dug;
		tries++;
	}

	return victoire;

}

void map::grid_actualize(sf::RenderWindow& window, std::array<sf::Sprite, map_size>& sprite_map)
{
	sf::Sprite temp;
	for (int idx = 0; idx < (int)tile_map.size(); idx++)
	{
		switch ((int)tile_map.at(idx))
		{
		case 0:
			temp.setTexture(ground, true);
			sprite_map.at(idx) = temp;
			break;
		case 1:
			temp.setTexture(dug_ground, true);
			sprite_map.at(idx) = temp;
			break;
		case 2:
			temp.setTexture(chest, true);
			sprite_map.at(idx) = temp;
			break;
		}
		sprite_map.at(idx).setScale(5, 5);
	}
}
void map::grid_draw(sf::RenderWindow& window, int& tries, int max_tries, std::array<sf::Sprite, map_size>& arr)
{
	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text text;
	text.setFont(font);
	text.setPosition(730, 10);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::White);
	std::string str = std::to_string(tries);
	str.append("/");
	str.append(std::to_string(max_tries));
	text.setString(str);


	window.clear();
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_length; j++)
		{
			arr.at(j + (map_length * i)).setPosition(j * ground_size_x + 5, i * ground_size_y + 5);
			window.draw(arr.at(j + (map_length * i)));
		}
	}
	window.draw(text);
}
void map::end_draw(sf::RenderWindow& window, bool victory, float& counter, float& dt)
{
	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize({ 375, 150 });
	rect.setOutlineThickness(5);
	rect.setPosition(220, 335);

	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text end_text;
	end_text.setFont(font);
	end_text.setPosition(330, 345);
	end_text.setCharacterSize(50);
	end_text.setFillColor(sf::Color::Red);

	if (victory)
	{
		end_text.setString("Victory");
	}
	else
	{
		end_text.setString("Defeat");
	}

	sf::Text shutdown_text;
	shutdown_text.setFont(font);
	shutdown_text.setPosition(230, 435);
	shutdown_text.setCharacterSize(25);
	shutdown_text.setFillColor(sf::Color::Red);

	counter += dt;
	int count_down = 5 - counter;

	std::string str = "The Game will shut down in ";
	str.append(std::to_string(count_down));
	shutdown_text.setString(str);


	window.draw(rect);
	window.draw(end_text);
	window.draw(shutdown_text);
}