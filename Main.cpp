#include "ConsoleGameEngine.h"

const int SC_WIDTH = 160, SC_HEIGHT = 40;

int main()
{
	CGE::Console engine;
	engine.Create(SC_WIDTH, SC_HEIGHT, L"Test");

	CGE::Character character(L'B', 100, 25);
	while(1)
	{
		engine.Clear();
		engine.Draw(character);
		engine.Display();
	}
}