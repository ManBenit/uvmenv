@echo off
setlocal EnableDelayedExpansion

:: Get PID from the first argument
set "PID=%~1"

if "%PID%"=="" (
    echo Usage: %0 ^<PID^>
    exit /b 1
)

:: Define spinner characters and initial counter
set "spinner=|/-\"
set "i=0"

:: Hack to generate a Carriage Return (CR) character to overwrite the current line
for /f %%A in ('copy /Z "%~f0" nul') do set "CR=%%A"

:: Create a temporary VBScript for a 100ms sleep. 
:: (Using this instead of PowerShell prevents heavy CPU usage and startup lag)
set "sleepVBS=%temp%\sleep_100ms.vbs"
echo WScript.Sleep 100 > "%sleepVBS%"

:loop
:: Check if process is alive (equivalent to 'kill -0')
tasklist /FI "PID eq %PID%" /NH 2>nul | find "%PID%" >nul
if errorlevel 1 goto endloop

:: Extract a different character each time
set /a "idx=i %% 4"
for %%j in (!idx!) do set "c=!spinner:~%%j,1!"

:: Print the spinner using the CR character to return to the start of the line
<nul set /p ="!CR![!c!] Please wait..."

:: Sleep 0.1 seconds
cscript //nologo "%sleepVBS%"

:: Increment counter and loop
set /a i+=1
goto loop

:endloop
:: Clean line and finish (Using √ as standard CMD doesn't natively render the Unicode \u2713 well)
echo !CR![√] Process finished!          

:: Cleanup temp file
del "%sleepVBS%" 2>nul

exit /b 0
