#ifndef DEF_JSON
#define DEF_JSON

#include <string>
#include <vector>
#include <array>
#include "Card.h"

class Player;

class Json
{
    protected:
        //Methods
        std::string jsonify(std::vector<std::array<std::string, 2> >);
        std::string jsonifyOpponentsPlayers(std::vector<std::array<std::string, 2> >);
        std::string jsonifyRows(std::vector <std::vector <Card *> >);
        std::string jsonifyCards(std::vector <Card *>);
        std::string jsonifyPlayersPoints(std::vector<std::array<std::string, 2> >);
    
    public:
        // Constructor & Destructor
        Json();
        ~Json();
};

#endif
