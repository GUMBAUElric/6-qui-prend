#ifndef DEF_RESPONSE
#define DEF_RESPONSE

#include <string>
#include <unistd.h>
#include <chrono>
#include <thread>
#include "Json.h"

class Response : public Json
{
    private:
        // Methods
        std::string jsonnifyMessage(std::string, std::string); 

    public:
        // Methods
        void send(int, std::string, std::string);

        // Constructor & Destructor
        Response();
        ~Response();
};

#endif
