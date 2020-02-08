#pragma once

#include <Windows.h>
#include <iostream>

namespace CGE
{
	class Character
	{
	public:
		Character()
		{
			character = L'A';
			int x = 0;
			int y = 0;
		}
		Character(wchar_t character, int x = 0, int y = 0)
		{
			this->character = character;
			this->x = x;
			this->y = y;
		}
		int GetX()
		{
			return x;
		}
		int GetY()
		{
			return y;
		}
		wchar_t GetCharacter()
		{
			return character;
		}
		void SetX(int x)
		{
			this->x = x;
		}
		void SetY(int y)
		{
			this->y = y;
		}
		void SetCharacter(wchar_t character)
		{
			this->character = character;
		}
	private:
		wchar_t character;
		int x, y;
	};
	class Console
	{
	public:
		Console()
		{
			width = 0;
			height = 0;
			title = L"ConsoleGameEngine";
			screen = new wchar_t[width * height];
			console = NULL;
			bytes = 0;
			clear_char = L' ';
		}
		bool Create(int width, int height, std::wstring title)
		{
			this->width = width;
			this->height = height;
			this->title = title;
			console = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, 0);
			CONSOLE_SCREEN_BUFFER_INFO buffer_info;
			GetConsoleScreenBufferInfo(console, &buffer_info);
			if(width < buffer_info.dwMaximumWindowSize.X || height < buffer_info.dwMaximumWindowSize.Y)
			{
				std::cout << "CGE::CREATION::FAILED::INVALID_BUFFER_SIZE\n";
				return 0;
			}
			SetConsoleTitle(title.c_str());
			SetConsoleScreenBufferSize(console, {(short) width, (short) height});
			SMALL_RECT window_size = {0, 0, (short) width - 1, (short) height - 1};
			if(!SetConsoleWindowInfo(console, true, &window_size)) return 0;
			SetConsoleActiveScreenBuffer(console);
			CONSOLE_CURSOR_INFO cursor_info;
			GetConsoleCursorInfo(console, &cursor_info);
			cursor_info.bVisible = false;
			SetConsoleCursorInfo(console, &cursor_info);
			screen = new wchar_t[width * height];
			Clear();
			return 1;
		}
		void Clear()
		{
			for(int i = 0; i < width * height; i++)
				screen[i] = clear_char;
		}
		void SetClearCharacter(wchar_t character)
		{
			clear_char = character;
		}
		void Display()
		{
			WriteConsoleOutputCharacter(console, screen, width * height, {0, 0}, &bytes);
		}
		void Draw(Character character)
		{
			screen[character.GetX() + width * character.GetY()] = character.GetCharacter();
		}
	private:
		wchar_t clear_char;
		std::wstring title;
		int width, height;
		wchar_t* screen;
		HANDLE console;
		DWORD bytes;
	};
}