g++ -Wall -Wextra -Wpedantic -I./fmt/include -std=c++17  %1 -L./fmt/lib -lfmt
@REM g++ -Wall -Wextra -Wpedantic -I./fmt-9.0.0/include -DFMT_HEADER_ONLY -std=c++17  %1

if %ERRORLEVEL% NEQ 1 a.exe %2 %3