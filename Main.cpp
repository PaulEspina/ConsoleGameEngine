#include "ConsoleGameEngine.h"
#include <iostream>

const int SC_WIDTH = 160, SC_HEIGHT = 40;

int main()
{
	CGE::Console engine;
	if(!engine.Create(SC_WIDTH, SC_HEIGHT, L"Test"))
	{
		std::cout << "Console Buffer Creation Failed!\n";
	}
	while(1)
	{
		engine.Clear();
		engine.Draw();
	}
}