#pragma once
#include <IConsole.h>
#include <conway.h>

class GameRenderer
{
public:
	GameRenderer(IConsole * console);
	GameRenderer(GameRenderer &other) = delete;
	~GameRenderer() = default;

	void SetCurrentGrid(Grid * current) { _currentGrid = current; }
	void SetPreviousGrid(Grid * previous) { _previousGrid = previous; }

	void RenderWorld() const;

private:
	IConsole *_console;
	Grid *_previousGrid;
	Grid *_currentGrid;
};