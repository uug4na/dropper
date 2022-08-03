#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <Lmcons.h>
using std::string;
using namespace std;

string getFileName(const string& s) {
    char sep = '/';
#ifdef _WIN32
    sep = '\\';
#endif
    size_t i = s.rfind(sep, s.length());
    if (i != string::npos) {
        return(s.substr(i + 1, s.length() - i));
    }
    return("");
}

void dropShit(string path) {
    ofstream MyFile(path);
    MyFile << "have a nice day";
    MyFile.close();
}

int main(int argc, char** argv) {
    char fileName[MAX_PATH];
    char username[UNLEN + 1];
    DWORD len = UNLEN + 1;
    GetUserName(username, &len);
    string path = argv[0];

    string newFile;
    string first = "C:\\Users\\";
    string second = "\\Desktop\\hacked.txt";
    
    newFile = first + username + second;
    cout << "The file name is: " << getFileName(path) << endl;
    cout << "New FileName: " << newFile << endl;

    if (getFileName(path) == "dropper.exe") {
        cout << "DROPPING :))" << endl;
        dropShit(newFile);
    }
    else
        cout << "F TEST" << endl;
}
