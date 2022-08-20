g++ -Wall -Wextra -Wpedantic -ID:\SW\Boost_Lib\boost_1_66_0 -std=c++17 %1  ^
    -LD:\SW\Boost_Lib\boost_1_66_0\stage\lib ^
    -lws2_32 ^
    -lwsock32 ^
    -lboost_thread-mgw112-mt-d-x64-1_66 ^
    -lboost_chrono-mgw112-mt-d-x64-1_66 ^
    -lboost_system-mgw112-mt-d-x64-1_66
@REM a.exe