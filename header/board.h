#pragma once
#include <vector>;
#include "tile.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Random.h"
#include "iostream"

using namespace std;
class Board
{
private:
	bool test_1;
	bool test_2;
	bool test_3;
public:
	sf::RenderWindow& window;
	int rows;
	int cols;
	int mines;
	int score;

	int orig_rows;
	int orig_cols;

	Board(int cols, int rows, int mines) {
		this->test_1 = false;
		this->test_2 = false;
		this->test_3 = false;

		this->game_lost = false;
		this->game_won = false;

		//determined by config
		this->rows = rows;
		this->cols = cols;
		this->mines = mines;

		this->orig_cols = rows;
		this->orig_rows = cols;

		//sf::RenderWindow window(sf::VideoMode(32 * this->cols, (32 * this->rows) + 100), "MINESWEEPER - Kerrick Cavanaugh");
		//this->window = window;

	}

	vector <Tile*> boardvec;

	bool game_lost;

	bool game_won;

	void reset();

	bool checkLose();

	sf::RenderWindow& initialize(int numRows, int numCols);

	bool checkWin();

	void setLoseBoard();

	sf::RenderWindow* setWindow();

	void test1Pressed();

	void test2Pressed();

	void test3Pressed();

	void UpdateScore(sf::RenderWindow& window, Board board);
};

