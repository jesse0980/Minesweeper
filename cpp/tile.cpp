#include "tile.h"

void Tile::Render(sf::RenderWindow& window) {
	window.draw(this->tile);
	if (this->getIsOvertileActivated()) {
		window.draw(this->over_tile);
	}
	if (this->getIsToptileActivated()) {
		window.draw(this->top_tile);
	}

}

bool  Tile::getisGameTile() {
	return this->isGameTile;
}

void Tile::setisGameTile(bool isGameTile) {
	this->isGameTile = isGameTile;
}

bool  Tile::getisBomb() {
	return this->isBomb;
}

sf::Sprite Tile::getSprite() {
	return this->tile;
}

void Tile::setTexture(string image) {
	this->tile.setTexture(TextureManager::GetTexture(image));
	this->image = image;
}

bool Tile::getisFlagged() {
	return this->isFlagged;
}

void  Tile::setisBomb(bool isBomb) {
	this->isBomb = isBomb;
}

void Tile::setMineTexture() {
	bool isBomb = this->getIsOvertileActivated();

	if (isBomb) {
		this->setIsOvertileActivated(true);
		this->setOverTile("mine");
		this->setTexture("tile_revealed");

	}
	else {
		this->setIsOvertileActivated(false);
		this->setTexture("tile_hidden");
	}


}

void Tile::setisFlagged(bool isFlagged) {
	this->isFlagged = isFlagged;
	if (isFlagged) {
		this->setIsToptileActivated(true);
		this->setTopTile("flag");
	}
	else {
		this->setIsToptileActivated(false);
	}
}

bool Tile::getisPressed() {
	return this->isPressed;
}

void Tile::setOverTile(string image) {
	this->over_tile.setTexture(TextureManager::GetTexture(image));
}

void Tile::setTopTile(string image) {
	this->top_tile.setTexture(TextureManager::GetTexture(image));
}

void Tile::checkAdjacency() {
	bool valid = true;
	vector<Tile*> arr = this->getAdjacent();
	this->setisPressed(true);
	for (unsigned int i = 0; i < arr.size(); i++) {
		if (this->calculateAdjacentMines() == 0) {
			if (!arr[i]->getisBomb() && !arr[i]->getisFlagged() && arr[i]->getisGameTile() && !arr[i]->getisPressed() && arr[i] != nullptr) {
				arr[i]->setisPressed(true);
				arr[i]->checkAdjacency();
			}
		}
		else {}
	}


}


void Tile::setisPressed(bool isPressed) {
	this->isPressed = isPressed;
	if (this->getisBomb() && this->getisGameTile()) {
		//this->setisBomb(true);
		this->setIsToptileActivated(true);
		this->setTopTile("mine");
		this->setTexture("tile_revealed");
	}
	else if (!this->getisBomb() && this->getisGameTile()) {
		int num_nearby_mines = 0;
		for (unsigned int i = 0; i < this->adjacent.size(); i++) {
			if (this->adjacent[i]->getisBomb()) {
				num_nearby_mines++;
			}
		}

		if (num_nearby_mines == 0) {
			this->setTexture("tile_revealed");
		}
		else {
			string numtexture = "number_" + to_string(num_nearby_mines);
			this->setIsOvertileActivated(true);
			this->setOverTile(numtexture);
			this->setTexture("tile_revealed");
		}
	}
}

string Tile::getID() {
	return this->id;
}

int Tile::calculateAdjacentMines() {
	int numMines = 0;
	for (unsigned int i = 0; i < adjacent.size(); i++) {
		if (adjacent[i]->getisBomb()) {
			numMines++;
		}
	}
	return numMines;
}

void Tile::setAdjacent(vector<Tile*> adjacent) {
	this->adjacent = adjacent;
}

vector<Tile*> Tile::getAdjacent() {
	return this->adjacent;
}

bool Tile::getIsOvertileActivated() {
	return this->over_tile_activated;
}

void Tile::setIsOvertileActivated(bool act) {
	this->over_tile_activated = act;
}

bool Tile::getIsToptileActivated() {
	return this->top_tile_activated;
}

void Tile::setIsToptileActivated(bool act) {
	this->top_tile_activated = act;
}