#ifndef DEF_GAMECORE
#define DEF_GAMECORE

#include <vector>
#include <random>
#include "Response.h"
#include "Thread.h"
#include "Socket.h"
#include "Player.h"
#include "Card.h"
#include "CountDown.h"

class GameCore : public Thread
{
    private:
        // Attributes
        const int MAX_PLAYERS = 10;
        const int MAX_CARDS_IN_ROWS = 5;
        const int MAX_PLAYER_POINTS = 66;
        const int TIME_WAITING = 10;
        bool partyIsStarted = false;
        bool gameIsFinish = false;
        std::vector <Player *> players;
        std::vector <Card *> deck;
        std::vector <std::vector <Card *> > rows;
        std::vector <Card *> deckRound;
        Socket *socket;

        // Methods
        void generateDeck();
        void generateRows();
        void sortDeckRoundByAscending();

    public:
        // Attributes
        CountDown *countdown;

        // Accessors
        bool getPartyIsStarted();
        int getConnfd();
        std::vector <Player *> getPlayers();
        std::vector <Card *> getDeck();
        std::vector <Card *> getDeckRound();
        std::string getJsonRows();
        std::string getJsonDeckRound();
        std::vector <std::vector <Card *> > getRows();

        // Mutators
        void setPartyIsStarted(bool);
        void setDeck(std::vector <Card *>);

        // Methods
        bool playersAreReady();
        bool playersHasPlayed();
        bool playersHasChoosenRow();
        bool maxPlayerIsReached();
        std::string generateUserUid();
        void createThread(void *); // Redefined virtual method
        void start();
        void waitPlayers();
        void addPlayer(Player *);
        void removePlayer(Player *);
        void sendMessage(std::string, std::string);
        void addCardToDeckRound(Card *);
        void distributePlayersCards();
        void addCardsToRows();
        void flushRow(int);
        void resetHasPlayedState();
        void sendCardsToPlayers();
        void sendPlayersPoints();
        void restartRound();
        void endGame();
        void handleGame(Player *);
        static void *handlePlayer(void *);

        // Constructor & Destructor
        GameCore(std::string, int);
        ~GameCore();
};

#endif
