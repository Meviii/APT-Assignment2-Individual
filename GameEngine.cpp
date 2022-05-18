#include "GameEngine.h"

GameEngine::GameEngine()
{
}
/*
 * Construct a new GameEngine:: GameEngine object
 * Assigns TileBag, Players and GameBoard
 */
GameEngine::GameEngine(TileBag *tb, std::vector<Player *> players, GameBoard *gb)
{
    this->tb = tb;
    this->players = players;
    this->gb = gb;
    readWordList();
}

void GameEngine::readWordList(){

    std::ifstream wordListData;
    std::string word;
    std::vector<std::string> word_list;

    wordListData.open("word_list.txt");

    if (!wordListData.is_open()){
        std::cout << "Error while trying to open file" << std::endl;
    }else{
        while (getline(wordListData, word)) {
            this->word_list.push_back(word);
        }
    }
}

// Implementation of the Scrabble game
void GameEngine::gamePlay()
{
    // Set player hands
    for (Player *p : players)
    {
        p->setHand(tb);
    }

    // Initiate Board with tile
    Tile* initTile = new Tile(tb->getFront()->getLetter(),tb->getFront()->getValue());
    if (gb->isTileValid(7,7)){
        gb->addTile(7,7,initTile);
        tb->removeFront();
    }

    // Initiate player turn
    //this->curr_player_turn = 0;
    curr_player = players[curr_player_turn];

    isGameOver = false;

    gb->printBoard();

    while (isGameOver == false)
    {
        if (isGameOver == false)
        {
            if (this->checkGameOver() == true)
            {
                this->printWinner();
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

                // CHOICE #1: Current player has finished placing Tiles
                if (input == "PLACE DONE")
                {
                    if (tile_place_counter > 0){
                        if (curr_player->getPassCounter() == 1)
                        {
                            curr_player->setPassCounter(0);
                        }
                        if (tile_place_counter == 7)
                        {
                            cout << "BINGO!!!" << endl;
                            cout << "You have scored an additional 50 points" << endl;
                            curr_player->setScore(curr_player->getScore() + 50);
                        }
                        changePlayer();
                        turn_end = true;
                        gb->printBoard();
                    }else{
                        std::cout << "Please place a tile first." << std::endl;
                    }

                }
                // CHOICE #2: Current player passing their turn
                else if (input == "PASS" && tile_place_counter == 0)
                {
                    curr_player->setPassCounter((curr_player->getPassCounter() + 1));
                    changePlayer();
                    turn_end = true;
                    gb->printBoard();

                }
                // CHOICE #3: Current player placing tiles
                else if (this->argTokenizer(input).size() == 4)
                {
                    if (input.substr(0, 6) == "PLACE " && input.substr(6, 1).size() == 1 && input.substr(8, 3) == "AT " && input.substr(11, 2).size() <= 3)
                    {
                        tile_place_counter += 1;
                        placeTile(input);
                    }else{
                        std::cout << "Incorrect Input" << std::endl;
                    }
                }
                // CHOICE #4: Replaces current players missing Tiles from the TileBag
                else if (this->argTokenizer(input).size() == 2)
                {
                    if (input.substr(0, 8) == "REPLACE " && input.substr(6, 1).size() == 1)
                    {

                        replaceTile(input);
                        turn_end = true;
                        gb->printBoard();
                    }else{
                        std::cout << "Invalid Input" << std::endl;
                    }
                }
                // CHOICE #5: Quit the game
                else if (input == "QUIT")
                {
                    isGameOver = true;
                    std::cout << "Goodbye!" << std::endl;
                    delete this->tb;
                    delete this->gb;
                    players.~vector();
                    std::abort();
                }
                // CHOICE #6: Save state of game in the specified save_file
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
                    this->saveGame(save_file);
                    std::cout << "Continuing game..." << std::endl;
                }
                else
                {
                    // INVALID INPUT: Current player to re-enter their choice
                    std::cout << "Incorrect Input" << std::endl;
                }
            }
        }
    }
}

int GameEngine::valueByLetter(Letter letter)
{
    return letterValue.find(letter)->second;
}

vector<string> GameEngine::argTokenizer(string input)
{
    stringstream ss(input);
    vector<string> s;

    while (ss >> input)
    {
        s.push_back(input);
    }
    return s;
}

/*
 * Place a tile on the board for the current player:
 * Arguments:
 * arg - text command "PLACE"
 * tileHandLetter - the Tile letter to play
 * holder - the text command "AT"
 * positionOnBoard - letter or y-axis position to be placed (A - O)
 * valueOfPositionOnBoard - number or x-axis position to be placed (0 -14))
 */
