#include <iostream>
#include <array>
#include "treasure_hunt_SFML.h"
#include "SFML/Graphics.hpp"


sf::Texture ground;
sf::Texture digged_ground;
sf::Texture chest;

int ground_size_x;
int ground_size_y;
int ground_size;
void Map::initialize()
{
	map.fill(Tiles::k_not_digged);

	ground.loadFromFile("Assets\\Ground.png");
	digged_ground.loadFromFile("Assets\\Digged_ground.png");
	chest.loadFromFile("Assets\\Chest.png");

	ground_size_x = ground.getSize().x * 0.2 + 5;
	ground_size_y = ground.getSize().y * 0.2 + 5;
	ground_size = ground_size_x * ground_size_y;
}
void Map::place_treasure()
{
	treasure = std::rand() % map.size();
	//treasure = 0;
}
bool Map::dig(int& tries, int mouse_x, int mouse_y)
{
	int x = (mouse_x / ground_size_x);
	int y = (mouse_y / ground_size_x);
	int idx = x + (map_lenght * y);
	bool victoire = false;

	if (map.at(idx) == Tiles::k_empty_digged)
	{
		system("cls");
		std::cout << "La case choisie a deja ete creuser !!\n";
	}
	else if (idx == treasure)
	{
		map.at(idx) = Tiles::k_treasure;
		victoire = true;
		tries++;
	}
	else
	{
		map.at(idx) = Tiles::k_empty_digged;
		tries++;
	}

	return victoire;

}
void Map::SFML_actualize(sf::RenderWindow& window, std::array<sf::Sprite, map_size>& arr)
{
	sf::Sprite temp;
	for (int idx = 0; idx < (int)map.size(); idx++)
	{
		switch ((int)map.at(idx))
		{
		case 0:
			temp.setTexture(ground, true);
			arr.at(idx) = temp;
			break;
		case 1:
			temp.setTexture(digged_ground, true);
			arr.at(idx) = temp;
			break;
		case 2:
			temp.setTexture(chest, true);
			arr.at(idx) = temp;
			break;
		}
		arr.at(idx).setScale(0.2, 0.2);
	}
}

void Map::display_SFML(sf::RenderWindow& window, int& tries, std::array<sf::Sprite, map_size>& arr)
{
	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text text;
	text.setFont(font);
	text.setPosition(500, 10);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	std::string str = std::to_string(tries);
	text.setString(str);


	window.clear();
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_lenght; j++)
		{
			arr.at(j + (map_lenght * i)).setPosition(j * ground_size_x + 5, i * ground_size_y + 5);
			window.draw(arr.at(j + (map_lenght * i)));
		}
	}
	window.draw(text);
}
void Map::end(sf::RenderWindow& window, bool victory_, float& counter_, float& dt_)
{
	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text end_text;
	end_text.setFont(font);
	end_text.setPosition(200, 150);
	end_text.setCharacterSize(50);
	end_text.setFillColor(sf::Color::Red);

	if (victory_)
	{
		end_text.setString("Victory");
	}
	else
	{
		end_text.setString("Defeat");
	}

	sf::RectangleShape rect;
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color::Black);
	rect.setSize({ 375, 150 });
	rect.setOutlineThickness(5);
	rect.setPosition(95, 145);


	sf::Text shutdown_text;
	shutdown_text.setFont(font);
	shutdown_text.setPosition(100, 250);
	shutdown_text.setCharacterSize(25);
	shutdown_text.setFillColor(sf::Color::Red);

	counter_ += dt_;
	int count_down = 5 - counter_;
	std::string str = "The Game will shut down in ";

	str.append(std::to_string(count_down));
	shutdown_text.setString(str);


	window.draw(rect);
	window.draw(end_text);
	window.draw(shutdown_text);
}