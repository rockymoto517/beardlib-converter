CONFIG += debug
HEADERS += gui.h
SOURCES = gui.cpp \
	  main.cpp
TARGET = guiprogram

!exists( main.cpp ) {
	error( "No main.cpp file found" )
}