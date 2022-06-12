#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "tile.h"
#include "board.h"
#include "iostream"
#include "Random.h"
#include "fstream"


int main()
{
    void RerenderBoard(Board & board, sf::RenderWindow & window);
    void CheckIfTilePressed(Board & board, sf::RenderWindow & window, string side, int numRows, int numCols);
    void UpdateScore(sf::RenderWindow & window, Board & board);

    //CONFIG
    ifstream infile;
    infile.open("./boards/config.cfg");
    int conf_cols;
    int conf_rows;
    int conf_mines;
    string line;
    vector<string> config_vec;
    while (getline(infile, line)) {
        config_vec.push_back(line);
    }
    conf_cols = stoi(config_vec[0]);
    conf_rows = stoi(config_vec[1]);
    conf_mines = stoi(config_vec[2]);

    Board board(conf_rows, conf_cols, conf_mines);

    int numTiles = conf_cols * conf_rows;

    auto& window = board.initialize(conf_cols, conf_rows); //initialize board

    while (window.isOpen())
    {
        sf::Event event;
        if (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();

            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {

                    CheckIfTilePressed(board, window, "left", board.rows, board.cols);

                }
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    CheckIfTilePressed(board, window, "right", board.rows, board.cols);

                }
            }
        }

        window.clear(sf::Color::White);

        RerenderBoard(board, window);

        window.display();
    }


    TextureManager::Clear();
    return 0;
}


void  CheckIfTilePressed(Board& board, sf::RenderWindow& window, string side, int numRows, int numCols) {
    auto mouse_pos = sf::Mouse::getPosition(window);
    auto translated_pos = window.mapPixelToCoords(mouse_pos);

    for (int i = 0; i < board.boardvec.size(); i++) {

        sf::Sprite curSprite = board.boardvec[i]->tile;
        Tile* curTile = board.boardvec[i];

        if (curSprite.getGlobalBounds().contains(translated_pos)) {

            cout << "Tile " << i << " pressed." << endl;
            if (side == "left") {
                if (curTile->getisGameTile() && !curTile->getisFlagged() && !board.game_lost && !board.game_won) { //if game tile pressed

                    Tile* face = board.boardvec[board.boardvec.size() - 5];
                    Tile* tep = board.boardvec[i];
                    if (tep->getisBomb()) {
                        cout << "PRESSED BOMB" << endl;
                        face->setTexture("face_lose"); //LOSE
                        board.game_lost = true;
                        cout << "GAME LOST" << endl;
                        //board.setLoseBoard();
                        //reveal all tiles


                    }
                    else {

                    }
                    tep->setisPressed(true);
                    tep->checkAdjacency();

                }
                else { //if option button pressed
                    if (curTile->getID() == "debug" && !board.game_lost) {
                        //cout << "Debug Pressed" << curTile->getisPressed() <<endl;
                        curTile->setisPressed(!curTile->getisPressed());

                    }
                    else if (curTile->getID() == "face_happy" || curTile->getID() == "face_lose" || curTile->getID() == "face_win") {
                        //cout << "face" << endl;
                        //board.cols = numCols;
                        //board.rows = numRows;
                        sf::RenderWindow& windo = board.initialize(numRows, numCols);
                        //board.setWindow(windo);

                    }
                    else if (curTile->getID() == "test_1") {
                        board.test1Pressed();
                        board.initialize(numRows, numCols);

                    }
                    else if (curTile->getID() == "test_2") {
                        cout << "Test 2" << endl;
                        board.test2Pressed();
                        board.initialize(numRows, numCols);

                    }
                    else if (curTile->getID() == "test_3") {
                        board.test3Pressed();
                        board.initialize(numRows, numCols);
                    }
                    else {
                        //cout << curTile->getID() << endl;
                    }


                }
            }
            else if (side == "right") {
                if (curTile->getisGameTile() && !curTile->getisFlagged() && !curTile->getisPressed() && !board.game_lost && !board.game_won) {
                    Tile* tep = board.boardvec[i];
                    tep->setisFlagged(true);

                }
                else if (curTile->getisGameTile() && curTile->getisFlagged() && !board.game_lost && !board.game_won) {
                    Tile* tep = board.boardvec[i];
                    tep->setisFlagged(false);
                }
            }
        }
    }
}

void RerenderBoard(Board& board, sf::RenderWindow window) {
    Tile* reveal_bomb = board.boardvec[board.boardvec.size() - 4];
    bool reveal_mines = reveal_bomb->getisPressed();

    board.checkLose();
    Tile* face = board.boardvec[board.boardvec.size() - 5];

    if (board.checkWin()) {
        face->setTexture("face_win"); //WIN
        for (int i = 0; i < board.boardvec.size(); i++) {
            if (board.boardvec[i]->getisBomb() && board.boardvec[i]->getisGameTile()) {
                Tile* tep = board.boardvec[i];
                tep->setIsOvertileActivated(true);
                tep->setisFlagged(true);
                tep->setOverTile("flag");
                //tep->setIsToptileActivated(true);
                //tep->setTopTile("mine");
                board.boardvec[i]->Render(window);
            }
            else {
                Tile* tep = board.boardvec[i];
                //tep->setIsToptileActivated(true);
                //tep->setTopTile("mine");
                board.boardvec[i]->Render(window);

            }

        }

    }
    else if (board.game_lost) {
        //cout << "GAME LOST" << endl;
        for (int i = 0; i < board.boardvec.size(); i++) {
            if (board.boardvec[i]->getisBomb() && board.boardvec[i]->getisGameTile()) {
                if (board.boardvec[i]->getisFlagged()) {
                    Tile* tep = board.boardvec[i];
                    tep->setIsOvertileActivated(true);
                    tep->setOverTile("flag");
                    tep->setIsToptileActivated(true);
                    tep->setTopTile("mine");
                    board.boardvec[i]->Render(window);
                }
                else {
                    Tile* tep = board.boardvec[i];
                    tep->setIsToptileActivated(true);
                    tep->setTopTile("mine");
                    board.boardvec[i]->Render(window);
                }

            }
            else {

                board.boardvec[i]->Render(window);
            }
        }
    }
    else {
        if (reveal_mines) {
            for (int i = 0; i < board.boardvec.size(); i++) {
                if (board.boardvec[i]->getisBomb() && board.boardvec[i]->getisGameTile()) {
                    Tile* tep = board.boardvec[i];
                    tep->setIsOvertileActivated(true);
                    tep->setMineTexture();
                    board.boardvec[i]->Render(window);

                }
                else {

                    board.boardvec[i]->Render(window);
                }
            }
        }
        else {
            for (int i = 0; i < board.boardvec.size(); i++) {
                if (board.boardvec[i]->getisBomb() && board.boardvec[i]->getisGameTile() && !board.boardvec[i]->getisPressed()) {
                    Tile* tep = board.boardvec[i];
                    tep->setIsOvertileActivated(false);

                    tep->setMineTexture();
                    board.boardvec[i]->Render(window);

                }
                else if (board.boardvec[i]->getisBomb()) {
                    board.boardvec[i]->setIsOvertileActivated(true);

                    board.boardvec[i]->setMineTexture();
                    board.boardvec[i]->Render(window);
                }
                else {
                    board.boardvec[i]->Render(window);
                }
            }
        }
    }



    //set score

    board.UpdateScore(window, board);

}





