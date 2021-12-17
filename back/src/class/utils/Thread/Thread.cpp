#include "Thread.h"
#include "Player.h"
#include "GameCore.h"
#include "Log.h"

using namespace std;

Thread::Thread()
{
}

Thread::~Thread()
{
}

/******************
*     Methods     *
*******************/

void Thread::detachThread() {
    pthread_detach(pthread_self());
}

void Thread::lockThread() {
    pthread_mutex_lock(&this->players_mutex);
}

void Thread::unlockThread() {
    pthread_mutex_unlock(&this->players_mutex);
}
