#include "Request.h"
#include "Log.h"

using namespace std;

Request::Request(int sockfd)
{
    this->sockfd = sockfd;
}

Request::~Request()
{
}

/******************
*   Accessors     *
*******************/

string Request::getType() {
    return this->type;
}

/******************
*     Methods     *
*******************/

string Request::getMessage() {
    int receive = recv(this->sockfd, this->buff_out, Socket::BUFFER_SZ, 0);

    if(receive < 0) {
        Log::write("GAME", "Cannot read player message");
        return "";
    }

    while (receive > 0 && (this->buff_out[receive - 1] == '\n' || this->buff_out[receive - 1] == '\r'))
        receive--;
    
    if (receive >= 0 && receive < Socket::BUFFER_SZ)
        this->buff_out[receive] = '\0';

    string msg = string(this->buff_out);

    return msg;
}

bool Request::testRegex(string msg) {
    if (regex_match(msg, this->rgx)) return true;

    this->type = "null";
    this->body = "null";
    return false;
}

Request *Request::wait() {
    string msg = this->getMessage();

    bool regexMatch = this->testRegex(msg);
    
    if (!regexMatch) return this;

    this->type = msg.substr(0, msg.find(" "));
    this->body = msg.substr(msg.find(" ")).erase(0, 1);

    return this;
}
