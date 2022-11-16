g++ -Wall -Wextra -Wpedantic -I.\fmt-9.0.0\include -std=c++2a %1

if %ERRORLEVEL% NEQ 1 a.exe %2
