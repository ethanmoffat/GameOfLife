#include "console.h"
#include "conway.h"

#include <thread>
#include <mutex>

using std::thread;
using std::mutex;

void InputThread(bool * quit, mutex * pause, int * speed)
{
	if (!quit || !pause || !speed)
		std::exit(-99);

	char input[256] = "";
	bool paused = false;
	while (!*quit)
	{
		Console::Read("%s", input);
		if (strlen(input) == 1)
		{
			switch (input[0])
			{
			case 'q': *quit = true; if (paused) pause->unlock(); break;
			case 'p': pause->lock(); paused = true; break;
			case 'r': pause->unlock(); paused = false; break;
			}
		}
		else if (input[0] == 'x')
		{
			int x = atoi(&input[1]);
			if (x)
				*speed = x;
		}
	}
}

int main(int argc, char * argv[])
{
	bool quit = false;
	mutex pause;
	int speed = 50;
	thread input(InputThread, &quit, &pause, &speed);

	try
	{
		Grid g;
		//seed with a 'gosper glider gun'
		//http://en.wikipedia.org/wiki/Gun_(cellular_automaton)
		g.Seed({{ 1, 5 }, { 2, 5 }, { 1, 6 }, { 2, 6 },

				{ 13, 3 }, { 14, 3 }, { 12, 4 }, { 16, 4 }, { 11, 5 }, { 17, 5 },
				{ 11, 6 }, { 15, 6 }, { 17, 6 }, { 18, 6 }, { 11, 7 }, { 17, 7 },
				{ 12, 8 }, { 16, 8 }, { 13, 9 }, { 14, 9 },

				{ 25, 1 }, { 25, 2 }, { 23, 2 }, { 21, 3 }, { 22, 3 }, { 21, 4 },
				{ 22, 4 }, { 21, 5 }, { 22, 5 }, { 23, 6 }, { 25, 6 }, { 25, 7 },

				{ 35, 3 }, { 36, 3 }, { 35, 4 }, { 36, 4 },
		});

		Console::Out(0, 44, "Enter \'q\' to quit.");
		Console::Out(0, 45, "p=pause  r=resume  x<num>=iteration speed (ms)");
		Console::SetCursorVisible(false);
		int i = 0;
		while (!quit)
		{
			pause.lock();
			Console::Out(0, 42, "Iteration %d...   (delaying %dms)", i + 1, speed);
			g.WriteToConsole();
			g.ActCells();
			Sleep(speed);
			i++;
			pause.unlock();
		}
		Console::Out(0, 43, "Quitting...            \n");
		Console::SetCursorVisible(true);

		/* SAMPLE MAIN using Console functions
		Console::Out(5, 5, "5");
		for (int i = 0; i <= 4; ++i)
		{
			Sleep(100);
			Console::RelativeOut(-2, -1, "%d", i);
		}
		Console::Out(0, 6, "Done!\n");*/
	}
	catch (ConsoleException &e)
	{
		printf("CAUGHT ConsoleException:\n");
		printf("\t Error code %d: %s\n", e.RetVal, e.ErrorToString().c_str());
		if (e.LastError)
			printf("\t Win32 code %d: %s\n", e.LastError, e.LastErrorToString().c_str());

		quit = true;
	}
	catch (std::exception &ex)
	{
		printf("CAUGHT exception:\n");
		printf("\t %s", ex.what());

		quit = true;
	}
	catch (...)
	{
		printf("CAUGHT unknown?\n");

		quit = true;
	}

	input.join();

	return 0;
}