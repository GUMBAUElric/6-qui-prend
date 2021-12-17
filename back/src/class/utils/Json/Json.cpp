#include "Json.h"
#include "Player.h"

using namespace std;

Json::Json(/* args */)
{
}

Json::~Json()
{
}

/******************
*     Methods     *
*******************/

string Json::jsonify(vector <array<string, 2> > values) {
    string jsonMsg = "[{";

    for (int i = 0; i < values.size(); i++)
    {
        jsonMsg += "\"" + values[i][0] + "\": \"" + values[i][1] + "\", ";
    }

    jsonMsg.resize(jsonMsg.size() - 2);

    jsonMsg += "}]";

    return jsonMsg;
}

string Json::jsonifyOpponentsPlayers(vector <array<string, 2> > values) {
    string jsonMsg = "[";

    for (int i = 0; i < values.size() ; i++)
    {
        jsonMsg += "{";
        
        jsonMsg += "\"uid\" : \"" + values[i][0] + "\", ";
        jsonMsg += "\"name\" : \"" + values[i][1] + "\"";

        jsonMsg += "}, ";
    }

    jsonMsg.resize(jsonMsg.size() - 2);
    jsonMsg += "]";

    return jsonMsg;
}

string Json::jsonifyRows(vector <vector <Card *> > rows) {
    string jsonCards = "[";

    for (int i = 0; i < rows.size(); i++)
    {
        jsonCards += "[";

        for (int j = 0; j < rows[i].size(); j++)
        {
            string number = to_string(rows[i][j]->getNumber());
            string value = to_string(rows[i][j]->getValue());
            string belongsTo = rows[i][j]->getBelongsTo();

            jsonCards += "{\"number\": " + number + ", \"value\": " + value + ", \"belongsTo\": \"" + belongsTo + "\"}, ";
        }

        jsonCards.resize(jsonCards.size() - 2);

        jsonCards += "], ";
    }

    jsonCards.resize(jsonCards.size() - 2);

    jsonCards += "]";

    return jsonCards;
}

string Json::jsonifyCards(vector <Card *> cards) {
     string jsonCards = "[";

    for (int i = 0; i < cards.size(); i++)
    {
        string number = to_string(cards[i]->getNumber());
        string value = to_string(cards[i]->getValue());
        string belongsTo = cards[i]->getBelongsTo();

        jsonCards += "{\"number\" : " + number + ", \"value\": " + value + ", \"belongsTo\": \"" + belongsTo + "\"}, ";
    }

    jsonCards.resize(jsonCards.size() - 2);

    jsonCards += "]";

    return jsonCards;
}

string Json::jsonifyPlayersPoints(vector <array<string, 2> > values) {
    string jsonMsg = "[";

    for (int i = 0; i < values.size() ; i++)
    {
        jsonMsg += "{";
        
        jsonMsg += "\"uid\" : \"" + values[i][0] + "\", ";
        jsonMsg += "\"points\" : \"" + values[i][1] + "\"";

        jsonMsg += "}, ";
    }

    jsonMsg.resize(jsonMsg.size() - 2);
    jsonMsg += "]";

    return jsonMsg;
}
