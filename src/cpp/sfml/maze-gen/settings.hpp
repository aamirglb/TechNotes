#pragma once

#include <list>
#include <map>
#include <string>
#include <stdexcept>

//! Settings class
//! Read key=value pair from an .ini file and store it in a map
//!
//! Public Interface:
//! Settings(@param filename) :
//! 	Read all key=value pairs from @filename
//!
//! string getValue(@param key) :
//! 	Given a key, return corresponding value if key is found in ini file
//!     else return the second parameter as the value
//!
//! list<string> getAllKeys() :
//! 	Get all the keys from the ini file
//!
class Settings
{
public:

    //! Exception class for Settings
    class SettingsException : public std::logic_error
    {
    public:
        SettingsException(std::string const& what_arg) : logic_error{what_arg} {}
    };

    //! Constructor
    Settings(const std::string& filename);

    //! Given a key, return the corresponding value if found, else return default value
    //! specified in the second parameter
    std::string getValue(const std::string& key, std::string default_value = "") const;

    //! Get all the files from ini file
    std::list<std::string> getAllKeys() const;

    ~Settings() = default;

private:
    const std::string fname;  //! Name of the settings file
    std::map<std::string, std::string> settings;
};
