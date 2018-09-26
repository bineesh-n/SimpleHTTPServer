#include <iostream>
#include <cstdlib>

int main()
{
	while (true)
	{
		std::cout << "Server is running now." << std::endl;
		system("./a.exe &>>log1.txt");
		std::cout << "Server aborted.. restarting.." << std::endl;
	}

	return 0;
}
