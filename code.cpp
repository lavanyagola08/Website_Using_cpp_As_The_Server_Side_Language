#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // Include this header for inet_ntoa

using namespace std;

const int PORT = 8080;
const string ROOT_DIRECTORY = "webroot"; // Folder containing HTML and CSS files

// ... (rest of the code)

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t sinSize = sizeof(struct sockaddr_in);

    // Create socket
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error in socket");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(serverAddr.sin_zero), '\0', 8);

    // Bind socket to address
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr)) == -1) {
        perror("Error in binding");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) == -1) {
        perror("Error in listening");
        exit(1);
    }

    cout << "Server is listening on port " << PORT << "..." << endl;

    while (true) {
        // Accept incoming connection
        if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &sinSize)) == -1) {
            perror("Error in accepting connection");
            continue;
        }

        cout << "Received a connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;

        // ... (rest of the code)

        close(clientSocket);
        cout << "Connection closed." << endl;
    }

    return 0;
}
