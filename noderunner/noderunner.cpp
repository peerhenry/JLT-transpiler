#include <direct.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <string>
#include <vector>
#include <sys/stat.h>
#define string std::string
#define vector std::vector

string GetExeFileName()
{
  char buffer[MAX_PATH];
  GetModuleFileName( NULL, buffer, MAX_PATH );
  return string(buffer);
}

string GetExePath()
{
  string f = GetExeFileName();
  return f.substr(0, f.find_last_of( "\\/" ));
}

void RunCommand(string command)
{
    if(!system(NULL)) exit(EXIT_FAILURE);
    system(command.c_str());
}

int main(int argc, char* argv[])
{
    string entry = "build\\app.js";
    string port = "3000";
    if(argc > 1) entry = argv[1];
    if(argc > 2) port = argv[2];
    string exePath = GetExePath();
    string npmCommand = "start node \"" + exePath + "\\" + entry + "\"";
    printf(("starting node in: " + entry + "\n").c_str());
    RunCommand(npmCommand);
    printf(("starting firefox on localhost:" + port + "\n").c_str());
    string browserCommand = "start firefox localhost:" + port;
    RunCommand(browserCommand);
    return 0;
}
