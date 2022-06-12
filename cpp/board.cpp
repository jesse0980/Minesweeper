#include "board.h"
#include "fstream"
#include "sstream"


void Board::reset() {
    this->game_lost = false;
    this->game_won = false;
    for (int i = 0; i < this->boardvec.size(); i++) {
        this->boardvec[i]->setTexture("tile_hidden");
    }
}

sf::RenderWindow& Board::initialize(int numRows, int numCols) {
    sf::RenderWindow window(sf::VideoMode(32 * this->rows, (32 * this->cols) + 100), "MINESWEEPER");

    this->game_lost = false;
    this->game_won = false;
    bool debug_state = false;


    if (this->boardvec.size() > 0) { //check if debug button pressed
        debug_state = this->boardvec[this->boardvec.size() - 4]->getisPressed();
    }
    this->boardvec.clear(); //clear the board vector

    if (this->test_1) { //test 1 pressed
        ifstream infile;
        infile.open("./boards/testboard1.brd");

        //get rows and cols
        int cols = 0;
        int rows = 0;


        //put all 0s and 1s into an array (1-D like board)
        string line;
        string bit;
        vector<vector<char>> content;
        while (getline(infile, line)) {
            cols = line.length();
            rows++;
            vector<char> temp;

            //temp.push_back(line);
            for (int i = 0; i <= line.length(); i++) {
                temp.push_back(line[i]);
            }

            content.push_back(temp);
        }

        this->cols = rows;
        this->rows = cols;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool is_mine = false;
                if (content[i][j] == '0') {
                    is_mine = false;
                    //cout << "no mine" << endl;
                }
                else if (content[i][j] == '1') {
                    is_mine = true;
                    // cout << "mine" << endl;
                }
                //cout << content[i][j];
                Tile* sqr = new Tile("tile_hidden", true, false, is_mine, false, j, i);
                sqr->tile.setPosition(j * 32, i * 32);
                sqr->over_tile.setPosition(j * 32, i * 32);
                sqr->top_tile.setPosition(j * 32, i * 32);
                this->boardvec.push_back(sqr);
            }
        }
    }
    else if (this->test_2) {
        ifstream infile;
        infile.open("./boards/testboard2.brd");

        //get rows and cols
        int cols = 0;
        int rows = 0;


        //put all 0s and 1s into an array (1-D like board)
        string line;
        string bit;
        vector<vector<char>> content;
        while (getline(infile, line)) {
            cols = line.length();
            rows++;
            vector<char> temp;

            //temp.push_back(line);
            for (int i = 0; i <= line.length(); i++) {
                temp.push_back(line[i]);
            }

            content.push_back(temp);
        }

        this->cols = rows;
        this->rows = cols;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool is_mine = false;
                if (content[i][j] == '0') {
                    is_mine = false;
                    //cout << "no mine" << endl;
                }
                else if (content[i][j] == '1') {
                    is_mine = true;
                    // cout << "mine" << endl;
                }
                //cout << content[i][j];
                Tile* sqr = new Tile("tile_hidden", true, false, is_mine, false, j, i);
                sqr->tile.setPosition(j * 32, i * 32);
                sqr->over_tile.setPosition(j * 32, i * 32);
                sqr->top_tile.setPosition(j * 32, i * 32);
                this->boardvec.push_back(sqr);
            }
        }
    }
    else if (this->test_3) {
        ifstream infile;
        infile.open("./boards/testboard3.brd");

        //get rows and cols
        int cols = 0;
        int rows = 0;

        //put all 0s and 1s into an array (1-D like board)
        string line;
        string bit;
        vector<vector<char>> content;
        while (getline(infile, line)) {
            cols = line.length();
            rows++;
            vector<char> temp;

            //temp.push_back(line);
            for (int i = 0; i <= line.length(); i++) {
                temp.push_back(line[i]);
            }

            content.push_back(temp);
        }

        this->cols = rows;
        this->rows = cols;


        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                bool is_mine = false;
                if (content[i][j] == '0') {
                    is_mine = false;
                    //cout << "no mine" << endl;
                }
                else if (content[i][j] == '1') {
                    is_mine = true;
                    // cout << "mine" << endl;
                }
                // cout << content[i][j];
                Tile* sqr = new Tile("tile_hidden", true, false, is_mine, false, j, i);
                sqr->tile.setPosition(j * 32, i * 32);
                sqr->over_tile.setPosition(j * 32, i * 32);
                sqr->top_tile.setPosition(j * 32, i * 32);
                this->boardvec.push_back(sqr);
            }
        }
    }
    else {
        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                Tile* sqr = new Tile("tile_hidden", true, false, false, false, i, j);
                sqr->tile.setPosition(i * 32, j * 32);
                sqr->over_tile.setPosition(i * 32, j * 32);
                sqr->top_tile.setPosition(i * 32, j * 32);
                this->boardvec.push_back(sqr);
            }
        }
        int num_mines = this->mines;
        int mines_set = 0;


        this->cols = this->orig_rows;
        this->rows = this->orig_cols;



        for (int i = num_mines; i > 0; i--) {
            int rand = Random::Int(0, this->boardvec.size() - 11);
            if (this->boardvec[rand]->getisBomb()) {
                i++;
            }
            else {
                this->boardvec[rand]->setisBomb(true);
                mines_set++;
            }

        }

        this->mines = mines_set;
    }
    Tile* sign = new Tile("digits", false, false);
    sign->tile.setPosition(0, window.getSize().y - 90);
    this->boardvec.push_back(sign);

    Tile* dig_1 = new Tile("digits", false, false);
    dig_1->tile.setPosition(32, window.getSize().y - 90);
    this->boardvec.push_back(dig_1);

    Tile* dig_2 = new Tile("digits", false, false);
    dig_2->tile.setPosition(64, window.getSize().y - 90);
    this->boardvec.push_back(dig_2);

    Tile* dig_3 = new Tile("digits", false, false);
    dig_3->tile.setPosition(96, window.getSize().y - 90);
    this->boardvec.push_back(dig_3);



    Tile* face_button = new Tile("face_happy", false, false);
    face_button->tile.setPosition((window.getSize().x / 2) - ((face_button->tile.getTexture()->getSize().x) * 2), window.getSize().y - 90);
    this->boardvec.push_back(face_button);

    Tile* debug_button = new Tile("debug", false, debug_state);
    debug_button->tile.setPosition(window.getSize().x - 245, window.getSize().y - 90);
    this->boardvec.push_back(debug_button);


    Tile* test_1 = new Tile("test_1", false, false);
    test_1->tile.setPosition(window.getSize().x - 185, window.getSize().y - 90);
    this->boardvec.push_back(test_1);

    Tile* test_2 = new Tile("test_2", false, false);
    test_2->tile.setPosition(window.getSize().x - 125, window.getSize().y - 90);
    this->boardvec.push_back(test_2);

    Tile* test_3 = new Tile("test_3", false, false);
    test_3->tile.setPosition(window.getSize().x - 60, window.getSize().y - 90);
    this->boardvec.push_back(test_3);

    //find adjacent tiles
    for (int j = 0; j < this->boardvec.size(); j++) {

        vector<Tile*> adjacent;
        Tile* cur = this->boardvec[j];
        int cur_x = cur->x_coor;
        int cur_y = cur->y_coor;
        for (int k = 0; k < this->boardvec.size(); k++) {
            Tile* comp = this->boardvec[k];
            int comp_x = comp->x_coor;
            int comp_y = comp->y_coor;

            int x_diff = cur_x - comp_x;
            int y_diff = cur_y - comp_y;


            if ((x_diff == -1 && y_diff == 0) || (x_diff == -1 && y_diff == 1) || (x_diff == -1 && y_diff == -1) || (x_diff == 0 && y_diff == 1) || (x_diff == 0 && y_diff == -1) || (x_diff == 0 && y_diff == 0) || (x_diff == 1 && y_diff == -1) || (x_diff == 1 && y_diff == 0) || (x_diff == 1 && y_diff == 1)) {
                if (adjacent.size() > 8) {
                    break;
                }
                adjacent.push_back(comp);

            }

        }
        cur->setAdjacent(adjacent);
    }

    //reset test board conditions;
    this->test_1 = false;
    this->test_2 = false;
    this->test_3 = false;


    // auto ret_win = &window;
    return window;
}



