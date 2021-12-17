#ifndef DEF_CARD
#define DEF_CARD

#include <string>

class Card
{
    private:
        // Attributes
        int number;
        int value;
        std::string uid;

    public:
        // Accessors
        int getNumber();
        int getValue();
        std::string getBelongsTo();

        // Mutators
        void belongsTo(std::string);
        
        // Constructor & Destructor
        Card(int, int);
        ~Card();
};

#endif
