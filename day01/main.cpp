#include <iostream>
#include <string>
#include <fstream>

// If substr exists, return them as single string digits for easier handling
std::string is_str_number(std::string &line, size_t i)
{
	if (line.substr(i, 3) == "one")
		return ("1");
	else if (line.substr(i, 3) == "two")
		return ("2");
	else if (line.substr(i, 5) == "three")
		return ("3");
	else if (line.substr(i, 4) == "four")
		return ("4");
	else if (line.substr(i, 4) == "five")
		return ("5");
	else if (line.substr(i, 3) == "six")
		return ("6");
	else if (line.substr(i, 5) == "seven")
		return ("7");
	else if (line.substr(i, 5) == "eight")
		return ("8");
	else if (line.substr(i, 4) == "nine")
		return ("9");
	else
		return ("0");
}

int find_digits(std::string &line)
{
	std::string n1;
	std::string n2;
	std::string combined_nums;
	int number;
	size_t i;
	ssize_t j;
	std::string ret_value;

	// Iterate through the string until first digit is met
	i = 0;
	while (i <= line.size())
	{
		if (std::isdigit(line[i]))
		{
			n1 = line[i];
			break;
		}
		ret_value = is_str_number(line, i);
		if (ret_value > "0")
		{
			n1 = ret_value;
			break;
		}
		i++;
	}

	// REVERSE iterate through the string until the first digit is met
	j = line.size();
	while (j >= 0)
	{
		if (std::isdigit(line[j]))
		{
			n2 = line[j];
			break;
		}
		ret_value = is_str_number(line, j);
		if (ret_value > "0")
		{
			n2 = ret_value;
			break;
		}
		j--;
	}

	// Convert them to int
	combined_nums = n1 + n2;
	number = std::stoi(combined_nums);
	return (number);
}

int main()
{
	std::ifstream file;
	size_t calibration_value;
	int add;
	std::string line;

	calibration_value = 0;

	file.open("input.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			add = find_digits(line);
			calibration_value += add;
		}
		std::cout << calibration_value << std::endl;
		return (0);
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return (1);
	}
}
