#ifndef TREASURE_HUNT_H
#define TREASURE_HUNT_H



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

	void initialize()
	{
		map.fill(Tiles::k_not_digged);
	}
	void place_treasure()
	{
		treasure = std::rand() % map.size();
		//treasure = 0;
	}
	bool dig(sf::RenderWindow& window, sf::Event& event, int& tries)
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
	void display_SFML(sf::RenderWindow& window)
	{
		std::array<sf::RectangleShape, map_size> arr;
		sf::RectangleShape temp(sf::Vector2f(90, 90));
		temp.setOutlineThickness(5);

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
			for (int j = 0;  j < map_lenght;  j++)
			{
				arr.at(j + (map_lenght * i)).setPosition(10+j*100,10+i * 100);
				window.draw(arr.at(j + (map_lenght * i)));
			}
		}
		window.display();

	}
};

#endif // TREASURE_HUNT_H
