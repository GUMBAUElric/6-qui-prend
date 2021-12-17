#ifndef DEF_THREAD
#define DEF_THREAD

#include <string>
#include <pthread.h>
#include "Response.h"

class Thread : public Response
{
    private:
        // Attributes 
        pthread_mutex_t players_mutex;

    protected:
        // Attributes 
        pthread_t tid;

        // Methods
        void detachThread();

    public:
        // Methods
        void lockThread();
        void unlockThread();

        // Virtual method
        virtual void createThread(void *) = 0;

        // Constructor & Destructor
        Thread();
        virtual ~Thread();
};

#endif
