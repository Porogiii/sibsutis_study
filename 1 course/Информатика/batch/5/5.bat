echo off


md txt
md png 
md doc


for %%i in (*.txt) do (
	move /-y "%5%\*.txt*" "%%"
  


)
for %%i in (*.png) do (
	move \*png\png



)
for %%i in (*.docx) do (
	move \*doc\doc



)
