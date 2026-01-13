@echo off
echo ------------------------------------------------
echo           Gimbal Control Simulation
echo ------------------------------------------------

REM Change directory to the script's location
cd /d "%~dp0"

echo [INFO] Cleaning up old build...
if exist "main.exe" del "main.exe"

echo [INFO] Compiling C Controller...
echo [INFO] Source Path: Src/
echo [INFO] Header Path: Inc/
echo [INFO] Dynamics Path: Src/automated_dynamics/

echo Started Compilation

REM Updated compile command:
REM Includes main controller files and all generated dynamics in subfolders M, C, and G
gcc Src\main.c ^
    Src\backstepping_2.c ^
    Src\communication_2.c ^
    Src\automated_dynamics\model.c ^
    Src\automated_dynamics\params.c ^
    Src\automated_dynamics\M\*.c ^
    Src\automated_dynamics\C\*.c ^
    Src\automated_dynamics\G\*.c ^
    -I Inc -I Src\automated_dynamics -o main.exe -O2

REM Check for errors
if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Compilation Failed!
    pause
    exit /b %errorlevel%
)

echo [INFO] Compilation Successful. main.exe is ready.
pause