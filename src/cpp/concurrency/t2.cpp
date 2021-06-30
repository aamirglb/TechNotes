#include <iostream>
#include <string>
#include <mutex>
#include <functional>

class some_data {
    int a;
    std::string b;
public:
    void do_something();
};

class data_wrapper {
private:
    some_data data;
    std::mutex m;

public:
    template<typename Function>
    void process_data(Function fun) {
        std::lock_guard<std::mutex> l(m);
        func(data);
    }
};

some_data* unprotected;
void malicious_function(some_data& protected_data) {
    unprotected = &protected_data;
}

data_wrapper x;
void foo() {
    x.process_data(malicious_function);
    unprotected->do_something();
}

void main() {
    foo();
}

/*
/* Try to set baud rate */
	struct termios uart_config;
	int termios_state;

	/* Initialize the uart config */
	if ((termios_state = tcgetattr(_uart_fd, &uart_config)) < 0) {
		PX4_ERR("ERR GET CONF %s: %d\n", uart_name, termios_state);
		::close(_uart_fd);
		return -1;
	}
*/

