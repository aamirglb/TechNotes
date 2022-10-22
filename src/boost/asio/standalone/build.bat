g++ -Wall -Wextra -Wpedantic -ID:\SW\asio-1.24.0\include -std=c++2a %1 -lws2_32 -lwsock32

if %ERRORLEVEL% NEQ 1 a.exe %2 %3


@REM g++ -Wall -Wextra -Wpedantic -ID:\SW\Boost_Lib\boost_1_66_0 -std=c++17 %1  ^
@REM     -LD:\SW\Boost_Lib\boost_1_66_0\stage\lib ^
@REM     -lws2_32 ^
@REM     -lwsock32 ^
@REM     -lboost_thread-mgw112-mt-d-x64-1_66 ^
@REM     -lboost_chrono-mgw112-mt-d-x64-1_66 ^
@REM     -lboost_system-mgw112-mt-d-x64-1_66
@REM a.exe