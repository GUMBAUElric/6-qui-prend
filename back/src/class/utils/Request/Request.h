#ifndef DEF_REQUEST
#define DEF_REQUEST

#include "Socket.h"
#include <string>
#include <regex>

class Request
{
    private:
        // Attributes 
        int sockfd;
        char buff_out[Socket::BUFFER_SZ] = "";
        std::string type;
        const std::regex rgx = std::regex("[a-zA-Z]+ [a-zA-Z0-9]+");  

        // Methods
        std::string getMessage();
        bool testRegex(std::string);

    public:
        // Attributes
        std::string body;

        // Methods
        Request *wait();

        // Accessors
        std::string getType();

        // Constructor & Destructor
        Request(int);
        ~Request();
};

#endif
