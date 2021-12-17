#include "CountDown.h"
#include "GameCore.h"
#include "Log.h"

using namespace std;

CountDown::CountDown()
{
}

CountDown::~CountDown()
{
}

/******************
*   Accessors     *
*******************/

bool CountDown::getIsLaunch() {
    return this->isLaunch;
}

/******************
*    Mutators     *
*******************/

void CountDown::setIsLaunch(bool isLaunch) {
    this->isLaunch = isLaunch;
}

/******************
*     Methods     *
*******************/

void CountDown::createThread(void *arg) {
    pthread_create(&this->tid, NULL, &CountDown::start, arg);
}

void *CountDown::start(void *gameCore) {
    int counter = CountDown::TIMER; //amount of seconds

    GameCore *_gameCore = (GameCore*)gameCore;

    _gameCore->countdown->setIsLaunch(true);

    while (counter >= 1)
    {
        if(!_gameCore->playersAreReady()) {
            Log::write("GAME", "All players are not ready, stop countdown");
            _gameCore->sendMessage("countDown", "0");
            break;    
        }
        
        sleep(1);
        counter--;
    }

    if (counter == 0) {
        _gameCore->setPartyIsStarted(true);
        Log::write("GAME", "Party starting");
        _gameCore->sendMessage("showRows", _gameCore->getJsonRows());
        _gameCore->distributePlayersCards();
    }

    _gameCore->countdown->setIsLaunch(false);
    _gameCore->countdown->detachThread();

    return 0;
}
