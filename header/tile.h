#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"
#include "vector"

using namespace std;

class Tile
{
private:
	string image;
	bool isGameTile;
	bool isBomb;
	bool isFlagged;
	string id;
	bool isPressed;
	bool over_tile_activated;
	bool top_tile_activated;

	vector<Tile*> adjacent;


public:
	sf::Sprite tile;
	sf::Sprite over_tile;
	sf::Sprite top_tile;
	int x_coor;
	int y_coor;
	//constructors
	Tile() {
		this->image = "";
		this->isGameTile = false;
		this->isBomb = false;

	}

	Tile(string image, bool isGameTile, bool isPressed) {
		this->image = image;
		sf::Sprite tile(TextureManager::GetTexture(image));
		this->tile = tile;
		this->isBomb = isBomb;
		this->isGameTile = isGameTile;
		this->isFlagged = isFlagged;
		this->id = image;
		this->isPressed = isPressed;
	}

	Tile(string image, bool isGameTile, bool isPressed, bool isBomb, bool isFlagged, int x_coor, int y_coor) {
		this->image = image;
		sf::Sprite tile(TextureManager::GetTexture(image));
		this->tile = tile;
		this->isBomb = isBomb;
		this->isGameTile = isGameTile;
		this->isFlagged = isFlagged;
		this->isPressed = isPressed;
		this->x_coor = x_coor;
		this->y_coor = y_coor;
	}

	int calculateAdjacentMines();

	void setOverTile(string image);

	//methods
	void Render(sf::RenderWindow& window);

	bool getisGameTile();

	bool getIsOvertileActivated();

	void setIsOvertileActivated(bool act);

	bool getIsToptileActivated();

	void setIsToptileActivated(bool act);

	void setMineTexture();

	void setisGameTile(bool isGameTile);

	bool getisBomb();

	string getID();

	void setisBomb(bool isBomb);

	bool getisFlagged();

	void setisFlagged(bool isFlagged);

	void setTexture(string image);

	sf::Sprite getSprite();

	bool getisPressed();

	void setisPressed(bool isPressed);

	void setAdjacent(vector<Tile*> adjacent);

	void checkAdjacency();

	vector<Tile*> getAdjacent();

	void setTopTile(string image);

};

