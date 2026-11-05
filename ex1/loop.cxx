#include <iostream>
#include <unistd.h>

int main(int argc, char **argv)
{
	std::cout << "I will now count to 10 in CPU speed";
	sleep(1);
	for (int i = 0; i <= 10;i++)
	{
		std::cout<<i<<std::endl;
	}
	sleep(1);
	return 0;
}
