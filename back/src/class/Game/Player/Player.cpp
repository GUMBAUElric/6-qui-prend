#include "Player.h"
#include "GameCore.h"
#include "Log.h"
#include "Json.h"

using namespace std;

Player::Player(GameCore *gameCore, int connfd)
{
    this->gameCore = gameCore;
    this->sockfd = connfd;
    this->uid = this->gameCore->generateUserUid();
    this->request = new Request(this->sockfd);
}

Player::~Player()
{
}

/******************
*   Accessors     *
*******************/

int Player::getSockfd() {
    return this->sockfd;
}

int Player::getPoints() {
    return this->points;
}

bool Player::getIsReady() {
    return this->isReady;
}

bool Player::getHasPlayed() {
    return this->hasPlayed;
}

bool Player::getChoosenRow() {
    return this->choosenRow;
}

vector <Card *> Player::getCards() {
    return this->cards;
}

string Player::getName() {
    return this->name;
}

string Player::getUid() {
    return this->uid;
}

string Player::getJsonCards() {
   return this->jsonifyCards(this->cards);
}

/******************
*    Mutators     *
*******************/

void Player::setName(string name) {
    this->name = name;
    vector <array<string, 2> > values;

    array <string, 2> uidJson = {"uid", this->uid};
    array <string, 2> nameJson = {"name", this->name};

    values.push_back(uidJson);
    values.push_back(nameJson);
    
    this->sendMessage("nameSet", this->jsonify(values));
    this->sendMessageToOpponents("newPlayer", this->jsonify(values));

    if (this->gameCore->getPlayers().size() > 1) {
        vector <array<string, 2> > opponentsPlayers;

        for (int i = 0; i < this->gameCore->getPlayers().size() - 1; i++)
        {
            Player *player = this->gameCore->getPlayers()[i];

            array <string, 2> opponentPlayer = {player->getUid(), player->getName()};

            opponentsPlayers.push_back(opponentPlayer);
        }

        this->sendMessage("playersConnected", this->jsonifyOpponentsPlayers(opponentsPlayers));
    }
}

void Player::setPoints(int points) {
    this->points += points;
}

void Player::setIsReady(bool isReady) {
    this->isReady = isReady;

    if (this->isReady) {
        this->sendMessage("isReady", "1");
        this->sendMessageToOpponents("playerReady", this->uid);
    }
    else {
        this->sendMessage("isReady", "0");
        this->sendMessageToOpponents("playerNotReady", this->uid);
    }
}

void Player::setHasPlayed(bool hasPlayed) {
    this->hasPlayed = hasPlayed;
}

void Player::setChoosenRow(bool choosenRow) {
    this->choosenRow = choosenRow;

    if (this->choosenRow) {
        this->sendMessage("chooseRow", "1");
        this->sendMessageToOpponents("playerChooseRow", this->uid);
    }
    else {
        this->sendMessage("chooseRow", "0");
        this->sendMessageToOpponents("playerHasChoosenRow", this->uid);
    }
}

/******************
*     Methods     *
*******************/

void Player::sendMessage(string type, string msg) {
    this->send(this->sockfd, type, msg);
}

void Player::sendMessageToOpponents(string type, string msg) {
    vector <Player *> players =  this->gameCore->getPlayers();

    for (int i = 0; i < players.size(); i++)
    {
        string uidPlayer = players[i]->getUid();
        int sockfdPlayer = players[i]->getSockfd();
        
        if (uidPlayer != this->uid) {
            this->send(sockfdPlayer, type, msg);
        }
    }
}

void Player::sendError(string err) {
    this->send(this->sockfd, "error", err);
}

void Player::distributeCards() {
    this->gameCore->lockThread();

    vector <Card *> deck = this->gameCore->getDeck();
    
    for (int i = 0; i < 10 ; i++)
    {
        this->cards.push_back(deck[i]);
        this->cards[i]->belongsTo(this->uid);
        deck.erase(deck.begin() + i);
    }

    sort(this->cards.begin(), this->cards.end());

    this->sendMessage("showCards", this->getJsonCards());

    this->gameCore->setDeck(deck);

    this->gameCore->unlockThread();
}

void Player::removeCard(string card) {
    this->gameCore->lockThread();

    int index = stoi(card) - 1;

    Card *cd = this->cards[index];

    this->sendMessageToOpponents("playerPlayed", this->uid);

    this->gameCore->addCardToDeckRound(cd);
    this->cards.erase(this->cards.begin() + index);

    this->sendMessage("cardRemoved", "1");

    this->gameCore->unlockThread();
}

void Player::resetPlayerState() {
    this->cards.clear();
    this->isReady = false;
    this->hasPlayed = false;
    this->choosenRow = false;
    this->points = 0;
}
