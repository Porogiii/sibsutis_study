echo off

type nul > numbers.txt

set /A min = 0 
set /A max = 10

for /l %%i in (1,1,10) do call :sort

sort /r numbers.txt /o sort_numbers.txt

:sort
set /a numbers=%random%%%max+min
echo %numbers% >> numbers.txt

exit /b

