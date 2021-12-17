#include "GameCore.h"
#include "Player.h"

int main(int argc, char const *argv[])
{
    std::string ip = argv[1];
    int port = std::stoi(argv[2]);

    GameCore gameCore(ip, port);

    gameCore.start();

    while (1)
    {
        
        gameCore.waitPlayers();

        if (gameCore.maxPlayerIsReached()) continue;

        Player *player = new Player(&gameCore, gameCore.getConnfd());

        gameCore.addPlayer(player);

        // Reduce CPU Usage
        sleep(1);
    }
    
    return 0;
}
 