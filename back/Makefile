CC = g++
EXEC = src/main.cpp
INC = -I src/class
BUILD = build/server
LIBS  = -pthread

all: pre-build build

pre-build:
	mkdir -p build

build: pre-build
	$(CC) -std=c++11 $(EXEC) src/class/**/*.cpp  src/class/Game/**/*.cpp src/class/utils/**/*.cpp $(INC)/Log \
	$(INC)/utils/Response $(INC)/utils/Request $(INC)/utils/Socket $(INC)/utils/Thread $(INC)/utils/Json \
	$(INC)/Game/GameCore $(INC)/Game/Player $(INC)/Game/Card $(INC)/Game/CountDown -o $(BUILD) $(LIBS)

run:
	build/server 127.0.0.1 4444