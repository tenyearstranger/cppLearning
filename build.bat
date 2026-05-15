@echo off
REM C++ 编译和运行脚本 (Windows)

setlocal enabledelayedexpansion

set "COMPILER=g++"
set "STD_FLAG=-std=c++17"
set "WARNINGS=-Wall -Wextra"
set "OUTPUT_DIR=build"

if not exist "%OUTPUT_DIR%" mkdir "%OUTPUT_DIR%"

if "%1%"=="compile" (
    if "%2%"=="" (
        echo 用法: %0 compile ^<file.cpp^>
        goto end
    )
    set "FILE=%2%"
    for %%F in (!FILE!) do set "NAME=%%~nF"
    set "NAME=!NAME:.cpp=!"
    set "OUTPUT=%OUTPUT_DIR%\!NAME!"
    
    echo 编译: !FILE!
    %COMPILER% %STD_FLAG% %WARNINGS% -o "!OUTPUT!" "!FILE!"
    if !errorlevel! equ 0 (
        echo ^✓ 编译成功: !OUTPUT!
    ) else (
        echo ^✗ 编译失败
    )
    goto end
)

if "%1%"=="run" (
    if "%2%"=="" (
        echo 用法: %0 run ^<program_name^>
        goto end
    )
    set "PROGRAM=%OUTPUT_DIR%\%2%.exe"
    if exist "!PROGRAM!" (
        echo.
        echo ========== 运行: %2% ==========
        call "!PROGRAM!"
        echo ==================================
        echo.
    ) else (
        echo ^✗ 文件不存在: !PROGRAM!
    )
    goto end
)

if "%1%"=="all" (
    echo 编译所有 C++ 文件...
    for %%F in (*.cpp) do (
        set "FILE=%%F"
        for %%G in (!FILE!) do set "NAME=%%~nG"
        set "NAME=!NAME:.cpp=!"
        set "OUTPUT=%OUTPUT_DIR%\!NAME!"
        
        echo 编译: !FILE!
        %COMPILER% %STD_FLAG% %WARNINGS% -o "!OUTPUT!" "!FILE!"
        if !errorlevel! equ 0 (
            echo ^✓ 编译成功
        ) else (
            echo ^✗ 编译失败
        )
    )
    echo 所有文件编译完成！
    goto end
)

if "%1%"=="clean" (
    echo 清理编译文件...
    if exist "%OUTPUT_DIR%" rmdir /s /q "%OUTPUT_DIR%"
    echo 完成！
    goto end
)

echo 用法:
echo   %0 compile ^<file.cpp^>  - 编译单个文件
echo   %0 run ^<program_name^>  - 运行编译后的程序
echo   %0 all                 - 编译所有文件
echo   %0 clean               - 清理编译文件

:end
endlocal
