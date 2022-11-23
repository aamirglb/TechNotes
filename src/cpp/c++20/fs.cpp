#include "format"
#include <filesystem>
#include <iostream>
// #include <unordered_map>
#include <map>
#include <vector>
#include <algorithm>
#include <source_location>

namespace fs = std::filesystem;

void logMessage(std::string_view msg,
    const std::source_location& loc = std::source_location::current())
{
    fmt::print("{}({}): {}: {}\n", loc.file_name(), loc.line(),
        loc.function_name(), msg);
}

void printDirectoryStructure(const fs::path& p)
{
    int total_files {};
    // std::unordered_map<std::string, int> file_count;
    std::map<std::string, int> file_count;

    if(!exists(p)) return;

    fs::recursive_directory_iterator begin{ p };
    fs::recursive_directory_iterator end {};

    for(auto itr {begin}; itr != end; ++itr) {
        const std::string spacer(itr.depth() * 2, ' ');

        auto& entry { *itr };

        if(fs::is_regular_file(entry)) {
            ++total_files;
            // get file extension
            std::string ext { entry.path().extension().string() };
            ++file_count[ext];

            fmt::print("{} = > {}File: {} ({} bytes)\n", total_files, spacer,
                entry.path().string(),
                fs::file_size(entry));
        } else if(fs::is_directory(entry)) {
            fmt::print("{}Dir: {}\n", spacer, entry.path().string());
        }
    }

    // fmt::print("\n\nTotal Files: {}\n", total_files);
    // for(const auto& [key, value] : file_count) {
    //     fmt::print("{:8} -> {}\n", key, value);
    // }

    std::vector<std::pair<std::string, int>> vec_file_count;
    for(auto itr = file_count.begin(); itr != file_count.end(); ++itr) {
        vec_file_count.push_back(*itr);
    }

    std::sort(vec_file_count.begin(), vec_file_count.end(),
        [=](const auto& p1, const auto& p2) {
            return p2.second < p1.second;
        });

    for(const auto& [key, value] : vec_file_count) {
        fmt::print("{:8} -> {}\n", key, value);
    }

    logMessage("printDirectoryStructure() finished executing.");
}


int main()
{
    logMessage("Starting main()");

    fs::path p{ R"(C:\Foo\Bar)" };
    for(const auto& component : p) {
        // fmt::print("{}\n", component);
        std::cout << component << std::endl;
    }

    fs::path p2 { R"(C:\Foo\Bar\file.txt)" };
    // fmt::print("{}\n", p2.root_name());
    std::cout << "root_name: " << p2.root_name() << std::endl;
    std::cout << "filename: " << p2.filename() << std::endl;
    std::cout << "stem: " << p2.stem() << std::endl;
    std::cout << "extension: " << p2.extension() << std::endl;

    fmt::print("\n\n");

    fs::path p3 { R"(D:/llvm6.bat)" };
    fs::directory_entry de { p3 };

    if(de.exists() && de.is_regular_file() ) {
        fmt::print("File size: {}\n", de.file_size());
        // std::cout << "Last modified time: " << de.last_write_time() << std::endl;
    }

    fs::path p4 {R"(D:/Books)"};
    printDirectoryStructure(p4);

    // const std::source_location loc = std::source_location::current();
    // fmt::print("Filename: {}\n", loc.file_name());
    // fmt::print("Line No:  {}\n", loc.line());
    // fmt::print("Column:   {}\n", loc.column());
    // fmt::print("Function: {}\n", loc.function_name());
}