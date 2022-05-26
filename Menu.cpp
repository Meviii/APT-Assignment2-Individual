#include "Menu.h"

Menu::Menu()
{
    readPlayerFile();
    cout << endl;
    cout << "Welcome to Scrabble!" << endl;
    cout << "--------------------" << endl;
    cout << endl;
    cout << "Congrats to our best players!" << endl;

    printTopPlayers();
}

Menu::~Menu() {}

// Engine to run Menu
void Menu::runMenu()
{
    this->choice = 0;
    this->printMenu();

    // get a valid user choice from the stdin
    std::cout << "> ";
    while (!(cin >> this->choice))
    {
        if (this->choice == 99)
        {
            return;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input" << endl;
        cout << "> ";
    }

    // run the game
    this->runChoice();
}

// Menu printer
void Menu::printMenu()
{
    // print the detailed system viewer
    cout << "Menu" << endl;
    cout << "----\n"
         << endl;
    cout << "1. New Game" << endl;
    cout << "2. Load Game" << endl;
    cout << "3. Credits (Show student information)" << endl;
    cout << "4. Quit" << endl;
    cout << endl;
    cout << "Extra Features:" << endl;
    cout << endl;
    cout << "5. Word Matcher" << endl;
    cout << "6. 1-4 Player Mode" << endl;
    cout << endl;
}

// Choice selector
void Menu::runChoice()
{
    // while true, continue
    while (this->choice != 4 || cin.eof() == true)
    {
        // if the choice is 1, start a new game
        if (this->choice == 1)
        {
            this->playerCheck();
        }
        // if the choice is 2, load the game from the specified file
        else if (this->choice == 2)
        {
            string load_file;
            string saveType = ".sav";

            cout << "Please enter a filename to load: " << endl;
            cout << "> ";
            while (!(cin >> load_file) || cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid file" << endl;
            }
            if (load_file.find(saveType) == std::string::npos){
                load_file.append(saveType);
                this->loadGame(load_file);
            }
            else if (load_file.find(saveType) != std::string::npos)
            {
                this->loadGame(load_file);
            }
        }
        else if (this->choice == 3)
        {
            // choice 3 is for printing detailed personal info
            this->printCredits();
            this->runMenu();
        }
        // choice 4 is for exiting the game
        else if (this->choice == 4)
        {
            cout << "Goodbye!" << endl;
            return;
        }
        else if (this->choice == 5)
        {
            string toggler;
            cout << "Would you like to toggle the word matcher? YES/NO" << endl;
            if (this->wordMatcherToggle == false){
                cout << "Currently: OFF" << endl;
            }else{
                cout << "Currently: ON" << endl;
            }
            
            cout << "> ";
            cin >> toggler;
            transform(toggler.begin(), toggler.end(), toggler.begin(), ::toupper);
            while (cin.fail() || !(toggler == "NO" || toggler == "YES")){
                cin.clear();
                cin.ignore(10000000, '\n');
                cout << "Invalid input" << endl;
                cout << "> ";
                cin >> toggler;
                transform(toggler.begin(), toggler.end(), toggler.begin(), ::toupper);
            }

            if (toggler == "NO"){
                cout << "Turned Off." << endl;
                this->wordMatcherToggle = false;
            }else if(toggler == "YES"){
                cout << "Turned On." << endl;
                this->wordMatcherToggle = true;
            }

            this->runMenu();
            
        }
        else if (this->choice == 6)
        {
            string toggler;
            cout << "Would you like to turn on 1-4 player mode? YES/NO" << endl;
            if (this->isTwoPlayer == true){
                cout << "Currently: OFF" << endl;
            }else{
                cout << "Currently: ON" << endl;
            }
            
            cout << "> ";
            cin >> toggler;
            transform(toggler.begin(), toggler.end(), toggler.begin(), ::toupper);
            while (cin.fail() || !(toggler == "NO" || toggler == "YES")){
                cin.clear();
                cin.ignore(10000000, '\n');
                cout << "Invalid input" << endl;
                cout << "> ";
                cin >> toggler;
                transform(toggler.begin(), toggler.end(), toggler.begin(), ::toupper);
            }

            if (toggler == "NO"){
                cout << "Turned Off." << endl;
                this->isTwoPlayer = true;
            }else if(toggler == "YES"){
                cout << "Turned On." << endl;
                this->isTwoPlayer = false;
            }

            this->runMenu();
        }
        else if (cin.eof() == true)
        {
            cout << "Goodbye!" << endl;
            return;
        }
        else
        {
            cout << "Invalid Input" << endl;
            this->choice = 0;
            this->runMenu();
        }
    }
    cout << "Goodbye!" << endl;
}

// Print credentials
void Menu::printCredits()
{
    // print the detailed personal info
    cout << endl;
    cout << "Name: Mevlut Saluk" << endl;
    cout << "Student ID: S3717696" << endl;
    cout << "Email: S3717696@rmit.edu.com.au" << endl;

    cout << endl;
    cout << "Name: Yong Hui Cheah" << endl;
    cout << "Student ID: S3778714" << endl;
    cout << "Email: S3778714@rmit.edu.com.au" << endl;

    cout << endl;
    cout << "Name: Terrence Taylor" << endl;
    cout << "Student ID: S3909238" << endl;
    cout << "Email: S3909238@student.rmit.edu.au" << endl;

    cout << endl;
    cout << "Name: Paul Lubig" << endl;
    cout << "Student ID: S3329840" << endl;
    cout << "Email: S3329840@rmit.edu.com.au" << endl;
    cout << endl;
}

// Load Players to new game.
void Menu::playerCheck()
{
    int player_count;

    cout << endl
         << "Starting a New Game" << endl;
    cout << "Player count? 2-4" << endl;
    cout << "> ";
    // input the number of the players in the game
    cin >> player_count;

    if (player_count >= 1 && player_count <= 4)
    {
        // if there are two players
        if (player_count == 2 && this->getIsTwoPlayer() == true)
        {
            // start the game
            this->playerSelection(player_count);
            return this->newGame();
        }
        else if (player_count > 2 && this->getIsTwoPlayer() == true)
        {
            // if there are more than two players, show error message
            cout << "Currently support 2-player only." << endl;
            this->runChoice();
        }
        else if (this->getIsTwoPlayer() == false)
        {
            this->playerSelection(player_count);
            return this->newGame();
        }
        else if (player_count < 2)
        {
            // if there is just one player, show the error message
            cout << "Single player not supported." << endl;
            this->runChoice();
        }
    }
    else
    {   
        cout << "Incorrect choice" << endl;
        this->choice = 1;
        this->runMenu();
    }
}

// Individual player setter
void Menu::playerSelection(int i)
{
    string playerName;
    string nameHolder; // to check previously entered name
    for (int x = 1; x < i + 1; x++)
    {
        if (x == i + 5)
        {
            cout << "Reached max player limit of 4" << endl;
            return;
        }
        // input the user name
        cout << "Enter a name for player " << x << ": " << endl;
        cout << "> ";
        cin >> playerName;

        // input a valid player name
        while (cin.fail() || playerName.find_first_of("0123456789!@#$%^&*()_+-=[]{};':\",./<>\\`~|") != string::npos || nameHolder == playerName || isPlayerNameUnique(playerName) == false)
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Name is taken or is invalid. No numbers please." << endl;
            std::cout << "> ";
            cin >> playerName;
        }

        // create a new player and push it at the end of the vector
        Player *tmp_p = new Player();
        nameHolder = playerName;
        tmp_p->setName(playerName);
        tmp_p->setScore(0);
        tmp_p->setPassCounter(0);
        players.push_back(tmp_p);
        cout << "Player" << x << " name set to: " << playerName << endl;
        cin.clear();
    }
    cout << endl;
}

