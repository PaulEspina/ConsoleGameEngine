#include "ConsoleGameEngine.h" // Include engine header file

const int SC_WIDTH = 160, SC_HEIGHT = 40;

int main()
{
	CGE::Console console(SC_WIDTH, SC_HEIGHT, "Test"); // create console with the specified number of characters(width and height) and window title

	console.SetClearCharacter('A'); // Sets clear character(sort of the background). default is a white space
	CGE::Character character("X", CGE::Vec2(100, 30)); // creates a drawable object with specified character and coordinates
	while(1) // basic and terrible game loop
	{
		Sleep(100); // game timer ( so that it wont go too fast)
		if(console.GetKeyState(VK_RIGHT)) // console.GetKeyState returns true if the virtual key code inputted is pressed
			character.pos += CGE::Vec2(1, 0); // updates character position
		if(console.GetKeyState(VK_LEFT))
			character.pos += CGE::Vec2(-1, 0);
		if(console.GetKeyState(VK_DOWN))
			character.pos += CGE::Vec2(0, 1);
		if(console.GetKeyState(VK_UP))
			character.pos += CGE::Vec2(0, -1);
		console.Clear(); // clears window
		console.Draw(character); // draws character
		console.Display(); // displays the drawn characters in the window
	}
}