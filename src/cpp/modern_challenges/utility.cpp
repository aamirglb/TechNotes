#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Shlwapi.h>

inline std::string GetWorkingDirectory()
{
    HMODULE hModule = GetModuleHandle(nullptr);
    if(!hModule) { return ""; }

    char path[256];
    GetModuleFileName(hModule, path, sizeof(path));
    PathRemoveFileSpec(path);
    strcat_s(path, "\\");
    return std::string(path);
}

using FileList = std::vector<std::string>;

inline FileList GetFileList(
    const std::string& l_directory,
    const std::string& l_search = "*.*")
{
    FileList files;
    if(l_search.empty()) { return files; }

    std::string path = l_directory + l_search;
    WIN32_FIND_DATA data;
    HANDLE found = FindFirstFile(path.c_str(), &data);

    if(found == INVALID_HANDLE_VALUE) { return files; }

    do {
        if( !(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            files.emplace_back(data.cFileName);
        }
    } while(FindNextFile(found, &data));

    FindClose(found);
    return files;
}

#endif

int main()
{
#ifdef _WIN32
    auto path = GetWorkingDirectory();
    std::cout << path << std::endl;

    FileList files = GetFileList("D:\\SW\\");
    for(auto &file : files) {
        std::cout << file << std::endl;
    }
#endif
    std::cout << "The End.\n";
}