bool Board::checkWin() {
    auto brd = this->boardvec;
    int num_game_tiles = this->rows * this->cols;

    int non_mines_pressed = 0;
    int non_mine_tiles = num_game_tiles - this->mines;

    for (unsigned int i = 0; i < num_game_tiles; i++) {
        if (brd[i]->getisPressed() && !brd[i]->getisBomb() && brd[i]->getisGameTile()) {
            non_mines_pressed++;
        }
    }

    //cout << "Non mines pressed: " << non_mines_pressed << " " << "Non mine tiles remaining: " << non_mine_tiles << endl;


    if (non_mines_pressed >= non_mine_tiles) {
        this->game_won = true;
        return true;
    }
    else {
        return false;
    }
}

bool Board::checkLose() {
    return this->game_lost;
}

sf::RenderWindow* Board::setWindow() {
    sf::RenderWindow window(sf::VideoMode(32 * this->cols, (32 * this->rows) + 100), "MINESWEEPER");
    auto ret_win = &window;
    return ret_win;
}

void Board::test1Pressed() {
    this->test_1 = true;
}

void Board::test2Pressed() {
    this->test_2 = true;
}

void Board::test3Pressed() {
    this->test_3 = true;
}

void Board::UpdateScore(sf::RenderWindow& window, Board board) {
    //cout << "Updating score" << endl;
    int score = 0;
    int mine_count = 0;
    int flag_count = 0;

    for (int i = 0; i < board.boardvec.size(); i++) {
        if (board.boardvec[i]->getisBomb()) {
            mine_count++;
        }
        if (board.boardvec[i]->getisFlagged()) {
            flag_count++;
        }
    }

    score = mine_count - flag_count;

    this->score = score;

    //cout << "Score : " << this->score << endl;

    //get all digit tiles (sprites)

    Tile* sign = board.boardvec[board.boardvec.size() - 9];

    sf::Sprite sign_sprite = sign->getSprite();

    Tile* digit_three = board.boardvec[board.boardvec.size() - 8];

    sf::Sprite digit_three_sprite = digit_three->getSprite();

    Tile* digit_two = board.boardvec[board.boardvec.size() - 7];

    sf::Sprite digit_two_sprite = digit_two->getSprite();

    Tile* digit_one = board.boardvec[board.boardvec.size() - 6];

    sf::Sprite digit_one_sprite = digit_one->getSprite();


    //convert score to array of strings (add minus sign if necessary)
    sf::IntRect neg(10 * 21, 0, 21, 32);
    sf::IntRect zero(0, 0, 32, 32);
    sf::IntRect none(0, 0, 0, 0);


    if (score < 100) {
        if (score < 0) {
            score = score * -1;

            sign_sprite.setTextureRect(neg);

            int first_dig = score % 10;
            digit_one_sprite.setTextureRect(sf::IntRect(first_dig * 21, 0, 21, 30));

            int sec_temp = score / 10;
            int sec_dig = sec_temp % 10;

            digit_two_sprite.setTextureRect(sf::IntRect(sec_dig * 21, 0, 21, 30));

            int third_temp = score / 100;
            int third_dig = third_temp % 10;
            digit_three_sprite.setTextureRect(sf::IntRect(third_dig * 21, 0, 21, 30));
        }
        else {

            sign_sprite.setTextureRect(none);

            int first_dig = score % 10;
            digit_one_sprite.setTextureRect(sf::IntRect(first_dig * 21, 0, 21, 30));

            int sec_temp = score / 10;
            int sec_dig = sec_temp % 10;

            digit_two_sprite.setTextureRect(sf::IntRect(sec_dig * 21, 0, 21, 30));

            int third_temp = score / 100;
            int third_dig = third_temp % 10;
            digit_three_sprite.setTextureRect(sf::IntRect(third_dig * 21, 0, 21, 30));
        }

    }
    else {
        sign_sprite.setTextureRect(none);

        int first_dig = score % 10;
        digit_one_sprite.setTextureRect(sf::IntRect(first_dig * 21, 0, 21, 30));

        int sec_temp = score / 10;
        int sec_dig = sec_temp % 10;

        digit_two_sprite.setTextureRect(sf::IntRect(sec_dig * 21, 0, 21, 30));

        int third_temp = score / 100;
        int third_dig = third_temp % 10;
        digit_three_sprite.setTextureRect(sf::IntRect(third_dig * 21, 0, 21, 30));

    }


    digit_one->tile = digit_one_sprite;

    digit_one->Render(window);


    digit_two->tile = digit_two_sprite;

    digit_two->Render(window);


    digit_three->tile = digit_three_sprite;

    digit_three->Render(window);

    sign->tile = sign_sprite;

    sign->Render(window);

}



