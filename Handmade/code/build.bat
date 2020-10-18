@echo off
mkdir ..\..\build
pushd ..\..\build
cl -Zi r:\Handmade\code\win32_handmade.cpp
popd
