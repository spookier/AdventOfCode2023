#include <iostream>
#include <string>
#include <fstream>
#include <vector>


// 1 - For each line, parse after ':' - skip space, find digits, store them until space again, save number
// until '|'

// 2 - same thing for next row except the ':'
// count same numbers 

void count_first_part(std::string &line, std::vector<int> &numbers)
{
	size_t 		i;
	std::string nbr;
	int 		number;

	i = 0;
	number = 0;
	while(i <= line.size() && line[i] != '|')
	{
		// skip non-digits
		if(!isdigit(line[i]))
			i++;

		// skip digit before ':' (ID)
		while(isdigit(line[i]) && (line[i+1] == ':' || line[i+2] == ':' || line[i+3] == ':'))
		{
			i++;
		}

		// if here, GOOD digit encountered
		if(isdigit(line[i]))
		{
			nbr += line[i];
			i++;
			if(isdigit(line[i]))
			{
				nbr += line[i];
				i++;
			}
		}
		if(!nbr.empty())
		{
			number = std::stoi(nbr);
			numbers.push_back(number);
			std::cout << "found: " << number << std::endl;
			nbr.clear();
			number = 0;
		}
	}
}


void count_second_part(std::string &line, std::vector<int> &my_numbers)
{
	size_t 		i;
	std::string nbr;
	int 		number;

	i = 0;
	number = 0;
	while(i <= line.size() && line[i] != '|')
		i++;
	while(i <= line.size())
	{
		// skip non-digits
		if(!isdigit(line[i]))
			i++;

		// skip digit before ':' (ID)
		if(isdigit(line[i]) && line[i+1] == ':')
			i++;

		// if here, GOOD digit encountered
		if(isdigit(line[i]))
		{
			nbr += line[i];
			i++;
			if(isdigit(line[i]))
			{
				nbr += line[i];
				i++;
			}
		}
		if(!nbr.empty())
		{
			number = std::stoi(nbr);
			my_numbers.push_back(number);
			number = 0;
			nbr.clear();
		}
	}
}

void compare_nbrs(std::vector<int> &numbers, std::vector<int> &my_numbers, int &points)
{
	for (size_t i = 0; i < numbers.size(); ++i)
	{
		for (size_t j = 0; j < my_numbers.size(); ++j)
		{
			if (numbers[i] == my_numbers[j])
			{
				//std::cout << "Match found: " << numbers[i] << std::endl;
				 if (points == 0) 
				 {
                    points = 1;  // First match, worth one point
                }
				else 
				{
                    points *= 2;  // Double the points for each subsequent match
                }
			}
		}
	}
}

int main(void)
{
	std::ifstream file;
	std::string line;

	std::vector<int> numbers;
	std::vector<int> my_numbers;

	int points = 0;
	int total_points = 0;

	file.open("input.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			count_first_part(line, numbers);
			count_second_part(line, my_numbers);
			compare_nbrs(numbers, my_numbers, points);

			numbers.clear();
			my_numbers.clear();

			total_points += points;
			points = 0;
		}

		std::cout << "Result: " << total_points << std::endl;
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
		return (1);
	}

	// Iterate through the vector to print numbers
	for (int num : numbers)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	for (int num : my_numbers)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
}
