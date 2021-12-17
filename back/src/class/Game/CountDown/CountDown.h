#ifndef DEF_COUNTDOWN
#define DEF_COUNTDOWN

#include "Thread.h"

class CountDown : public Thread
{
    private:
        // Attributes
        bool isLaunch = 0;
        
    public:
        // Attibutes
        static const int TIMER = 10;

        // Accessors
        bool getIsLaunch();

        // Mutators
        void setIsLaunch(bool);

        // Methods
        void createThread(void *); // Redefined virtual method
        static void *start(void *);

        // Constructor & Destructor
        CountDown();
        ~CountDown();
};

#endif
