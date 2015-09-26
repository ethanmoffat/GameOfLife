#include "WindowsConsole.h"

WindowsConsole::WindowsConsole()
	: m_hConsole(INVALID_HANDLE_VALUE)
{
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!m_hConsole || m_hConsole == INVALID_HANDLE_VALUE)
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(m_hConsole, &info))
		throw ConsoleException(ConsoleException::ERROR_GET_ATTRIBUTES_FAILED, GetLastError());
	m_backColor = static_cast<ConsoleColor>(info.wAttributes >> 4 & 0xF);
	m_foreColor = static_cast<ConsoleColor>(info.wAttributes & 0xF);

	CONSOLE_CURSOR_INFO curInfo;
	if (!GetConsoleCursorInfo(m_hConsole, &curInfo))
		throw ConsoleException(ConsoleException::ERROR_GET_CURSORINFO_FAILED, GetLastError());
	m_cursorHeight = curInfo.dwSize;
	m_isCursorVisible = curInfo.bVisible != 0;
}

WindowsConsole::~WindowsConsole()
{
	//no need to close handle because it is stdout
}

void WindowsConsole::Out(const char * const format, ...)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	va_list list;
	va_start(list, format);
	char buffer[4096] = { 0 };
	vsprintf_s(buffer, format, list);
	va_end(list);

	DWORD numCharsWritten = 0;
	if (!WriteConsoleA(m_hConsole, buffer, static_cast<DWORD>(strlen(buffer)), &numCharsWritten, NULL))
		throw ConsoleException(ConsoleException::ERROR_OUTPUT_FAILED, GetLastError());
	
	if (numCharsWritten != static_cast<DWORD>(strlen(buffer)))
		throw ConsoleException(ConsoleException::ERROR_OUTPUT_FAILED);
}

void WindowsConsole::Out(short x, short y, const char * const format, ...)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	COORD pos = { x, y };
	if (!SetConsoleCursorPosition(m_hConsole, pos))
		throw ConsoleException(ConsoleException::ERROR_SET_POSITION_FAILED, GetLastError());
	
	va_list list;
	va_start(list, format);
	char buffer[4096] = { 0 };
	vsprintf_s(buffer, format, list);
	Out(buffer);
	va_end(list);
}

void WindowsConsole::RelativeOut(short x, short y, const char * const format, ...)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO info;
	if (!GetConsoleScreenBufferInfo(m_hConsole, &info))
		throw ConsoleException(ConsoleException::ERROR_GET_ATTRIBUTES_FAILED, GetLastError());

	//relative to the previous cursor position
	COORD pos = { info.dwCursorPosition.X + x, info.dwCursorPosition.Y + y };
	if (!SetConsoleCursorPosition(m_hConsole, pos))
		throw ConsoleException(ConsoleException::ERROR_SET_POSITION_FAILED, GetLastError());

	va_list list;
	va_start(list, format);
	char buffer[4096] = { 0 };
	vsprintf_s(buffer, format, list);
	Out(buffer);
	va_end(list);
}

void WindowsConsole::SetBounds(short x, short y)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);
	
	COORD sz = { x, y };
	if (!SetConsoleScreenBufferSize(m_hConsole, sz))
		throw ConsoleException(ConsoleException::ERROR_SET_SIZE_FAILED, GetLastError());
}

void WindowsConsole::SetForeColor(ConsoleColor color)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	m_foreColor = color;
	WORD attr = static_cast<WORD>(color);
	attr |= static_cast<WORD>(m_backColor);

	if (!SetConsoleTextAttribute(m_hConsole, attr))
		throw ConsoleException(ConsoleException::ERROR_SET_COLOR_FAILED, GetLastError());
}

void WindowsConsole::SetBackColor(ConsoleColor color)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	m_backColor = color;
	WORD attr = static_cast<WORD>(color) << 4;
	attr |= static_cast<WORD>(m_foreColor);

	if (!SetConsoleTextAttribute(m_hConsole, attr))
		throw ConsoleException(ConsoleException::ERROR_SET_COLOR_FAILED, GetLastError());
}

void WindowsConsole::SetCursorVisible(bool bVis)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	CONSOLE_CURSOR_INFO info;
	info.dwSize = m_cursorHeight;
	info.bVisible = m_isCursorVisible = bVis;

	if (!SetConsoleCursorInfo(m_hConsole, &info))
		throw ConsoleException(ConsoleException::ERROR_SET_CURSORINFO_FAILED, GetLastError());
}

void WindowsConsole::SetCursorHeight(int percent)
{
	if (!IsHandleValid())
		throw ConsoleException(ConsoleException::ERROR_BAD_HANDLE);

	if (percent < 0 || percent > 100)
		throw ConsoleException(ConsoleException::ERROR_CURSOR_HEIGHT_INVALID);

	CONSOLE_CURSOR_INFO info;
	info.dwSize = m_cursorHeight = static_cast<DWORD>(percent);
	info.bVisible = m_isCursorVisible;

	if (!SetConsoleCursorInfo(m_hConsole, &info))
		throw ConsoleException(ConsoleException::ERROR_SET_CURSORINFO_FAILED, GetLastError());
}

void WindowsConsole::Read(const char * const format, ...)
{
	//this is pretty much just a wrapper around scanf...
	va_list list;
	va_start(list, format);
	vscanf(format, list);
	va_end(list);
}