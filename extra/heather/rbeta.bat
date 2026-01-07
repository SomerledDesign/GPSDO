@echo off
if %1i == i goto usage
call setset c14
nmake /f makefile.w32 /A
if errorlevel 1 goto bail 
touch heather.iss
if errorlevel 1 goto bail 
nmake /f makefile.w32 output/setup.exe
if errorlevel 1 goto bail 
cd output
pause
ren setup.exe beta.exe
call setset c16
call sign beta.exe %1
if errorlevel 1 goto bail 
call ke5fx.bat beta.exe heather
cd ..
call ke5fx.bat readme.txt heather
call ke5fx.bat readme.htm heather
goto bail
:usage
echo Usage: rbeta password
:bail

