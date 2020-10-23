@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path=R:\Handmade\misc;%path%
mkdir ..\..\build
pushd ..\..\build
cl -Zi r:\Handmade\code\win32_handmade.cpp user32.lib gdi32.lib