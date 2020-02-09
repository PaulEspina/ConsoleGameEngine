#include "ConsoleGameEngine.h"

const int SC_WIDTH = 160, SC_HEIGHT = 40;

int main()
{
	CGE::Console engine;
	engine.Create(SC_WIDTH, SC_HEIGHT, L"Test");

	engine.SetClearCharacter(L' ');
	CGE::Character character(L'X', CGE::Vec2(100, 30));
	CGE::Character title(L"Hey");
	while(1)
	{
		Sleep(100);
		character.pos += CGE::Vec2(1, 0);
		engine.Clear();
		engine.Draw(character);
		engine.Draw(title);
		engine.Display();
	}
}