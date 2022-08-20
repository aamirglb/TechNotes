#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <string>

boost::asio::io_service srv;
int a = 0;
bool stop {false};

class Worker {
public:
    Worker(std::string id_) : id{id_} {}
    void operator()() {
        while(!stop) {
            std::cout << id << ": " << ++a << ".\n";
            boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
        }
        std::cout << "running srv.run() now.\n";
        srv.run();
        std::cout << "end." << std::endl;
    }
    std::string id;
};

void WorkerThread(std::string id) {
    while(!stop) {
        std::cout << id << ": " << ++a << ".\n";
        boost::this_thread::sleep_for(boost::chrono::milliseconds{500});
    }
    srv.run();
    std::cout << "end." << std::endl;
}

int main() {
    boost::shared_ptr<boost::asio::io_service::work> worker{
        new boost::asio::io_service::work(srv)
    };

    std::cout << "Press ENTER to exit!" << std::endl;

    boost::thread_group threads;
    for(int i = 0; i < 5; ++i) {
        std::string s = "thread-" + std::to_string(i+1);
        Worker w{s};
        threads.create_thread(w);
    }
    std::cin.get();
    stop = true;
    srv.stop();
    threads.join_all();
}