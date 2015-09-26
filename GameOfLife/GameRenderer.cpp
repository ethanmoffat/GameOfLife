#include "GameRenderer.h"

GameRenderer::GameRenderer(IConsole* console)
{
	if (console == nullptr)
		throw std::exception("Invalid console pointer (must not be nullptr)");
	_console = console;
	_currentGrid = nullptr;
	_previousGrid = nullptr;
}

void GameRenderer::RenderWorld() const
{
	if (_currentGrid == nullptr || _previousGrid == nullptr)
		return;

	for (int y = 0; y < _currentGrid->GetHeight(); ++y)
	{
		for (int x = 0; x < _currentGrid->GetWidth(); ++x)
		{
			Cell& prevCell = _previousGrid->GetCellAt(x, y);
			Cell& cell = _currentGrid->GetCellAt(x, y);

			auto foreColor = !prevCell.Active() && cell.Active() ? IConsole::Green : IConsole::White;
			auto backColor = IConsole::Black;

			_console->SetForeColor(foreColor);
			_console->SetBackColor(backColor);
			_console->Out(x, y, cell.Active() ? "+" : " ");
		}
		_console->SetBackColor(IConsole::White);
		_console->Out(_currentGrid->GetWidth(), y, " ");
	}

	_console->SetBackColor(IConsole::White);
	for (int x = 0; x < _currentGrid->GetWidth(); ++x)
		_console->Out(x, _currentGrid->GetHeight(), " ");

	_console->SetBackColor(IConsole::Black);
}