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

bool IsFile(string const& path)
{
    struct stat buf;
    stat(path.c_str(), &buf);
    return S_ISREG(buf.st_mode);
}

bool IsDirectory(string const& path)
{
    struct stat buf;
    stat(path.c_str(), &buf);
    return S_ISDIR(buf.st_mode);
}

bool StringEndsWith(string const& fullString, string const& ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}

void RunCommand(string command)
{
    if(!system(NULL)) exit(EXIT_FAILURE);
    system(command.c_str());
}

void CompileTypeScript(string const& srcPath, string const& destPath)
{
    RunCommand("tsc \"" + srcPath + "\" --outFILE \"" + destPath.substr(0, destPath.length() - 3) + ".js\"");
}

void CompileJade(string const& srcPath, string const& destPath)
{
    RunCommand("jade < \"" + srcPath + "\" > \"" + destPath.substr(0, destPath.length() - 5) + ".html\"");
}

void CompileLess(string const& srcPath, string const& destPath)
{
    RunCommand("lessc \"" + srcPath + "\" \"" + destPath.substr(0, destPath.length() - 5) + ".css\"");
}

void TranspileDirectory(string const& sourcePath, string const& buildPath, string const& dirPath)
{
    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir (dirPath.c_str())) != NULL)
    {
        while ((ent = readdir(dir)) != NULL)
        {
            string entityName = ent->d_name;
            string fullPath = dirPath + "\\" + entityName;
            string relPath = fullPath.substr(sourcePath.length(), fullPath.length());
            string destPath = buildPath + relPath;
            if(IsDirectory(fullPath) && entityName.compare(".") != 0 && entityName.compare("..") != 0 )
            {
                mkdir(destPath.c_str());
                TranspileDirectory(sourcePath, buildPath, fullPath);
            }
            else if(IsFile(fullPath))
            {
                printf(("transpiling " + fullPath + "\n").c_str());
                if(StringEndsWith(entityName, ".ts")) CompileTypeScript(fullPath, destPath);
                else if(StringEndsWith(entityName, ".jade")) CompileJade(fullPath, destPath);
                else if(StringEndsWith(entityName, ".less")) CompileLess(fullPath, destPath);
                else CopyFile(fullPath.c_str(), destPath.c_str(), FALSE);   // FALSE means overwrite
            }
        }
        closedir (dir);
    }
    else perror ("could not open directory");
}

bool FileExists (string const& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

void InstallPackages(string const& buildPath)
{
    string packagePath = buildPath + "\\package.json";
    if(FileExists(packagePath)) RunCommand("npm --prefix \"" + buildPath + "\" install \"" + buildPath + "\"");
}

int main()
{
    string exePath = GetExePath();
    string sourcePath = exePath + "\\src";
    string buildPath = exePath + "\\build";
    mkdir(buildPath.c_str());
    printf("now transpiling all .ts, .less and .jade files and copying the rest from:\n");
    printf((sourcePath+"\n").c_str());
    printf("To destination:\n");
    printf((buildPath+"\n").c_str());
    TranspileDirectory(sourcePath, buildPath, sourcePath);
    printf("Installing packages with npm if package.json file is present...\n");
    InstallPackages(buildPath);
    printf("Done!\n");
    //std:getchar();
    return 0;
}
