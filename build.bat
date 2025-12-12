@echo off
echo ===============================
echo      BUILDING SHAURYA
echo ===============================

if not exist bin mkdir bin

echo [1/2] Compiling Mock Exchange...
g++ MockExchange.cpp -o bin/exo -lws2_32 -std=c++11

echo [2/2] Compiling Shaurya Engine...
g++ src/Main.cpp src/NetworkClient.cpp src/FixParser.cpp -o bin/Shaurya -lws2_32 -std=c++11 -O3

echo.
echo Build Complete.
pause