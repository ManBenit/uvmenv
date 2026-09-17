@echo off
setlocal enabledelayedexpansion

:: Flag file to know when main process finishes
set "FLAG_FILE=%~1"

:: Get backspace natively
for /f %%a in ('"prompt $H&for %%b in (1) do rem"') do set "BS=%%a"

:: Create 18 returns variable (Exact length of "[|] Please wait...")
set "BACK=!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!!BS!"

:: Create temporary VBScript for no int sleeping
set "SLEEP_VBS=%temp%\sleep_100ms_%random%.vbs"
echo WScript.Sleep 100 > "%SLEEP_VBS%"

set "spinner_chars=|/-\"
set /a i=0

:: Print first time
<nul set /p "=[ ] Please wait..."

:loop
if exist "%FLAG_FILE%" goto :done

:: Calcul current index
set /a "idx=i %% 4"
set "c=!spinner_chars:~%idx%,1!"

:: Clear current line using returns and write new frame
<nul set /p "=!BACK![!c!] Please wait..."

:: Call VBScript to wait 0.x seconds
cscript //nologo "%SLEEP_VBS%"

set /a i+=1
goto loop

:done
:: Delete temp file
if exist "%SLEEP_VBS%" del /f /q "%SLEEP_VBS%"

:: Overwrite spinner with success
echo !BACK![OK] Process finished!          
exit /b 0
