#include <iostream>
#include <vector>
#include "lib/netry/include/NetStream.h"
#include "include/FileHandler.h"

using namespace netry;
using namespace std;

int main() {

    Socket socket("0.0.0.0", 5000);
    NetStream stream(socket);

    vector<string> fileNames;

    // 01
    // Receive the number of files
    int numberOfFiles = stoi(stream.readString());

    // 02
    // Receive the names of the files
    for (int i = 0; i < numberOfFiles; i++) {
        fileNames.push_back(stream.readString());
    }

    // Show file names
    for (int i = 0; i < fileNames.size(); i++) {
        cout << i + 1 << " " << fileNames[i] << endl;
    }

    // 03
    // Message before sending the file number
    cout << stream.readString();

    // Get file number from user
    int option;
    cin >> option;

    // 04
    // Send the file number
    stream.writeInt(option - 1);

    // 05
    // Receive file confirmation
    cout << stream.readString();
    string fileName = stream.readString();
    cout << fileName << endl;

    // 06
    // Receive the file size
    int fileSize = stream.readInt();
    cout << endl << "File size: " << fileSize << " bytes" << endl;

    cout << "Downloading..." << endl;

    string condition;
    const size_t kBufferSize = 1024;
    char buffer[kBufferSize];

    FILE *pFile = FileHandler::openOutputFile(fileName);
    int totalBytesReceived = 0;

    // 07
    condition = stream.readString();

    while (condition == "_continue") {
        // TODO: implement protocol for confirmation of bytes received by the client

        // 08
        stream.readBytes(buffer);
        totalBytesReceived += fwrite(buffer, sizeof(unsigned char), kBufferSize, pFile);

        // 07
        condition = stream.readString();
    }

    cout << "Download completed " << endl;
    cout << "Bytes: " << totalBytesReceived << endl;

    // Sleeps some time so we can test several clients connected
    // sleep(20);

    fclose(pFile);
    socket.close();

    return 0;
}