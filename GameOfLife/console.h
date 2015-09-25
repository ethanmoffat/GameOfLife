#pragma once

#include <Windows.h>
#include <memory>
#include <string>
#include <sstream>

class Console
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

private:
	//singleton pattern
	static Console& GetInst()
	{
		static Console inst;
		return inst;
	}
	Console();

	//public interface
public:
	static void Out(const char * const format, ...);
	static void Out(short x, short y, const char * const format, ...);
	static void RelativeOut(short x, short y, const char * const format, ...);
	static void SetBounds(short x, short y);
	static void SetForeColor(ConsoleColor color);
	static void SetBackColor(ConsoleColor color);
	static void SetCursorVisible(bool bVis);
	static void SetCursorHeight(int percent);
	static void Read(const char * const format, ...);

	static ConsoleColor GetForeColor() { return GetInst().m_foreColor; }
	static ConsoleColor GetBackColor() { return GetInst().m_backColor; }

	~Console();
//private instance methods
private:
	bool IsHandleValid() const { return m_hConsole && m_hConsole != INVALID_HANDLE_VALUE; }

//private instance members
private:
	HANDLE m_hConsole;
	ConsoleColor m_foreColor;
	ConsoleColor m_backColor;
	DWORD m_cursorHeight;
	bool m_isCursorVisible;
};

class ConsoleException : public std::exception
{
public:
	enum ReturnValue
	{
		SUCCESS = 0,
		ERROR_BAD_HANDLE,
		ERROR_OUTPUT_FAILED,
		ERROR_SET_POSITION_FAILED,
		ERROR_SET_SIZE_FAILED,
		ERROR_SET_COLOR_FAILED,
		ERROR_GET_ATTRIBUTES_FAILED, 
		ERROR_SET_CURSORINFO_FAILED, 
		ERROR_GET_CURSORINFO_FAILED,
		ERROR_CURSOR_HEIGHT_INVALID
	};

	ReturnValue RetVal;
	DWORD LastError;
	ConsoleException() = delete;
	ConsoleException(ReturnValue ret) : RetVal(ret), LastError(0) { }
	ConsoleException(ReturnValue ret, DWORD ErrorCode) : RetVal(ret), LastError(ErrorCode) { }

	std::string ErrorToString() const
	{
		switch (RetVal)
		{
		case SUCCESS: return std::string("SUCCESS");
		case ERROR_BAD_HANDLE: return std::string("ERROR_BAD_HANDLE");
		case ERROR_OUTPUT_FAILED: return std::string("ERROR_OUTPUT_FAILED");
		case ERROR_SET_POSITION_FAILED: return std::string("ERROR_SET_POSITION_FAILED");
		case ERROR_SET_SIZE_FAILED: return std::string("ERROR_SET_SIZE_FAILED");
		case ERROR_SET_COLOR_FAILED: return std::string("ERROR_SET_COLOR_FAILED");
		case ERROR_GET_ATTRIBUTES_FAILED: return std::string("ERROR_GET_ATTRIBUTES_FAILED");
		case ERROR_SET_CURSORINFO_FAILED: return std::string("ERROR_SET_CURSORINFO_FAILED");
		case ERROR_CURSOR_HEIGHT_INVALID: return std::string("ERROR_CURSOR_HEIGHT_INVALID");
		case ERROR_GET_CURSORINFO_FAILED: return std::string("ERROR_GET_CURSORINFO_FAILED");
		default: return std::string("Unknown error");
		}
	}

	std::string LastErrorToString() const
	{
		LPVOID lpMsgBuf;
		
		FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, LastError, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, NULL);

		std::string ret((LPSTR)lpMsgBuf);
		if (lpMsgBuf)
			LocalFree(lpMsgBuf);

		return ret;
	}

	ConsoleException& operator=(const ConsoleException&) = delete;
	~ConsoleException() = default;
};