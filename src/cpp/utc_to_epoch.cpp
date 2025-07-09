#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

std::time_t rmc_to_epoch(const std::string& rmc_time, const std::string& rmc_date) {
    // Parse the time (hhmmss.sss) and date (ddmmyy) from the RMC message
    int hour = std::stoi(rmc_time.substr(0, 2));
    int minute = std::stoi(rmc_time.substr(2, 2));
    int second = std::stoi(rmc_time.substr(4, 2));

    int day = std::stoi(rmc_date.substr(0, 2));
    int month = std::stoi(rmc_date.substr(2, 2));
    int year = std::stoi(rmc_date.substr(4, 2));
    
    // long utcTimeOfDay = std::stol( rmc_time );

	// long hours = utcTimeOfDay / 10000;
	// long minutes = ( utcTimeOfDay % 10000 ) / 100;
	// long seconds = utcTimeOfDay % 100;


    // Adjust for 21st century (assuming years 00-69 are in 21st century, 70-99 are in 20th century)
    year += (year < 70) ? 2000 : 1900;

    // Create a tm structure to represent the time
    std::tm timeinfo = {};
    timeinfo.tm_year = year - 1900; // years since 1900
    timeinfo.tm_mon = month - 1;    // months since January (0-11)
    timeinfo.tm_mday = day;         // day of the month (1-31)
    timeinfo.tm_hour = hour;
    timeinfo.tm_min = minute;
    timeinfo.tm_sec = second;

    // Convert the tm structure to time_t (seconds since epoch)
    std::time_t epoch_time = std::mktime(&timeinfo);

    return epoch_time;
}

int main() {
    // Example RMC time and date (from the NMEA message)
    std::string rmc_time = "110520"; // hhmmss.sss (12:35:19)
    std::string rmc_date = "100924"; // ddmmyy (23 March 1994)

    std::time_t seconds_since_epoch = rmc_to_epoch(rmc_time, rmc_date);

    // Output the result
    std::cout << "Seconds since epoch: " << seconds_since_epoch << std::endl;
    std::cout << "UTC: " << std::put_time(std::gmtime(&seconds_since_epoch), "%Y-%m-%d %H:%M:%S") << std::endl;

    return 0;
}