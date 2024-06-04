echo off

type nul > dir.txt

dir /b c:\ > dir.txt
call dir.txt
pause

type nul > sort_dir.txt
sort dir.txt /output sort_dir.txt
call sort_dir.txt