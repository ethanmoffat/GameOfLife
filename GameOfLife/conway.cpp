#include "conway.h"

Grid::Grid(int grid_width, int grid_height)
{
	m_width = grid_width;
	m_height = grid_height;
	m_cells = new Cell*[m_height];
	for (int i = 0; i < m_height; ++i)
	{
		m_cells[i] = new Cell[m_width];
	}
}

Grid::~Grid()
{
	if (m_cells)
	{
		for (int i = 0; i < m_height; ++i)
		{
			delete[] m_cells[i];
			m_cells[i] = nullptr;
		}
		delete[] m_cells;
		m_cells = nullptr;
	}
}

void Grid::Seed(const list<COORD> &cells)
{
	for (auto loc : cells)
	{
		if (loc.X < m_width && loc.Y < m_height && loc.X >= 0 && loc.Y >= 0)
		{
			m_cells[loc.Y][loc.X].Toggle();
		}
	}
}

void Grid::ActCells()
{
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			//foreach cell in the grid...
			Cell * c = &m_cells[y][x];
			int neighborCount = 0;

			//sum the neighbors
			for (int yy = y - 1; yy <= y + 1; ++yy)
			{
				for (int xx = x - 1; xx <= x + 1; ++xx)
				{
					if (yy == y && xx == x || 
						yy < 0 || yy >= m_height ||
						xx < 0 || xx >= m_width) continue;

					if (m_cells[yy][xx].Active()) 
						neighborCount++;
				}
			}

			//don't actually change the state of cells here: prepare them to change
			if (c->Active() && neighborCount < 2)
				c->PrepareToggle(); //dies
			else if (c->Active() && neighborCount > 3)
				c->PrepareToggle(); //dies
			else if (!c->Active() && neighborCount == 3)
				c->PrepareToggle(); //lives!
		}
	}

	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			Cell &c = m_cells[y][x];
			if (c.IsPrepared())
			{
				bool prevActive = c.Active();
				c.Toggle();
				c.PrepareToggle(false);
				if (!prevActive && c.Active())
					c.SetColors(Console::Green, Console::Black);
			}
			else
				c.SetColors(Console::DarkGray, Console::Black);
		}
	}
}

void Grid::WriteToConsole() const
{
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			Cell& cell = m_cells[y][x];
			Console::SetForeColor(cell.ForeColor());
			Console::SetBackColor(cell.BackColor());
			Console::Out(x, y, cell.Active() ? "+" : " ");
		}
		Console::SetBackColor(Console::White);
		Console::Out(m_width, y, " ");
	}

	Console::SetBackColor(Console::White);
	for (int x = 0; x < m_width; ++x)
		Console::Out(x, m_height, " ");
	
	Console::SetBackColor(Console::Black);
}

int Grid::GetNumberOfLiveCells() const
{
	auto numberOfLiveCells = 0;

	for (auto y = 0; y < m_height; ++y)
	{
		for (auto x = 0; x < m_width; ++x)
		{
			auto& cell = m_cells[y][x];
			if (cell.Active())
				numberOfLiveCells++;
		}
	}

	return numberOfLiveCells;
}