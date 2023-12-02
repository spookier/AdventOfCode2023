#include <iostream>
#include <string>
#include <fstream>

void check_values(std::string &combined_digits, std::string &color, int &MAX_RED, int &MAX_GREEN, int &MAX_BLUE)
{
	// Does the value fit in the context of the question ?
	// [ 12 red cubes, 13 green cubes, and 14 blue cubes ]

	std::string color_answers = "RGB";
	int digit_to_int;

	if (color_answers.find(color) != std::string::npos)
	{
		if (color == "R")
		{
			digit_to_int = std::stoi(combined_digits);

			if (MAX_RED < digit_to_int)
				MAX_RED = digit_to_int;
		}
		else if (color == "G")
		{
			digit_to_int = std::stoi(combined_digits);

			if (MAX_GREEN < digit_to_int)
				MAX_GREEN = digit_to_int;
		}
		else if (color == "B")
		{
			digit_to_int = std::stoi(combined_digits);

			if (MAX_BLUE < digit_to_int)
				MAX_BLUE = digit_to_int;
		}
	}

}

std::string is_color(std::string &line, size_t i)
{
	if (line.substr(i, 3) == "red")
		return ("R");
	else if (line.substr(i, 5) == "green")
		return ("G");
	else if (line.substr(i, 4) == "blue")
		return("B");
	else
		return ("X");
}

ssize_t find_possible_game(std::string &line, ssize_t &res)
{
	size_t 		i;
	std::string color;

	std::string digit1;
	std::string digit2;
	std::string combined_digits;

	std::string id_digit1;
	std::string id_digit2;
	std::string combined_id;

	int MAX_RED		= 0;
	int MAX_GREEN	= 0;
	int MAX_BLUE	= 0;


	// get ID for the entire subset
	i = 0;
	while(i <= line.size() && line[i] != ':')
	{
		if (std::isdigit(line[i]))
		{
			id_digit1 = line[i];
			i++;
			if (i <= line.size() && std::isdigit(line[i]))
			{
				id_digit2 = line[i];
				combined_id = id_digit1 + id_digit2;
				i++;
			}
			else
				combined_id = id_digit1;

			break ;
		}
		i++;
	}

	while (i < line.size() && (line[i] == ':' || std::isspace(line[i]))) 
		i++;

	// FOR EACH SUBSET !
	// ---------------------

	while (i <= line.size())
	{
		// First, get the value and store it inside combined_digits
		while (i <= line.size() && (line[i] != ',' && line[i] != ';'))
		{
			if (std::isdigit(line[i]))
			{
				digit1 = line[i];
				i++;
				if (i <= line.size() && std::isdigit(line[i]))
				{
					digit2 = line[i];
					combined_digits = digit1 + digit2;
					i++;
				}
				else
					combined_digits = digit1;

				break;
			}
			i++;
		}

		// We got the first value, now we need the color (stored in color)
		while (i <= line.size() && (line[i] != ',' && line[i] != ';'))
		{
			color = is_color(line, i);
			if (color != "X")
				break;
			i++;
		}

		// @DEBUG - error check
		if(color == "X")
		{
			std::cout << "COLOR ERROR!" << std::endl;
			exit(-1);
		}

		check_values(combined_digits, color, MAX_RED, MAX_GREEN, MAX_BLUE);

		i++;
	}

	// ---------------------


	// If arrives until here it means the game would have been possible, so add the ID
	std::cout << MAX_RED << " | " << MAX_GREEN << " | " << MAX_BLUE << std::endl;;
	res += MAX_RED * MAX_BLUE * MAX_GREEN;
	return(0);
}


int main()
{
	std::ifstream file;
	std::string line;
	ssize_t res;
	
	res = 0;
	file.open("input.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			find_possible_game(line, res);
		}
		std::cout << "RES: " << res << std::endl;
		return (0);
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return (1);
	}
}
