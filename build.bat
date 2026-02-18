@echo off
echo ==========================================
echo   BUILDING SHAURYA (LLVM + LLD LINKER)
echo ==========================================

:: Set Compiler
set CXX=clang++

:: Flags
set CXXFLAGS=-O3 -march=native -std=c++20 -fuse-ld=lld -Wno-deprecated-declarations -Wno-nonportable-include-path

:: Include Paths (Added common MSYS2 Eigen paths so Clang can find it!)
set INCLUDES=-I./include -I./frugally-deep/include -I./json/include -I./FunctionalPlus/include -IC:/msys64/mingw64/include/eigen3 -IC:/msys64/ucrt64/include/eigen3 -I./eigen

:: Specific Source Files (Only compiling what we actually need)
set SOURCES=src/Main.cpp src/FixParser.cpp src/NetworkClient.cpp

echo Compiling with LLVM Backend...
%CXX% %CXXFLAGS% %INCLUDES% %SOURCES% -o bin/Shaurya.exe -lws2_32

if %errorlevel% neq 0 (
    echo.
    echo [ERROR] Build Failed! Check the Eigen path.
    pause
    exit /b %errorlevel%
)

echo Build Successful! Shaurya is ready.
pause