/**
 * @brief check weather there two player mode is enabled
 *
 * @return true
 * @return false
 */
bool Menu::getIsTwoPlayer()
{
    return this->isTwoPlayer;
}

void Menu::setIsTwoPlayer(bool val)
{
    this->isTwoPlayer = val;
}

/**
 * @brief start a new game
 *
 */
void Menu::newGame()
{
    // Player initializing
    cout << "Let's Play!" << endl;
    cout << endl;

    // initialize the TileBag and GameBoard objects
    LinkedList *list = new LinkedList();
    TileBag *tb = new TileBag(list);
    GameBoard *gb = new GameBoard();

    cout << "Player 1 starts first." << endl;
    cout << endl;

    // start playing the game
    GameEngine *ge = new GameEngine(tb, players, gb);
    ge->gamePlay();
}

void Menu::loadGame(string inputFile)
{
    // initialize the TileBag and GameBoard objects
 
    LinkedList* list = new LinkedList();
    TileBag *tb = new TileBag();
    GameBoard *gb = new GameBoard();
    
    ifstream gameData;
    tb->setAsList(list);
 
    // clear current players in the container
    players.~vector();
 
    gameData.open(inputFile);
 
    if (!gameData || gameData.fail())
    {
        cout << "Error loading game" << endl;
        this->runMenu();
    }
    // GET CURRENT PLAYER INDEX
    int current_player_index;
    gameData >> current_player_index;
    // GET PLAYER COUNT
    int pl_count;
    gameData >> pl_count;
    // INTIALIZE PLAYERS
    string name;
    int score;
    int pass_count;
 
    string line;
 
    for (int i = 0; i < pl_count; i++)
    {
        // load player from the file
        Player *tmp_pl = new Player();
        // basic string
 
        // load the player name, score, pass_count
        gameData >> name;
        gameData >> score;
        gameData >> pass_count;
        // tiles
        getline(gameData >> ws, line);
        stringstream ss(line);
        int x = 0;
        // parse the Tiles in the player's hand
        for (int i = 0; i < 7; i++)
        {
            char tmp_char = line[0 + x];
            if(tmp_char == 'Q' || tmp_char == 'Z')
            {
                int tmp_value = line[2 + x] - '0';
                tmp_value *= 10;
                Tile *tmp_tl = new Tile(tmp_char, tmp_value);
                tmp_pl->addToHand(tmp_tl);
                x += 6;
            }
            else
            {
                int tmp_value = line[2 + x] - '0';
                Tile *tmp_tl = new Tile(tmp_char, tmp_value);
                tmp_pl->addToHand(tmp_tl);
                x += 5;
            }
            
        }
        // setters
        // initialize the loader player
        tmp_pl->setName(name);
        tmp_pl->setScore(score);
        tmp_pl->setPassCounter(pass_count);
        tmp_pl->printHand();
        players.push_back(tmp_pl);
    }
 
    // TileBag
    // load the left TileBag from the file
    getline(gameData >> ws, line);
    stringstream ss(line);
    vector<Tile *> tile_bag;
    while (getline(ss, line, ','))
    {
        // parse the tile from the file
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
        char tmp_tb_char = line[0];
        int tmp_tb_int = line[2] - '0';
        Tile *tmp_tile = new Tile(tmp_tb_char, tmp_tb_int);
        tile_bag.push_back(tmp_tile);
    }
 
    int new_tb_size = tile_bag.size();
 
    for (int tl = 0; tl < new_tb_size; tl++)
    {
        // initialize the TileBag object
        Tile* tmp = new Tile(tile_bag[tl]->getLetter(), tile_bag[tl]->getValue());
        tb->addBack(tmp);
    }
 
    // Skip lines
    for (int skip = 0; skip < 17; skip++)
    {
        getline(gameData, line);
    }
    GameEngine *ge = new GameEngine(tb, players, gb);
    // Board tiles
    line.clear();
    // load the game board from the file
    getline(gameData >> ws, line);
    stringstream ss2(line);
    while (getline(ss2, line, ','))
    {
        // initialize the GameBoard from the parameters loaded from the file
        line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
        char tmp_board_char = line[0];
        char board_row_char = line[2];
        int board_col = line[3] - '0';
        int board_row = ge->boardRow.find(board_row_char)->second;
        Tile *tmp_board_tile = new Tile(tmp_board_char, ge->valueByLetter(tmp_board_char));
 
        gb->addTile(board_row, board_col, tmp_board_tile);
    }

    // set current player
    ge->curr_player_turn = current_player_index;
    // set word matcher toggle
    bool toggle;
    gameData >> toggle;
    ge->setWordMatcherToggle(toggle);
    // start playing the game
    ge->gamePlay();
}

