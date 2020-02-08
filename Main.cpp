#include "ConsoleGameEngine.h"

const int SC_WIDTH = 160, SC_HEIGHT = 40;

int main()
{
	CGE::Console engine;
	engine.Create(SC_WIDTH, SC_HEIGHT, L"Test");

	engine.SetClearCharacter(L'-');
	CGE::Character character(L'B', CGE::Vec2(100, 30));
	while(1)
	{
		engine.Clear();
		engine.Draw(character);
		engine.Display();
	}
}