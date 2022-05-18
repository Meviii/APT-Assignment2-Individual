#include "../GameEngine.h"
#include "../Menu.h"
#include "../LinkedList.h"
#include "../Tile.h"
#include <map>
#include <iterator>
#include <fstream>
#include <iostream>

void testGamePlay();
int testValueByLetter(Letter letter);
vector<string> testArgTokenizer(string input);
void testPlaceTile(string input);
void testChangePlayer();
void testReplaceTile(string input);
bool testCheckGameOver();
void testPrintWinner();
void testSaveGame(string inputFile);
void testReadWordList();

class TestGameEngine
{
    private:

    bool isGameOver;
    TileBag *tb;
    vector<Player *> players;
    GameBoard *gb;
    int curr_player_turn;
    Player *curr_player;
    map<char, int> boardRow = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}};
    map<Letter, int> letterValue = {{'A', 1}, {'B', 3}, {'C', 3}, {'D', 2}, {'E', 1}, {'F', 4}, {'G', 2}, {'H', 4}, {'I', 1}, {'J', 8}, {'K', 5}, {'L', 1}, {'M', 3}, {'N', 1}, {'O', 1}, {'P', 3}, {'Q', 10}, {'R', 1}, {'S', 1}, {'T', 1}, {'U', 1}, {'V', 4}, {'W', 4}, {'X', 8}, {'Y', 4}, {'Z', 10}};


    public:

    TestGameEngine()
    {
    }

    TestGameEngine(TileBag *tb, std::vector<Player *> players, GameBoard *gb)
    {
        this->tb = tb;
        this->players = players;
        this->gb = gb;
    }

    void testReadWordList(){
        std::ifstream wordListData;
        std::string word;
        std::vector<std::string> word_list;

        wordListData.open("word_list.txt");

        if (!wordListData.is_open()){
            std::cout << "Error while trying to open file" << std::endl;
        }else{
            while (getline(wordListData, word)) {
                // word_list.push_back(word);
                std::cout << word << std::endl;
            }
        }
    }

    void testGamePlay()
    {

        for (Player *p : players)
        {
            p->setHand(tb);
        }

        this->curr_player_turn = 0;
        curr_player = players[curr_player_turn];

        isGameOver = false;

        while (isGameOver == false)
        {
            gb->printBoard();
            if (isGameOver == false)
            {
                if (this->testCheckGameOver() == true)
                {
                    this->testPrintWinner();
                }

                string input;
                cout << endl;
                cout << curr_player->getName() << ", it's your turn" << endl;
                cout << endl;
                for (Player *p : players)
                {
                    cout << "Score for " << p->getName() << ": " << p->getScore() << endl;
                }
                cout << endl;
                curr_player->printHand();

                bool turn_end = false;
                int tile_place_counter = 0;
                while (turn_end == false)
                {
                    cout << "> ";
                    while (!getline(cin >> ws, input))
                    {
                        cout << "Incorrect input" << endl;
                        cin.clear();
                        cin.ignore();
                    }
                    transform(input.begin(), input.end(), input.begin(), ::toupper);

                    if (input == "PLACE DONE")
                    {
                        if (curr_player->getPassCounter() == 1)
                        {
                            curr_player->setPassCounter(0);
                        }
                        testChangePlayer();
                        turn_end = true;
                    }
                    else if (input == "PASS")
                    {
                        curr_player->setPassCounter((curr_player->getPassCounter() + 1));
                        testChangePlayer();
                        turn_end = true;
                    }
                    else if (this->testArgTokenizer(input).size() == 4)
                    {
                        if (input.substr(0, 6) == "PLACE " && input.substr(6, 1).size() == 1 && input.substr(8, 3) == "AT " && input.substr(11, 2).size() <= 3)
                        {
                            tile_place_counter += 1;
                            if (tile_place_counter == 7)
                            {
                                cout << "BINGOD!!!" << endl;
                                cout << "You have scored an additional 50 points" << endl;
                                curr_player->setScore(curr_player->getScore() + 50);
                            }
                            testPlaceTile(input);
                            curr_player->printHand();
                        }
                    }
                    else if (this->testArgTokenizer(input).size() == 2)
                    {
                        if (input.substr(0, 8) == "REPLACE " && input.substr(6, 1).size() == 1)
                        {

                            testReplaceTile(input);
                            turn_end = true;
                        }
                    }
                    else if (input == "QUIT")
                    {
                        isGameOver = true;
                        std::cout << "Goodbye!" << std::endl;
                        std::abort();
                    }
                    else if (input == "SAVE")
                    {
                        std::string save_file;
                        std::cout << "Please enter a filename to save: " << std::endl;
                        std::cout << "> ";
                        while (!(std::cin >> save_file))
                        {
                            std::cin.clear();
                            std::cin.ignore(10000, '\n');
                            std::cout << "Invalid input" << std::endl;
                        }
                        this->testSaveGame(save_file);
                        std::cout << "Continuing game..." << std::endl;
                    }
                    else
                    {
                        std::cout << "Incorrect Input" << std::endl;
                    }
                }
            }
        }
    }

    int testValueByLetter(Letter letter)
    {
        return letterValue.find(letter)->second;
    }

    vector<string> testArgTokenizer(string input)
    {
        stringstream ss(input);
        vector<string> s;

        while (ss >> input)
        {
            s.push_back(input);
        }
        return s;
    }

    void testPlaceTile(std::string input)
    {
        std::string arg;
        std::string tileHandLetter;
        std::string holder;
        std::string positionOnBoard;
        int valueOfPositionOnBoard;

        std::vector<std::string> s = this->testArgTokenizer(input);

        arg = s[0];
        tileHandLetter = s[1];
        holder = s[2];
        positionOnBoard = s[3];
        valueOfPositionOnBoard = std::stoi(positionOnBoard.substr(1, 3));

        transform(tileHandLetter.begin(), tileHandLetter.end(), tileHandLetter.begin(), ::toupper);
        transform(positionOnBoard.begin(), positionOnBoard.end(), positionOnBoard.begin(), ::toupper);

        char charHandLetter = tileHandLetter[0];
        Tile *tile_to_place = new Tile((Letter)charHandLetter, (Value)this->testValueByLetter(((Letter)charHandLetter)));

        if (gb->isTileValid(this->boardRow.find(positionOnBoard[0])->second, valueOfPositionOnBoard) && curr_player->isTileInHand(charHandLetter))
        {

            gb->addTile(this->boardRow.find(positionOnBoard[0])->second, valueOfPositionOnBoard, tile_to_place);
            curr_player->removeTileInHand(charHandLetter);

            if (curr_player->canDrawTile(tb))
            {
                curr_player->drawTile(tb);
            }

            cout << "Added tile to " << positionOnBoard[0] << valueOfPositionOnBoard << endl;
            curr_player->setScore(curr_player->getScore() + (Value)this->testValueByLetter(((Letter)charHandLetter)));
            gb->printBoard();
        }
        else
        {
            cout << "You cannot place that tile" << endl;
            cout << endl;
        }
    }

    void testChangePlayer()
    {
        int players_size = players.size();

        if (players_size > (curr_player_turn + 1))
        {
            curr_player_turn += 1;
            curr_player = players[curr_player_turn];
        }
        else if (players_size == (curr_player_turn + 1))
        {
            curr_player_turn = 0;
            curr_player = players[curr_player_turn];
        }
        else
        {
            cout << "Error while switching player turn" << endl;
        }
    }

    void testReplaceTile(std::string input)
    {
        char tileLetterToRemove;

        vector<string> s = this->testArgTokenizer(input);
        tileLetterToRemove = s[1][0];

        if (curr_player->isTileInHand(tileLetterToRemove))
        {
            curr_player->removeTileInHand(tileLetterToRemove);

            if (curr_player->canDrawTile(tb))
            {
                curr_player->drawTile(tb);
            }
            cout << "Tile removed from hand" << endl;
            this->testChangePlayer();
        }
        else
        {
            cout << "You do not own that tile." << endl;
        }
    }

    bool testCheckGameOver()
    {
        if (tb->getSize() == 0)
        {
            this->isGameOver = true;
            return true;
        }

        for (Player *p : players)
        {
            if (p->getHandSize() == 0 || p->getPassCounter() == 2)
            {
                this->isGameOver = true;
                return true;
            }
        }

        return false;
    }

    void testPrintWinner()
    {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Game Over!" << std::endl;
        
        Player* tmp = new Player();
        int highest_score = 0;
        for (Player *p : players)
        {
            if (p->getScore() > highest_score)
            {
                tmp->setName(p->getName());
                tmp->setScore(p->getScore());
                highest_score = p->getScore();
            }
            cout << "Score for " << p->getName() << ": " << p->getScore() << endl;
        }
        cout << "Player " << tmp->getName() << " won!" << endl;
        cout << endl;
        cout << "Goodbye!" << endl;
        return;
    }

    void testSaveGame(std::string inputFile)
    {
        std::ofstream gameData;

        gameData.open(inputFile);

        if (!gameData)
        {
            std::cout << "Error saving game" << std::endl;
        }
        else
        {
            gameData << players.size() << "\n";

            for(Player* p : players){
                gameData << p->getName() << "\n";
                gameData << p->getScore() << "\n";
                gameData << p->getPassCounter() << "\n";

                LinkedList *player_hand = p->getHand();
                Node *h = player_hand->getHead();
                for (int i = 0; i < PLAYER_HAND_AMOUNT; i++)
                {
                    if (i == (PLAYER_HAND_AMOUNT - 1))
                    {
                        gameData << h->tile->getLetter() << "-" << h->tile->getValue() << "\n";
                    }
                    else
                    {
                        gameData << h->tile->getLetter() << "-" << h->tile->getValue() << ", ";
                    }
                    h = h->next;
                }
            }
            int tb_size = tb->getSize();
            LinkedList *tb_list = tb->getList();
            Node *tb_h = tb_list->getHead();
            for (int i = 0; i < tb_size; i++)
            {
                if (i == (tb_size - 1))
                {
                    gameData << tb_h->tile->getLetter() << "-" << tb_h->tile->getValue() << "\n";
                }
                else
                {
                    gameData << tb_h->tile->getLetter() << "-" << tb_h->tile->getValue() << ", ";
                }
                tb_h = tb_h->next;
            }
            char alpha[15] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'};

            gameData << "    0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  "
                    << "\n";
            gameData << "---------------------------------------------------------------"
                    << "\n";
            std::vector<std::vector<Tile *>> board = gb->getBoard();
            std::map<Tile *, std::string> tl_on_board;
            int gb_size = gb->getSize();
            for (int row = 0; row < gb_size; row++)
            {
                gameData << alpha[row] << " ";
                for (int col = 0; col < gb_size; col++)
                {
                    if (board[row][col] == nullptr)
                    {
                        gameData << "| ";
                    }
                    else if (board[row][col] != nullptr && board[row][col]->getLetter() == ' ')
                    {
                        gameData << "| " << board[row][col]->getLetter() << " ";
                    }
                    else
                    {
                        string tmp = to_string(col);
                        tl_on_board.insert({board[row][col], (alpha[row] + tmp)});
                        gameData << "| " << board[row][col]->getLetter() << " ";
                    }
                }
                gameData << "|"
                        << "\n";
            }
            unsigned int iter_sz = 0;
            for (auto const &x : tl_on_board)
            {
                if (iter_sz == tl_on_board.size() - 1)
                {
                    gameData << x.first->getLetter() << "@" << x.second;
                }
                else
                {
                    gameData << x.first->getLetter() << "@" << x.second << ", ";
                }
                iter_sz += 1;
            }
        }
        gameData.close();
    }
};


