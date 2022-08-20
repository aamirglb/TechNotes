#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

boost::mutex global_stream_lock;

void print(std::string s) {
    global_stream_lock.lock();
    std::cout << s << std::endl;
    global_stream_lock.unlock();
}

void WorkerThread(boost::shared_ptr<boost::asio::io_service> srv,
    int counter) {
    print(std::to_string(counter));
    srv->run();
    print("end");
}

size_t fac(size_t n) {
    if(n <= 1) return n;
    boost::this_thread::sleep(boost::posix_time::milliseconds(500));
    return n * fac(n - 1);
}

void calculateFactorial(size_t n) {
    std::string s = "Calculating " + std::to_string(n) + "! factorial";
    print(s);
    size_t f = fac(n);
    s = std::to_string(n) + "! = " + std::to_string(f);
    print(s);
}

int main() {
    boost::shared_ptr<boost::asio::io_service> srv{
        new boost::asio::io_service
    };

    boost::shared_ptr<boost::asio::io_service::work> worker{
        new boost::asio::io_service::work{*srv}
    };

    print("The program will exit once all work is finished.");

    boost::thread_group threads;
    for(int i = 0; i <= 5; ++i) {
        threads.create_thread(boost::bind(&WorkerThread, srv, i));
    }

    srv->post(boost::bind(calculateFactorial, 5));
    srv->post(boost::bind(calculateFactorial, 6));
    srv->post(boost::bind(calculateFactorial, 8));
    srv->post(boost::bind(calculateFactorial, 11));
    srv->post(boost::bind(calculateFactorial, 15));

    worker.reset();
    threads.join_all();
}


