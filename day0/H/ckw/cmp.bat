g++ mkdt.cpp -o mkdt -O2
:loop
mkdt.exe
std.exe < data.in > std.out
bf.exe < data.in > bf.out
fc std.out bf.out
if %errorlevel% ==0 goto loop
pause
