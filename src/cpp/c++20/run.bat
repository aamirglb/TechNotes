REM clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include\ .\employee.cpp .\employeetest.cpp
REM clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include\ .\employee.cpp .\database.cpp .\databasetest.cpp
REM clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include\ .\employee.cpp .\database.cpp .\userinterface.cpp
REM clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include -std=c++20 -fexperimental-library view.cpp
REM clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include -std=c++20 -fexperimental-library pointer.cpp
REM clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include -std=c++20 .\spreedsheetcell.cpp .\spreedsheetmain.cpp
clang++.exe -Wall -Wextra -pedantic -I.\fmt-9.0.0\include -std=c++20 .\gridmain.cpp
if %ERRORLEVEL% NEQ 1 a.exe %2

