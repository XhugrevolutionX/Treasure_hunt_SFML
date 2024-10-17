#include <iostream>
#include <array>
#include "treasure_hunt_SFML.h"
#include "SFML/Graphics.hpp"

constexpr int square_size = 90;
constexpr int border_size = 5;
int full_size = square_size + (2 * border_size);

void Map::initialize()
{
	map.fill(Tiles::k_not_digged);
}
void Map::place_treasure()
{
	treasure = std::rand() % map.size();
	//treasure = 0;
}
bool Map::dig(int& tries, int mouse_x, int mouse_y)
{
	int x = (mouse_x / full_size);
	int y = (mouse_y / full_size);
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
void Map::SFML_actualize(sf::RenderWindow& window, std::array<sf::RectangleShape, map_size>& arr)
{
	sf::RectangleShape temp(sf::Vector2f(square_size, square_size));
	temp.setOutlineThickness(border_size);

	for (int idx = 0; idx < (int)map.size(); idx++)
	{
		switch ((int)map.at(idx))
		{
		case 0:
			temp.setFillColor(sf::Color::White);
			temp.setOutlineColor(sf::Color::Black);
			arr.at(idx) = temp;
			break;
		case 1:
			temp.setFillColor(sf::Color::Black);
			temp.setOutlineColor(sf::Color::White);
			arr.at(idx) = temp;
			break;
		case 2:
			temp.setFillColor(sf::Color::Yellow);
			temp.setOutlineColor(sf::Color::Green);
			arr.at(idx) = temp;
			break;
		}
	}
}

void Map::display_SFML(sf::RenderWindow& window, int& tries, std::array<sf::RectangleShape, map_size>& arr)
{
	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text text;
	text.setFont(font);
	text.setPosition(450, 10);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);
	std::string str = std::to_string(tries);
	text.setString(str);

	window.clear();
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_lenght; j++)
		{
			arr.at(j + (map_lenght * i)).setPosition(10 + j * full_size, 10 + i * full_size);
			window.draw(arr.at(j + (map_lenght * i)));
		}
	}
	window.draw(text);
}
void Map::end(sf::RenderWindow& window, bool victory_)
{
	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text end_text;
	end_text.setFont(font);
	end_text.setPosition(175, 250);
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

	sf::Text shutdown_text;
	shutdown_text.setFont(font);
	shutdown_text.setPosition(20, 350);
	shutdown_text.setCharacterSize(25);
	shutdown_text.setFillColor(sf::Color::Red);
	shutdown_text.setString("The Game will shut down in 5 seconds");


	window.draw(end_text); 
	window.draw(shutdown_text);
}