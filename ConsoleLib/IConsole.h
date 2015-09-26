#pragma once

#include <Windows.h>

class IConsole
{
public:
	enum ConsoleColor {
		Black = 0,
		DarkBlue = FOREGROUND_BLUE,
		DarkGreen = FOREGROUND_GREEN,
		DarkCyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DarkRed = FOREGROUND_RED,
		DarkMagenta = FOREGROUND_RED | FOREGROUND_BLUE,
		DarkYellow = FOREGROUND_RED | FOREGROUND_GREEN,
		DarkGray = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Gray = FOREGROUND_INTENSITY,
		Blue = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		Green = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		Cyan = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		Red = FOREGROUND_INTENSITY | FOREGROUND_RED,
		Magenta = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		Yellow = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		White = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	}; //background can be obtained by << 8

	IConsole() = default;
	IConsole(IConsole& other) = delete;

	virtual void Out(const char * const format, ...) = 0;
	virtual void Out(short x, short y, const char * const format, ...) = 0;
	virtual void RelativeOut(short x, short y, const char * const format, ...) = 0;
	virtual void SetBounds(short x, short y) = 0;
	virtual void SetForeColor(ConsoleColor color) = 0;
	virtual void SetBackColor(ConsoleColor color) = 0;
	virtual void SetCursorVisible(bool bVis) = 0;
	virtual void SetCursorHeight(int percent) = 0;
	virtual void Read(const char * const format, ...) = 0;

	virtual ConsoleColor GetForeColor() const = 0;
	virtual ConsoleColor GetBackColor() const = 0;

	virtual ~IConsole() = default;
};