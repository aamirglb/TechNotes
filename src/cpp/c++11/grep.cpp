#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void showing_all_files(std::string path, std::string search)
{
      std::ofstream log_file;
      log_file.open("..\\grep_ex.log", std::ios::out);


    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(path))
        {
            std::cout << "checking " << entry << "...\n";
            int line_no = 0;
            std::string line;
            std::string filename;
            //  if( !entry.is_regular_file() ) {
            //      continue;
            //  }

             std::ifstream infile(entry.path());

             while(getline(infile, line))
             {

                ++line_no;
                auto pos = line.find(search);
                if(pos != std::string::npos)
                    {
                        log_file << entry.path() << ":" << line_no << ":" << line << std::endl;
                    }

             }
            // log_file << entry.path() << std::endl;

        }
        log_file.close();
}

int main() {
    showing_all_files(".", "main");
}