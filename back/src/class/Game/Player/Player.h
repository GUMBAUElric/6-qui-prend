#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <string>
#include <vector>
#include "Socket.h"
#include "Response.h"
#include "Request.h"
#include "Card.h"

class GameCore;

class Player : public Response
{
    private:
        // Attributes 
        int sockfd;
        int points = 0;
        bool isReady = false;
        bool hasPlayed = false;
        bool choosenRow = false;
        std::vector <Card *> cards;
        std::string name;
        std::string uid;

    public:
        // Attributes 
        GameCore *gameCore;
        Request *request;

        // Accessors 
        int getSockfd();
        int getPoints();
        bool getIsReady();
        bool getHasPlayed();
        bool getChoosenRow();
        std::vector <Card *> getCards();
        std::string getName();
        std::string getUid();
        std::string getJsonCards();

        // Mutators
        void setName(std::string);
        void setPoints(int);
        void setIsReady(bool);
        void setHasPlayed(bool);
        void setChoosenRow(bool);

        // Methods
        void sendMessage(std::string, std::string);
        void sendMessageToOpponents(std::string, std::string);
        void sendError(std::string);
        void distributeCards();
        void removeCard(std::string);
        void resetPlayerState();
        
        // Constructor & Destructor
        Player(GameCore *, int);
        ~Player();
};

#endif
