#include "conway.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GameOfLifeTest
{		
	TEST_CLASS(conwayTest)
	{
	public:
		TEST_METHOD(GivenSingleLiveCell_WhenActIsCalled_CellDies)
		{
			Grid grid(5, 5);
			grid.Seed({ {2,2} });

			grid.ActCells();

			Assert::AreEqual(0, grid.GetNumberOfLiveCells());
		}

		TEST_METHOD(GivenSingleDeadCell_WhenExactlyThreeNeighbors_CellLives)
		{
			Grid grid(5, 5);
			grid.Seed({ {1, 1}, {1, 2}, {1, 3} });

			grid.ActCells();

			Assert::IsTrue(grid.GetCellAt(2, 2).Active());
		}

		TEST_METHOD(GivenSingleDeadCell_WhenLessThanThreeNeighbors_CellStaysDead)
		{
			Grid grid(5, 5);
			grid.Seed({ {1, 1}, {1, 3} });

			grid.ActCells();

			Assert::IsFalse(grid.GetCellAt(2, 2).Active());
		}

		TEST_METHOD(GivenSingleDeadCell_WhenMoreThanThreeNeighbors_CellStaysDead)
		{
			Grid grid(5, 5);
			grid.Seed({ { 1, 1 }, {1, 2}, { 1, 3 }, {2, 1} });

			grid.ActCells();

			Assert::IsFalse(grid.GetCellAt(2, 2).Active());
		}

		TEST_METHOD(GivenLiveCell_WhenLessThanTwoNeighbors_CellDies)
		{
			Grid grid(5, 5);
			grid.Seed({ {1, 2}, {2, 2} });

			grid.ActCells();

			Assert::IsFalse(grid.GetCellAt(2, 2).Active());
		}

		TEST_METHOD(GivenLiveCell_WhenTwoNeighbors_CellLives)
		{
			Grid grid(5, 5);
			grid.Seed({ {1, 1}, {1, 2}, {2, 2} });

			grid.ActCells();

			Assert::IsTrue(grid.GetCellAt(2, 2).Active());
		}

		TEST_METHOD(GivenLiveCell_WhenThreeNeighbors_CellLives)
		{
			Grid grid(5, 5);
			grid.Seed({ { 1, 1 },{ 1, 2 },{ 1, 3 },{ 2, 2 } });

			grid.ActCells();

			Assert::IsTrue(grid.GetCellAt(2, 2).Active());
		}

		TEST_METHOD(GivenLiveCell_WhenMoreThanThreeNeighbors_CellDies)
		{
			Grid grid(5, 5);
			grid.Seed({ { 1, 1 },{ 1, 2 },{ 1, 3 },{ 2, 2 },{ 2, 1 } });

			grid.ActCells();

			Assert::IsFalse(grid.GetCellAt(2, 2).Active());
		}
	};
}