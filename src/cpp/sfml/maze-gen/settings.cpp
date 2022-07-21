#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "settings.hpp"

//! function to trim leading and trailing spaces in-place
void trim(std::string& str)
{
    // trim leading spaces
    std::string delims{" \t"};

    std::string::size_type startIdx = str.find_first_not_of(delims);

    // if there are leading spaces, chop them off
    if( startIdx != std::string::npos )
        str = str.substr( startIdx );

    // look for trailing spaces
    std::string::size_type endIdx = str.find_first_of (delims);

    // if there are trailing spaces, chop them off
    if( endIdx != std::string::npos )
        str = str.substr(0, endIdx);
}

//! Class Constructor
//! 1) Check if file extension is .ini
Settings::Settings(const std::string& filename) :
        fname(filename)
{
    // Check for file extension
    std::string::size_type dotIdx{ fname.find_last_of(".") };
    std::string extension{ fname.substr(dotIdx) };

    // If file is an .ini file
    if( extension == ".ini")
    {
        // Open the settings file
        std::ifstream settingsFile{fname};

        // If file is opened successfully
        if( settingsFile )
        {
            int lineNum{0};
            std::string line{}, key{}, value{};
            std::string delims{" \t"};

            // Read line one by one and populate the map
            while( std::getline(settingsFile, line) )
            {
                ++lineNum;
                //std::cout << std::setw(3) << lineNum << ": " << line << std::endl;

                // Ignore empty lines
                if( line.empty() )
                    continue;

                // trim leading spaces
                //trim(line);
                std::string::size_type startpos = line.find_first_not_of(delims);
                if( startpos != std::string::npos )
                    line = line.substr( startpos );

                // Ignore comment line or section name line
                if( line[0] == '#' || line[0] == '[')
                    continue;

                std::string::size_type equalIdx{ line.find("=") };
                if( equalIdx != std::string::npos )
                {
                    key = line.substr(0, equalIdx);
                    value = line.substr(equalIdx + 1);

                    trim(key);
                    trim(value);

                    // Insert <key, value> pair in the map
                    settings[key] = value;

                    //std::cout << "{" << key << ", " << value << "}" << std::endl;
                }
                else
                {
                    //! TODO
                    //! Ignore invalid entries or through an exception
                    // Ignore invalid entries
                    std::cout << "Invalid entry at line " << lineNum << std::endl;
                }
            } // End of while
        } // End of enable to open
        else
        {
            //std::cout << "Enable to open " << fname << std::endl;
            std::string msg = R"(Enable to open ')" + fname + "'\n";
            throw SettingsException{msg};
        }
    }
    else
    {
        //std::cout << "File should be an .ini file\n";
        throw SettingsException{"File should be an '.ini' file\n"};
    }
}

//! Given a key, return the corresponding value if found, else return empty string
std::string Settings::getValue(const std::string& key, std::string default_value) const
{
    std::string retValue = default_value;
    auto pos{ settings.find(key) };
    if( pos != settings.end() )
            retValue = pos->second;
    return retValue;
}

//! Get all the files from ini file
std::list<std::string> Settings::getAllKeys() const
{
    std::list<std::string> keys;
    std::map<std::string, std::string>::const_iterator itr = settings.cbegin();
    while( itr != settings.cend() )
    {
            keys.push_back(itr->first);
            ++itr;
    }
    return keys;
}

#ifdef _TEST_CODE_
int main()
{
    try
    {
        std::unique_ptr<Settings> appSettings(new Settings("settings.txt"));

        std::list<std::string> allKeys(appSettings->getAllKeys());
        for(auto ele : allKeys)
        {
                std::cout << "[" << ele << " = " << appSettings->getValue(ele) <<"]" << std::endl;
        }
    }
    catch(const Settings::SettingsException& ex)
    {
        std::cerr << ex.what();
    }
    catch(...)
    {
        std::cerr << "Exception Occured...\n";
    }
    std::cout << "Continue processing...\n";
}
#endif
