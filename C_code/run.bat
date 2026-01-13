@echo off
REM 1. CLEANUP: Delete the old file
if exist main.exe del main.exe

REM 2. COMPILE:
REM Added "Src\dynamics_c\*.c" so gcc compiles the split files too
echo Compiling...
gcc Src\*.c Src\dynamics_c\*.c -I Inc -o main.exe

REM 3. CHECK STATUS
if not exist main.exe (
    echo.
    echo [ERROR] Compilation Failed!
    pause
    exit /b
)

REM 4. RUN
echo.
echo [SUCCESS] Running code...
echo ------------------------------
main.exe
echo ------------------------------
pause