// Read current players from file
void Menu::readPlayerFile(){
    map<int, string, std::greater_equal<int> > toSort;

    ifstream playerFile;
    playerFile.open("players.txt");

    if (!playerFile){
        std::cout << "Error opening player file" << std::endl;
    }else{
        string name;
        int score;

        while (!playerFile.eof()){
            playerFile >> name;
            playerFile >> score;
            toSort.insert(std::pair<int, string>(score, name));
        }
    }

    for (auto iter = toSort.begin(); iter != toSort.end(); ++iter){
        nameScoreVector.push_back(std::make_pair(iter->second, iter->first));
    }

    playerFile.close();
}

// Check if name is unique from playerFile
bool Menu::isPlayerNameUnique(string name){
    ifstream playerFile;
    playerFile.open("players.txt");
    bool toRet = false;
    if (!playerFile){
        std::cout << "Error opening player file" << std::endl;
    }else{
        string line;
        int sz = nameScoreVector.size();
        for (int i = 0; i < sz; i++){
            if (nameScoreVector[i].first == name){
                return false;
            }else{
                toRet = true;
            }
        }
    }

    playerFile.close();
    return toRet;
}

void Menu::printTopPlayers(){
    int nameScoreVectorSize = nameScoreVector.size();
    if (nameScoreVectorSize > 3){
        for (int i = 0; i < 3; i++){
            cout << (i+1) << ". "<< nameScoreVector[i].first << ", Score: " << nameScoreVector[i].second << endl;
        }
    }else{
        for (int i = 0; i < nameScoreVectorSize; i++){
            cout << (i+1) << ". "<< nameScoreVector[i].first << ", Score: " << nameScoreVector[i].second << endl;
        }
    }
    cout << endl;
}