int main(void){
    testReadWordList();
    // /*
    //  * Test 1: valueByLetter() - Return values of tiles by their letter
    //  * and compares with a reference of values
    //  */

    // LinkedList* list = new LinkedList();
    // TileBag *tb = new TileBag(list);
    // Tile *b3 = new Tile('B', 3);

    // GameBoard *gb1 = new GameBoard();

    // Player *p1 = new Player();
    // p1->setName("Jo");
    // p1->setHand(tb);
    // p1->setScore(40);
    // p1->setPassCounter(0);

    // Player *p2 = new Player();
    // p2->setName("Ma");
    // p2->setHand(tb);
    // p2->setScore(30);
    // p2->setPassCounter(0);

    // std::vector<Player *> players;
    // players.push_back(p1);
    // players.push_back(p2);

    // TestGameEngine *ge1 = new TestGameEngine(tb, players, gb1);

    // LinkedList* scrTiles = new LinkedList();
    // TileBag *scrValues = new TileBag();

    // Tile *tA = new Tile('A', 1);
    // Tile *tB = new Tile('B', 3);
    // Tile *tC = new Tile('C', 3);
    // Tile *tD = new Tile('D', 2);
    // Tile *tE = new Tile('E', 1);
    // Tile *tF = new Tile('F', 4);
    // Tile *tG = new Tile('G', 2);
    // Tile *tH = new Tile('H', 4);
    // Tile *tI = new Tile('I', 1);
    // Tile *tJ = new Tile('J', 8);
    // Tile *tK = new Tile('K', 5);
    // Tile *tL = new Tile('L', 1);
    // Tile *tM = new Tile('M', 3);
    // Tile *tN = new Tile('N', 1);
    // Tile *tO = new Tile('O', 1);
    // Tile *tP = new Tile('P', 3);
    // Tile *tQ = new Tile('Q', 10);
    // Tile *tR = new Tile('R', 1);
    // Tile *tS = new Tile('S', 1);
    // Tile *tT = new Tile('T', 1);
    // Tile *tU = new Tile('U', 1);
    // Tile *tV = new Tile('V', 4);
    // Tile *tW = new Tile('W', 4);
    // Tile *tX = new Tile('X', 8);
    // Tile *tY = new Tile('Y', 4);
    // Tile *tZ = new Tile('Z', 10);

    // scrTiles->addBack(tA);
    // scrTiles->addBack(tB);
    // scrTiles->addBack(tC);
    // scrTiles->addBack(tD);
    // scrTiles->addBack(tE);
    // scrTiles->addBack(tF);
    // scrTiles->addBack(tG);
    // scrTiles->addBack(tH);
    // scrTiles->addBack(tI);
    // scrTiles->addBack(tJ);
    // scrTiles->addBack(tK);
    // scrTiles->addBack(tL);
    // scrTiles->addBack(tM);
    // scrTiles->addBack(tN);
    // scrTiles->addBack(tO);
    // scrTiles->addBack(tP);
    // scrTiles->addBack(tQ);
    // scrTiles->addBack(tR);
    // scrTiles->addBack(tS);
    // scrTiles->addBack(tT);
    // scrTiles->addBack(tU);
    // scrTiles->addBack(tV);
    // scrTiles->addBack(tW);
    // scrTiles->addBack(tX);
    // scrTiles->addBack(tY);
    // scrTiles->addBack(tZ);

    // scrValues->setAsList(scrTiles);

    // std::cout << "Testing valueByLetter() for returning the correct value:" << std:: endl;    

    // for(int i = 0; i < 26; i++){
    //     char currLetter = ('A' + i);
    //     int scrValue = scrValues->getTile(i)->getValue();
    //     if (ge1->testValueByLetter(currLetter) == scrValue){
    //         std::cout << currLetter << " value of " << ge1->testValueByLetter(currLetter) << " matches the reference table value: " << scrValue << std::endl;
    //         }
    //     }
    // std::cout << std::endl << std::endl;

    // for (int i = 0; i < scrValues->getSize(); i++)
    // {
    //     delete scrValues->getTile(i);
    // }

    // //Deconstructor for the TileBag and its LinkedList
    // scrValues->~TileBag();



    // /* 
    //  * Test 2: Check game over conditions
    //  */ 
    
    // // 1st Case: TileBag is not empty. Players have tiles and no passes.
    // // Using TestGameEngine *ge1 = new TestGameEngine(tb, players, gb1);
    // std::cout << "Testing checkGameOver() 1st Case: TileBag is not empty. Players have tiles and no passes:" << std:: endl; 

    // if (ge1->testCheckGameOver()){
    //     std::cout << "Game has reached an endgame condition" << std::endl << std::endl;
    // } else {
    //     std::cout << "Game has not reached an endgame condition" << std::endl << std::endl;
    // }
    
    
    // //2nd Case: TileBag is empty. Players have tiles and no passes
    // std::cout << "Testing checkGameOver() 2nd Case: TileBag is empty. Players have tiles and no passes:" << std:: endl;

    // LinkedList *emptyList = new LinkedList();
    // TileBag *emptyTb = new TileBag();
    // emptyTb->setAsList(emptyList);
    // TestGameEngine *ge2 = new TestGameEngine(emptyTb, players, gb1);

    // if (ge2->testCheckGameOver()){
    //     std::cout << "Game has reached an endgame condition" << std::endl << std::endl;
    // } else {
    //     std::cout << "Game has not reached an endgame condition" << std::endl << std::endl;
    // }


    // //3rd Case: TileBag is not empty. Players have no tiles and 2 passes
    // std::cout << "Testing checkGameOver() 3rd Case: TileBag is not empty. Players have no tiles and 2 passes:" << std:: endl;

    // Player *p3 = new Player();
    // p3->setName("Mii");
    // p3->addToHand(b3);
    // p3->setScore(0);
    // p3->setPassCounter(2);

    // Player *p4 = new Player();
    // p4->setName("Mike");
    // p4->setScore(60);
    // p4->setPassCounter(2);

    // std::vector<Player *> players2;
    // players2.push_back(p3);
    // players2.push_back(p4);

    // TestGameEngine *ge3 = new TestGameEngine(tb, players2, gb1);

    // if (ge3->testCheckGameOver()){
    //     std::cout << "Game has reached an endgame condition" << std::endl << std::endl;
    // } else {
    //     std::cout << "Game has not reached an endgame condition" << std::endl << std::endl;
    // }


    // //4th Case: TileBag is empty. Player hands are empty. No passes
    // std::cout << "Testing checkGameOver() 4th Case: TileBag is empty. Player hands are empty. No passes:" << std:: endl;

    // Player *p5 = new Player();
    // p5->setName("Mii");
    // p5->addToHand(b3);
    // p5->setScore(0);
    // p5->setPassCounter(0);

    // Player *p6 = new Player();
    // p6->setName("Mike");
    // p6->setScore(60);
    // p6->setPassCounter(0);

    // std::vector<Player *> players3;
    // players3.push_back(p5);
    // players3.push_back(p6);

    // TestGameEngine *ge4 = new TestGameEngine(emptyTb, players3, gb1);

    // if (ge4->testCheckGameOver()){
    //     std::cout << "Game has reached an endgame condition" << std::endl << std::endl;
    // } else {
    //     std::cout << "Game has not reached an endgame condition" << std::endl << std::endl;
    // }


    // //5th Case: TileBag is empty. Player hands are empty. 2 passes
    // TestGameEngine *ge5 = new TestGameEngine(emptyTb, players2, gb1);
    // std::cout << "Testing checkGameOver() 5th Case: TileBag is empty. Player hands are empty. 2 passes:" << std:: endl;

    // if (ge5->testCheckGameOver()){
    //     std::cout << "Game has reached an endgame condition" << std::endl << std::endl;
    // } else {
    //     std::cout << "Game has not reached an endgame condition" << std::endl << std::endl << std::endl;
    // }



    // /*
    //  *Test 3: Player with highest points is the winner
    //  */

    // std::cout << "Testing printWinner(). Player with highest points should be declared winner:" << std:: endl;
    // ge1->testPrintWinner();

    return EXIT_SUCCESS;
}
