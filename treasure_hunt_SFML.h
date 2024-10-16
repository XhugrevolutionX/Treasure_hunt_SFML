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
	bool dig()
	{
		int l = 0;
		int c = 0;
		std::string answer;
		bool victoire = false;
		bool dig_end = false;
		std::string input_string;


		while (!dig_end)
		{

			bool valid_input;
			bool valid_number;

			do
			{
				do
				{
					valid_input = true;
					valid_number = false;
					std::cout << "entre ligne (un numero) entre " << 1 << "-" << map_lenght << std::endl;
					std::getline(std::cin, input_string);

					// Check if it's a number or not
					if (input_string.length() == 0 || !std::all_of(input_string.begin(), input_string.end(), ::isdigit))
					{
						system("cls");
						std::cout << input_string << " n'est pas un nombre" << std::endl;
						valid_input = false;
						display();
					}
					if (valid_input)
					{
						// Checks if number is between 1 and array size
						l = std::stoi(input_string);
						if (l > map_lenght || l < 1)
						{
							system("cls");
							valid_number = true;
							std::cout << "Ce n'est pas un chiffre entre 1-" << map_lenght << std::endl;
							display();
						}
					}
				} while (valid_number);

			} while (!valid_input);


			do
			{
				do
				{
					valid_input = true;
					valid_number = false;
					std::cout << "entre colonne (un numero) entre " << 1 << "-" << map_height << std::endl;
					std::getline(std::cin, input_string);

					// Check if it's a number or not
					if (input_string.length() == 0 || !std::all_of(input_string.begin(), input_string.end(), ::isdigit))
					{
						system("cls");
						std::cout << input_string << " n'est pas un nombre" << std::endl;
						display();
						valid_input = false;
					}
					if (valid_input)
					{
						// Checks if number is between 1 and array size
						c = std::stoi(input_string);
						if (c > map_lenght || c < 1)
						{
							system("cls");
							valid_number = true;
							std::cout << "Ce n'est pas un chiffre entre 1-" << map_lenght << std::endl;
							display();
						}
					}
				} while (valid_number);

			} while (!valid_input);


			int idx = (l - 1) * map_lenght + (c - 1);

			if (map.at(idx) == Tiles::k_empty_digged)
			{
				system("cls");
				std::cout << "La case choisie a deja ete creuser !!\n";
				display();
			}
			else if (idx == treasure)
			{
				map.at(idx) = Tiles::k_treasure;
				dig_end = true;
				victoire = true;
			}
			else
			{
				map.at(idx) = Tiles::k_empty_digged;
				dig_end = true;
			}
		}
		return victoire;

	}
	void display()
	{
		for (int idx = 0; idx < (int)map.size(); idx++)
		{
			switch ((int)map.at(idx))
			{
			case 0:
				std::cout << "X ";
				break;
			case 1:
				std::cout << "O ";
				break;
			case 2:
				std::cout << "$ ";
				break;
			}

			if (idx % map_lenght == map_lenght - 1)
			{
				std::cout << "\n";
			}
		}
	}
};

#endif // TREASURE_HUNT_H
