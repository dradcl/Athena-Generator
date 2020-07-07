#include <iostream>
#include <limits>
#include "Generator.h"

int main(void)
{
	unsigned int choice = 0;
	bool validChoice = false;

	std::cout << "---Options---\n[0] Generate all cosmetics\n[1] Generate new cosmetics only\n";

	do
	{
		if (!(std::cin >> choice) || choice > 1) // forces choices to be 0 or 1
		{
			std::cout << "Invalid input, try again" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else
		{
			if (choice) // 1
			{
				std::cout << "Generating new.." << std::endl;
				generate(true);
			}
			else // 0
			{
				std::cout << "Generating all.." << std::endl;
				generate();
			}
			validChoice = true;
		}
	} 
	while (!validChoice);

	return 0;
}