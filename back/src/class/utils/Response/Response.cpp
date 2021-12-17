#include "Response.h"
#include "Log.h"

using namespace std;

Response::Response()
{
}

Response::~Response()
{
}

/******************
*     Methods     *
*******************/

string Response::jsonnifyMessage(string type, string msg) {
    string jsonMsg = "";
    
    if (msg.rfind("[", 0) == 0) {
        jsonMsg = "{\"type\": \"" + type + "\", \"message\": " + msg + "}" + "\n";
    } else {
        jsonMsg = "{\"type\": \"" + type + "\", \"message\": \"" + msg + "\"}" + "\n";
    }

    return jsonMsg;
}

void Response::send(int sockfd, string type, string msg) {
    this_thread::sleep_for(std::chrono::milliseconds(100));
    string jsonMsg = this->jsonnifyMessage(type, msg);
    const char *s = jsonMsg.c_str();
    if(write(sockfd, s, strlen(s)) < 0) Log::writeError("Write to descriptor failed");
}
