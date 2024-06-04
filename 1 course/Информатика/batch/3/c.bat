echo off

set a=0
set b=1
set /a n = 8
set /a c = n/2


for /l %%i in (%c%,-1,1) do (
	set /a a = a + b
	set /a b = b + a
	
)
echo %a%
pause
