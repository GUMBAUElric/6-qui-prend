#include "GameCore.h"
#include "Log.h"
#include "Request.h"
#include "Json.h"

using namespace std;

GameCore::GameCore(string ip, int port)
{
    this->socket = new Socket(ip, port);
    this->generateDeck();
    this->generateRows();
    this->countdown = new CountDown();
}

GameCore::~GameCore()
{
}

/******************
*   Accessors     *
*******************/

bool GameCore::getPartyIsStarted() {
    return this->partyIsStarted;
}

int GameCore::getConnfd() {
    return this->socket->connfd;
}

vector <Player *> GameCore::getPlayers() {
    return this->players;
}

vector <Card *> GameCore::getDeck() {
    return this->deck;
}

vector <Card *> GameCore::getDeckRound() {
    return this->deckRound;
}

string GameCore::getJsonRows() {
    return this->jsonifyRows(this->rows);
}

string GameCore::getJsonDeckRound() {
    return this->jsonifyCards(this->deckRound);
}

vector <vector <Card *> > GameCore::getRows() {
    return this->rows;
}

/******************
*    Mutators     *
*******************/

void GameCore::setPartyIsStarted(bool isStarted) {
    this->partyIsStarted = isStarted;
}

void GameCore::setDeck(std::vector <Card *> deck) {
    this->deck = deck;
}

/******************
*     Methods     *
*******************/

void GameCore::generateDeck() {
    int endWithZero = 10;
    int isDouble = 11;

    for (int i = 1; i <= 104; i++)
    {
        if (i == 55) {
            this->deck.push_back(new Card(i, 7));
        } 
        else if (i % endWithZero == 0) {
             this->deck.push_back(new Card(i, 3));
             endWithZero += 10;
        } 
        else if (i % isDouble == 0) {
            this->deck.push_back(new Card(i, 5));
             isDouble += 11;
        } 
        else if (i % 5 == 0) {
            this->deck.push_back(new Card(i, 2));
        } 
        else {
            this->deck.push_back(new Card(i, 1));
        }
    }
    
    shuffle(this->deck.begin(), this->deck.end(), random_device());
}

void GameCore::generateRows() {
    for (int i = 0; i < 4; i++)
    {
        vector <Card *> vec;
        vec.push_back(this->deck[i]);
        this->rows.push_back(vec);
        this->deck.erase(this->deck.begin() + i);
    }
}

void GameCore::sortDeckRoundByAscending() {
    sort(this->deckRound.begin(), this->deckRound.end());
}

bool GameCore::playersAreReady() {
    if (this->players.size() <= 1) return false;

    bool areReady = true;

    for (int i = 0; i < this->players.size(); i++)
    {
        if (!this->players[i]->getIsReady()) areReady = false;
    }
    
    return areReady;
}

bool GameCore::playersHasPlayed() {
    bool hasPlayed = true;

    for (int i = 0; i < this->players.size(); i++)
    {
        if (!this->players[i]->getHasPlayed()) hasPlayed = false;
    }
    
    return hasPlayed;
}

bool GameCore::playersHasChoosenRow() {
    bool hasChoosen = true;

    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->getChoosenRow()) hasChoosen = false;
    }
    
    return hasChoosen;
}

bool GameCore::maxPlayerIsReached() {
    bool isReached = this->players.size() == this->MAX_PLAYERS;

    if (isReached) {
        Log::write("GAME", "Max players connected. Connection rejected");
        this->socket->close();
    }

    return isReached;
}

