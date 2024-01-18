#include <iostream>
#include <zmqpp/zmqpp.hpp>
#include "../core/constants.h"

using namespace std;

int main(int argc, char** argv){

    const str endpoint = "tcp://localhost:4242";

    // initialize the 0MQ context
    zmqpp::context context;

    // generate a pull socket
    zmqpp::socket_type type = zmqpp::socket_type::pull;
    zmqpp::socket socket (context, type);

    // bind to the socket
    cout << "Binding to " << endpoint << "..." << endl;
    socket.bind(endpoint);

    // receive the message
    cout << "Receiving message..." << endl;
    zmqpp::message message;
    // decompose the message
    socket.receive(message);
    string text;
    int number;
    message >> text >> number;

    cout << "Received text:\"" << text << "\" and a number: " << number << endl;
    cout << "Finished." << endl;
    return 0;
}
