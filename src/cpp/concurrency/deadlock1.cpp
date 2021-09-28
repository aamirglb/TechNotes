#include <iostream>
#include <mutex>
#include <future>
#include <string>
#include <thread>

class Database {
private:
    //std::mutex dbMutex;
    std::recursive_mutex dbMutex;

public:
    void createTable() {
        std::lock_guard<std::recursive_mutex> lg(dbMutex);
        std::cout << "Database table created.\n";
    }

    void insertData() {
        std::lock_guard<std::recursive_mutex> lg(dbMutex);
        std::cout << "Database inserting data.\n";
    }

    void createTableAndInsertData() {
        std::lock_guard<std::recursive_mutex> lg(dbMutex);
        std::cout << "create table and insert data.\n";
        createTable();
        insertData();
    }

};

int main() {
    Database db;
    db.createTableAndInsertData();
    std::cout << "Done!!\n";
}