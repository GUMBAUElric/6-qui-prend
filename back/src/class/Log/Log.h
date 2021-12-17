#ifndef DEF_LOG
#define DEF_LOG

#include <string>

class Log
{
    public:
        // Methods
        static void write(std::string, std::string); 
        static void writeError(std::string); 

        // Constructor & Destructor
        Log();
        ~Log();
};

#endif
