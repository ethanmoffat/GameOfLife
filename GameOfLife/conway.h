#pragma once

#include "console.h"
#include <list>

using std::list;

class Cell
{
public:
	Cell(const Cell&)			 = delete;
	Cell& operator=(const Cell&) = delete;
	~Cell()						 = default;

	Cell(bool bOn = false)
		: m_Enabled(bOn)
		, m_prepare(false)
		, m_foreColor(Console::GetForeColor())
		, m_backColor(Console::GetBackColor()) { }

	inline void Toggle() { m_Enabled = !m_Enabled; }
	inline bool Active() const { return m_Enabled; }

	inline void PrepareToggle(bool bPrepared = true) { m_prepare = bPrepared; }
	inline bool IsPrepared() const { return m_prepare; }

	inline Console::ConsoleColor ForeColor() const { return m_foreColor; }
	inline Console::ConsoleColor BackColor() const { return m_backColor; }
	inline void SetColors(Console::ConsoleColor foreColor, Console::ConsoleColor backColor) { m_foreColor = foreColor; m_backColor = backColor; }
private:
	bool m_Enabled, m_prepare;
	Console::ConsoleColor m_foreColor;
	Console::ConsoleColor m_backColor;
};

class Grid
{
public:
	Grid(int grid_width = 40, int grid_height = 40);
	Grid(const Grid&) = delete;
	Grid& operator=(const Grid&) = delete;
	~Grid();

	void ActCells();
	void Seed(const list<COORD> &cells);
	void WriteToConsole() const;

private:
	Cell ** m_cells;
	int m_width, m_height;
};