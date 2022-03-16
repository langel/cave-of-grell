# compiler flags
FLAGS := -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lm
EXEC := cave-of-grell

# detect windows
ifeq ($(OS),Windows_NT)
	FLAGS := -I"C:\libsdl\include" -L"C:\libsdl\lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
	EXEC := cave-of-grell.exe
endif

build:
	gcc -Wall \
	-std=c99 \
	./main.c \
	$(FLAGS) \
	-o $(EXEC)