string GameCore::generateUserUid() {
    static random_device dev;
    static mt19937 rng(dev());

    uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = { 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0 };

    string res;
    for (int i = 0; i < 16; i++) {
        if (dash[i]) res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    
    return res;
}

void GameCore::createThread(void *arg) {
    pthread_create(&this->tid, NULL, &GameCore::handlePlayer, arg);
}

void GameCore::start() {
    this->socket->listen();
}

void GameCore::waitPlayers() {
    socklen_t clilen = sizeof(this->socket->cli_addr);
    this->socket->accept(clilen);
}

void GameCore::addPlayer(Player *player) {
    this->lockThread();

    vector<Player *>::iterator it = find(this->players.begin(), this->players.end(), player);

     if(it == this->players.end()) {
        Log::write("GAME", "Add new player");
        this->players.push_back(player);
    }

    this->unlockThread();

    this->createThread(player);
}

void GameCore::removePlayer(Player *player) {
    vector <array<string, 2> > values;

    array <string, 2> uidJson = {"uid", player->getUid()};
    values.push_back(uidJson);

    player->sendMessageToOpponents("playerExit", this->jsonify(values));

    this->socket->close(player->getSockfd());

    this->lockThread();

    vector<Player *>::iterator it = find(this->players.begin(), this->players.end(), player);

    if(it != this->players.end()) {
        Log::write("GAME", "Delete player");
        this->players.erase(it);
    }

    this->unlockThread();
}

void GameCore::sendMessage(string type, string msg) {
    for (int i = 0; i < this->players.size(); i++)
    {
        this->send(this->players[i]->getSockfd(), type, msg);
    }
}

void GameCore::addCardToDeckRound(Card *card) {
    this->deckRound.push_back(card);
}

void GameCore::distributePlayersCards() {
    for (int i = 0; i < this->players.size(); i++) this->players[i]->distributeCards();
}

void GameCore::addCardsToRows() {
    this->sortDeckRoundByAscending();

    for (int i = this->deckRound.size(); i <= this->deckRound.size(); i--)
    {
        if (this->gameIsFinish || this->deckRound.size() == 0) break;

        Card *cardPlayer = this->deckRound[0];
        int rowData[2] = {-1, -1};

        for (int j = 0; j < this->rows.size(); j++)
        {

            Card *lastCard = this->rows[j].back();
            int val = cardPlayer->getNumber() - lastCard->getNumber();

            /*
            * Check which row is to be played by subtracting the player's card value 
            * and the last card in the row
            */
            if(val > 0) {
                if(rowData[1] == -1) {
                    rowData[0] = j;
                    rowData[1] = val;
                    continue;
                }

                if (val < rowData[1]) {
                    rowData[0] = j;
                    rowData[1] = val;
                }
            }
        }

        if (rowData[0] == -1) {
            // Found the player that must select a row to flush
            for (int k = 0; k < this->players.size(); k++)
            {
                if (this->players[k]->getUid() != cardPlayer->getBelongsTo()) continue;
                this->players[k]->setChoosenRow(true);
                break;
            }
            break;
        } else {
            // Check if row need to be flushed
             if (this->rows[rowData[0]].size() == this->MAX_CARDS_IN_ROWS) {
                this->flushRow(rowData[0]);
                continue;
            }

            this->rows[rowData[0]].push_back(cardPlayer);
            this->deckRound.erase(this->deckRound.begin());
        }
    }

}

void GameCore::flushRow(int row) {
    int points = 0;

    for (int i = 0; i < this->rows[row].size(); i++)
    {
        this->deck.push_back(this->rows[row][i]);
        points += this->rows[row][i]->getValue();
    }

    Log::write("GAME", "Flushing row");

    for (int i = 0; i < this->players.size(); i++)
    {
        if (this->players[i]->getUid() == this->deckRound[0]->getBelongsTo()) {

            this->players[i]->setPoints(points);

            if (this->players[i]->getPoints() >= this->MAX_PLAYER_POINTS) this->gameIsFinish = true;
            
            break;
        }
    }
            
    this->rows[row].clear();
    this->rows[row].push_back(this->deckRound[0]);
    this->deckRound.erase(this->deckRound.begin());
}

void GameCore::resetHasPlayedState() {
    for (int i = 0; i < this->players.size(); i++)
    {
       this->players[i]->setHasPlayed(false);
    }
}

void GameCore::sendCardsToPlayers() {
    for (int i = 0; i < this->players.size(); i++) {
        this->players[i]->sendMessage("showCards",  this->players[i]->getJsonCards());
    }
}

void GameCore::sendPlayersPoints() {
    vector <array<string, 2> > playerPoints;

    for (int i = 0; i < this->players.size(); i++)
    {
        array <string, 2> player = {this->players[i]->getUid(), to_string(this->players[i]->getPoints())};

        playerPoints.push_back(player);
    }

    this->sendMessage("showPoints", this->jsonifyPlayersPoints(playerPoints));
}

void GameCore::restartRound() {
    Log::write("GAME", "Restarting round");

    this->deck.clear();
    this->rows.clear();
    this->deckRound.clear();
    
    this->generateDeck();
    this->generateRows();

    this->sendPlayersPoints();
    this->sendMessage("newRound", "1");

    sleep(this->TIME_WAITING);

    this->sendMessage("showRows", this->getJsonRows());

    for (int i = 0; i < this->players.size(); i++)
    {
        this->players[i]->getCards().clear();
        this->players[i]->distributeCards();
    }
}

void GameCore::endGame() {
    this->sendMessage("endGame", "1");
    
    this->deck.clear();
    this->rows.clear();
    this->deckRound.clear();

    vector <array<string, 2> > playerPoints;

    for (int i = 0; i < this->players.size(); i++)
    {
        array <string, 2> player = {this->players[i]->getUid(), to_string(this->players[i]->getPoints())};

        playerPoints.push_back(player);
    }

    this->sendMessage("playersPoint", this->jsonifyPlayersPoints(playerPoints));
    
    for (int i = 0; i < this->players.size(); i++)
    {
        this->players[i]->resetPlayerState();
    }

    this->partyIsStarted = false;
    this->gameIsFinish = false;

    this->generateDeck();
    this->generateRows();
}

void GameCore::handleGame(Player *player) {    
    this->lockThread();

    if (this->deckRound.size() == this->players.size()) this->sendMessage("showDeckRound", this->getJsonDeckRound());

    this->addCardsToRows();

    if (this->gameIsFinish) {
        this->endGame();
        return;
    }

    // Check if at least one player has to choose a row
    if (this->playersHasChoosenRow()) {
        this->resetHasPlayedState();
    
        sleep(this->TIME_WAITING);

        this->sendMessage("clearDeckRound", "1");

        this->sendMessage("showRows", this->getJsonRows());

        if (player->getCards().size() == 0) {
            this->restartRound();
            return;
        }

        this->sendCardsToPlayers();

        this->sendPlayersPoints();
    }

    this->unlockThread();
}

void *GameCore::handlePlayer(void *ply) {
    int leaveFlag = 0;

    Player *player = (Player*)ply;
    GameCore *gameCore = player->gameCore;

    while (!leaveFlag)
    {
        Request *req = player->request->wait();

        if (req->getType() == "null") {
            player->sendError("Commande invalide");
            continue;
        }

        // EXIT
        if (req->getType() == "EXIT" && req->body == "1") {
            leaveFlag = 1;
            continue;
        }

        // Set player name
        if (req->getType() == "setName" && player->getName() == "") {
            string name = req->body;

            if (name.size() < 3) {
                player->sendError("Nom trop court");
                continue;
            }

            player->setName(name);

            continue;
        }
        
        if (player->getName() == "") continue;

        // Set player ready
        if (!gameCore->getPartyIsStarted()) {

            if (req->getType() != "setReady") continue;
            
            if (req->body == "1" && !player->getIsReady()) player->setIsReady(true);
            
            if (req->body == "0" && player->getIsReady()) player->setIsReady(false);

            if (!gameCore->countdown->getIsLaunch() && gameCore->playersAreReady()) {
                Log::write("GAME", "All players are ready, starting countdown...");
                gameCore->sendMessage("countDown", "1");
                gameCore->countdown->createThread(gameCore);
            }
        }

        // Game
        if (gameCore->getPartyIsStarted()) {
            string type = req->getType();

            // Play card
            if (type == "playCard") {
                if (player->getHasPlayed()) {
                    player->sendMessage("alreadyPlayed", "1");
                    continue;
                }

                player->removeCard(req->body);
                player->setHasPlayed(true);

                // All players have played their cards
                if (gameCore->playersHasPlayed()) gameCore->handleGame(player);
            }

            // Choose row
            if (type == "chooseRow" && player->getChoosenRow()) {
                // Flush row
                int row = stoi(req->body) - 1;
                gameCore->flushRow(row);

                if (gameCore->gameIsFinish) {
                    gameCore->endGame();
                    continue;
                }

                player->setChoosenRow(false);
                gameCore->handleGame(player);
            }
        }

        sleep(1);
    }

    gameCore->removePlayer(player);

    delete player;

    gameCore->detachThread();

    return 0;
}
