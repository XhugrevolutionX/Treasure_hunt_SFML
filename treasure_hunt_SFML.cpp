#include <iostream>
#include <array>
#include "treasure_hunt_SFML.h"
#include "SFML/Graphics.hpp"

void Map::initialize()
{
	map.fill(Tiles::k_not_digged);
}
void Map::place_treasure()
{
	treasure = std::rand() % map.size();
	//treasure = 0;
}
bool Map::dig(sf::RenderWindow& window, sf::Event& event, int& tries)
{
	int x = 0;
	int y = 0;
	int idx = 0;
	bool victoire = false;


	if (event.mouseButton.button == sf::Mouse::Button::Left && event.type == sf::Event::MouseButtonPressed)
	{
		x = (sf::Mouse::getPosition(window).x / 100);
		y = (sf::Mouse::getPosition(window).y / 100);
		idx = x + (map_lenght * y);

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
	}


	return victoire;

}
void Map::display_SFML(sf::RenderWindow& window, int& tries)
{
	std::array<sf::RectangleShape, map_size> arr;
	sf::RectangleShape temp(sf::Vector2f(90, 90));
	temp.setOutlineThickness(5);

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

	window.clear();
	for (int i = 0; i < map_height; i++)
	{
		for (int j = 0; j < map_lenght; j++)
		{
			arr.at(j + (map_lenght * i)).setPosition(10 + j * 100, 10 + i * 100);
			window.draw(arr.at(j + (map_lenght * i)));
		}
	}
	window.draw(text);
	window.display();

}

void Map::end(sf::RenderWindow& window, bool victory_)
{
	sf::Font font;
	if (!font.loadFromFile("Assets\\BrownieStencil.ttf"))
	{

	}

	sf::Text text;
	text.setFont(font);
	text.setPosition(175, 250);
	text.setCharacterSize(50);
	text.setFillColor(sf::Color::Red);

	if (victory_)
	{
		text.setString("Victory");
	}
	else
	{
		text.setString("Defeat");
	}

	window.clear();
	window.draw(text);
	window.display();

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == event.MouseButtonPressed || event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
}