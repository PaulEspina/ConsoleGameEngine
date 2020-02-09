/*
	Copyright (c) 2020 Paul Espina

	You may use, edit or redistribute this code. However it comes without warranty of any kind.
	See license for more details.
*/

#pragma once

#include <Windows.h>
#include <iostream>

namespace CGE
{
	class Vec2
	{
	public:
		Vec2() = default;
		Vec2(int x_in, int y_in)
			:
			x(x_in),
			y(y_in)
		{
		}
		Vec2 operator+(const Vec2& rhs) const
		{
			return Vec2(x + rhs.x, y + rhs.y);
		}
		Vec2& operator+=(const Vec2& rhs)
		{
			return *this = *this + rhs;
		}
		Vec2 operator*(int rhs) const
		{
			return Vec2(x * rhs, y * rhs);
		}
		Vec2& operator*=(int rhs)
		{
			return *this = *this * rhs;
		}
		Vec2 operator-(const Vec2& rhs) const
		{
			return Vec2(x - rhs.x, y - rhs.y);
		}
		Vec2& operator-=(const Vec2& rhs)
		{
			return *this = *this - rhs;
		}
		int GetMagnitude() const
		{
			return x * x + y * y;
		}
		Vec2& Normalize()
		{
			return *this = GetNormalized();
		}
		Vec2 GetNormalized() const
		{
			const int len = GetMagnitude();
			if(len != 0)
			{
				return *this * (1 / len);
			}
			return *this;
		}
		int x, y;
	};
	class Character
	{
	public:
		Character()
		{
			this->character = L" ";
			this->pos.x = 0;
			this->pos.y = 0;
		}
		Character(std::wstring character, int x = 0, int y = 0)
			:
			Character()
		{
			this->character = character;
			this->pos.x = x;
			this->pos.y = y;
		}
		Character(wchar_t character, Vec2 pos)
			:
			Character()
		{
			this->character = character;
			this->pos.x = pos.x;
			this->pos.y = pos.y;
		}
		wchar_t GetCharacter()
		{
			return character[0];
		}
		void SetCharacter(wchar_t character)
		{
			this->character = character;
		}
		Vec2 pos;
		std::wstring character;
	};
	class Console
	{
	public:
		Console()
		{
			wchar_t clear_char = L' ';
			std::wstring title = L"ConsoleGameEngine";
			int width = 120, height = 30;
			wchar_t* screen = NULL;
			HANDLE console = NULL;
			DWORD bytes = 0;
		}
		Console(int width, int height, std::wstring title)
			:
			Console()
		{
			Create(width, height, title);
		}
		~Console()
		{
			delete[] screen;
		}
		bool Create(int width, int height, std::wstring title)
		{
			this->width = width;
			this->height = height;
			this->title = title;
			handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, 0);
			CONSOLE_SCREEN_BUFFER_INFO buffer_info;
			GetConsoleScreenBufferInfo(handle, &buffer_info);
			if(width < buffer_info.dwMaximumWindowSize.X || height < buffer_info.dwMaximumWindowSize.Y)
			{
				std::cout << "CGE::CREATION::FAILED::INVALID_BUFFER_SIZE\n";
				return 0;
			}
			SetConsoleTitle(title.c_str());
			SetConsoleScreenBufferSize(handle, {(short) width, (short) height});
			SMALL_RECT window_size = {0, 0, (short) width - 1, (short) height - 1};
			if(!SetConsoleWindowInfo(handle, true, &window_size)) return 0;
			SetConsoleActiveScreenBuffer(handle);
			CONSOLE_CURSOR_INFO cursor_info;
			GetConsoleCursorInfo(handle, &cursor_info);
			cursor_info.bVisible = false;
			SetConsoleCursorInfo(handle, &cursor_info);
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
			WriteConsoleOutputCharacter(handle, screen, width * height, {0, 0}, &bytes);
		}
		void Draw(Character character)
		{
			
			for(unsigned int i = 0; i < character.character.length(); i++)
				screen[character.pos.x + i + width * character.pos.y] = character.character[i];
		}
		bool GetKeyState(int i)
		{
			return 0x8000 & GetAsyncKeyState(i);
		}
	private:
		wchar_t clear_char;
		std::wstring title;
		int width, height;
		wchar_t* screen;
		HANDLE handle;
		DWORD bytes;
	};
}