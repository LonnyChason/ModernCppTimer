#include "ModernCppTimer.h"
#include <iostream>

int main()
{
	Timer t;
	t.start(5 * 1000, []
	{
		std::cout << "Hello World!\n";
	});

	getchar();
}
