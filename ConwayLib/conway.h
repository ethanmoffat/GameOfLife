#pragma once

#include "WindowsConsole.h"
#include <list>

using std::list;

class Cell
{
public:
	Cell(const Cell&)			 = delete;
	Cell& operator=(const Cell&) = delete;
	~Cell()						 = default;

	Cell(bool enabled = false)
		: m_Enabled(enabled)
		, m_prepare(false) { }

	void Toggle() { m_Enabled = !m_Enabled; }
	bool Active() const { return m_Enabled; }

	void PrepareToggle(bool bPrepared = true) { m_prepare = bPrepared; }
	bool IsPrepared() const { return m_prepare; }
private:
	bool m_Enabled, m_prepare;
};

class Grid
{
public:
	Grid(int grid_width = 40, int grid_height = 40);
	Grid(const Grid&);
	Grid& operator=(const Grid&) = delete;
	~Grid();

	void ActCells();
	void Seed(const list<COORD> &cells);

	int GetNumberOfLiveCells() const;

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	Cell& GetCellAt(int x, int y) const
	{
		if (x < 0 || x >= m_width || y < 0 || y >= m_height)
			throw std::exception("GetCellAt Out of bounds of the grid!");

		return m_cells[y][x];
	}

private:
	Cell ** m_cells;
	int m_width, m_height;
};