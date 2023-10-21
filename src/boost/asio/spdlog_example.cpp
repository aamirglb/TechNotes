// #define SPDLOG_FMT_EXTERNAL
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

void multi_sink_example()
{
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");

    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/multisink.txt", true);
    file_sink->set_level(spdlog::level::trace);

    spdlog::logger logger("multi_sink", {console_sink, file_sink});
    logger.set_level(spdlog::level::debug);
    logger.warn("this should appear in both console and file");
    logger.info("this message should not appear in the console, only in the file");
}

int main()
{
    // change log pattern
    spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    spdlog::info("Welcome to spdlog!");
    spdlog::error("Some error message with arg: {}", 1);

    spdlog::warn("Easy padding in numbers like {:08d}", 12);
    spdlog::critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
    spdlog::info("Support for floats {:03.2f}", 1.23456);
    spdlog::info("Positional args are {1} {0}..", "too", "supported");
    spdlog::info("{:<30}", "left aligned");

    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    spdlog::debug("This message should be displayed..");

    // // change log pattern
    // spdlog::set_pattern("[%H:%M:%S %z] [%n] [%^---%L---%$] [thread %t] %v");

    // Compile time log levels
    // define SPDLOG_ACTIVE_LEVEL to desired level
    SPDLOG_TRACE("Some trace message with param {}", 42);
    SPDLOG_DEBUG("Some debug message");

    multi_sink_example();
}

/*
Please define _WIN32_WINNT or _WIN32_WINDOWS appropriately. For example:
  - add -D_WIN32_WINNT=0x0601 to the compiler command line; or
  - add _WIN32_WINNT=0x0601 to your project's Preprocessor Definitions.
  Assuming _WIN32_WINNT=0x0601 (i.e. Windows 7 target).
*/