void GameEngine::placeTile(std::string input)
{
    std::string arg;
    std::string tileHandLetter;
    std::string holder;
    std::string positionOnBoard;
    int valueOfPositionOnBoard;

    std::vector<std::string> s = this->argTokenizer(input);

    arg = s[0];
    tileHandLetter = s[1];
    holder = s[2];
    positionOnBoard = s[3];
    valueOfPositionOnBoard = std::stoi(positionOnBoard.substr(1, 3));

    transform(tileHandLetter.begin(), tileHandLetter.end(), tileHandLetter.begin(), ::toupper);
    transform(positionOnBoard.begin(), positionOnBoard.end(), positionOnBoard.begin(), ::toupper);

    char charHandLetter = tileHandLetter[0];
    Tile *tile_to_place = new Tile((Letter)charHandLetter, (Value)this->valueByLetter(((Letter)charHandLetter)));
    std::vector<std::vector<Tile *>> board = gb->getBoard();
    if (gb->isTileValid(this->boardRow.find(positionOnBoard[0])->second, valueOfPositionOnBoard) && curr_player->isTileInHand(charHandLetter))
    {
        if (gb->isTileAdj((this->boardRow.find(positionOnBoard[0])->second), valueOfPositionOnBoard) == true)
        {
            // Place Tile
            gb->addTile(this->boardRow.find(positionOnBoard[0])->second, valueOfPositionOnBoard, tile_to_place); // place tile

            // Check if it is a word match
            if (isWord((this->boardRow.find(positionOnBoard[0])->second), valueOfPositionOnBoard) == true){
                std::cout << "SUCCESS" << std::endl;
            }
            
            // Remove Tile
            curr_player->removeTileInHand(charHandLetter);
            // Draw Tile if available
            if (curr_player->canDrawTile(tb))
            {
                curr_player->drawTile(tb);
            }

            cout << "Added tile to " << positionOnBoard[0] << valueOfPositionOnBoard << endl;
            curr_player->setScore(curr_player->getScore() + (Value)this->valueByLetter(((Letter)charHandLetter)));
            //gb->printBoard();
        }else{
            cout << "Please place next to another tile" << endl;
        }
    }
    else
    {
        cout << "You cannot place that tile" << endl;
    }
}

void GameEngine::changePlayer()
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

/*
 * Removes specified tile from players hand.
 * Replaces (adds to the back of the player's hand) with a Tile from the TileBag
 * Removes that tile form the TileBag
 */
void GameEngine::replaceTile(std::string input)
{
    char tileLetterToRemove;

    vector<string> s = this->argTokenizer(input);
    tileLetterToRemove = s[1][0];

    if (curr_player->isTileInHand(tileLetterToRemove))
    {
        curr_player->removeTileInHand(tileLetterToRemove);

        if (curr_player->canDrawTile(tb))
        {
            curr_player->drawTile(tb);
        }
        cout << "Tile removed from hand" << endl;
        this->changePlayer();
    }
    else
    {
        cout << "You do not own that tile." << endl;
    }
}

bool GameEngine::isWord(int row, int col)
{

    string word_to_check = "";
    std::vector<std::vector<Tile *>> board = gb->getBoard();

    // vertical - bottom to top search
    int row_holder = (BOARD_MAX-1);
    while (board[(row_holder)][col] == NULL){
        row_holder -= 1;
    }
    while (board[row_holder][col] != NULL){

        Letter curLetter = board[row_holder][col]->letter;
        word_to_check += curLetter;
        int checkedWordListSize = checked_words.size();
        
        for (int j = 0; j < checkedWordListSize; j++){
            if (word_to_check == checked_words[j]){
                return false;
            }   
        }
        row_holder -= 1;
    }

    int wordListSize = word_list.size();
    std::cout << word_to_check << std::endl;
    if (word_to_check.length() > 2){
        for (int i = 0; i < wordListSize; i++){
            if (word_to_check.find(word_list[i]) != std::string::npos) {
                this->checked_words.push_back(word_list[i]);
                return true;
            }
        }
    }
    return false;

}


/*
 * Check game end conditions
 * i.e. If no more Tiles in TileBag, and for any player either no Tiles in hand 
 * or 2 consecutive passes 
 */
bool GameEngine::checkGameOver()
{
    if (tb->getSize() == 0)
    {
        for (Player *p : players)
        {
            if (p->getHandSize() == 0 || p->getPassCounter() == 2)
            {
                this->isGameOver = true;
                return true;
            }
        }
    }

    return false;
}

/*
 * Outputs winner and their score
 * Iterates through players to find highest score
 * due to variable number of players
 */
void GameEngine::printWinner()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Game Over!" << std::endl;
    
    Player* tmp = new Player();
    int highest_score = -1;
    bool isDraw = false;
    for (Player *p : players)
    {
        if (p->getScore() > highest_score)
        {
            tmp->setName(p->getName());
            tmp->setScore(p->getScore());
            highest_score = p->getScore();
        }
        else if (p->getScore() == highest_score)
        {
            isDraw = true;
        }
        cout << "Score for " << p->getName() << ": " << p->getScore() << endl;
    }
    
    if (isDraw){
        std::cout << "There was a TIE!" << std::endl;
        cout << endl;
    }else{
        cout << "Player " << tmp->getName() << " won!" << endl;
        cout << endl;
    }
    cout << "Goodbye!" << endl;
    abort();
    return;
}

/*
 *Saves snapshot of current gamestate
 *to a user specified file
 */
void GameEngine::saveGame(std::string inputFile)
{
    std::ofstream gameData;
    string saveType = ".sav";
    if (inputFile.find(saveType) == std::string::npos)
    {
        inputFile.append(saveType);
    }
    gameData.open(inputFile);

    if (!gameData)
    {
        std::cout << "Error saving game" << std::endl;
    }
    else
    {
        // Save current player index
        int count = 0;
        int players_list_size = players.size();
        for (int i = 0; i < players_list_size; i++){
            if (i == curr_player_turn){
                gameData << count << "\n";
            }
            count += 1;
        }

        // Save player amount
        gameData << players.size() << "\n";

        // Save players' names, points, num. passes, hands as LinkedLists
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
        // Save TileBag as LinkedList
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
        // Save GameBoard's current state
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
                    gameData << "|   ";
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
        // Save Tiles 'LETTER@TILE'
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
