#include <iostream>
#include <string>
#include <map>

int main()
{
	std::cout	<< "MODULE 22 | Task 02" << std::endl
				<< "Electronic queue" << std::endl
				<< "-------------------" << std::endl << std::endl;
	
	std::map<std::string, int> queue;

	std::string value;

	while (std::cin >> value)
	{
		if (value == "stop" || value == "exit")
		{
			return 0;
		}
		else if (value == "help")
		{
			std::cout	<< "Available commands:" << std::endl
						<< "exit, stop\t- ends the program" << std::endl
						<< "help\t\t- displays a list of available commands." << std::endl
						<< "next\t\t- displays the last name of the next person in alphabetical order." << std::endl
						<< "[last name/first name/identifier] - enter the queue by last name/first name/identifier" <<std::endl
						<< "if you enter the last name, first name and identifier of the same person separately, it will be added to the queue exactly as many times as the value was entered" << std::endl << std::endl;

		}
		else if (value == "Next" || value == "next" || value == "NEXT")
		{
			if (!queue.empty())
			{
				auto _it = queue.begin();
				std::cout << "NEXT > " << _it->first << std::endl;

				if (--_it->second == 0)
					queue.erase(_it);
			}
			else
			{
				std::cerr << "There is no one in the queue" << std::endl;
			}
		}
		else
		{
			queue[value]++;
		}
	}
	return 0;
}