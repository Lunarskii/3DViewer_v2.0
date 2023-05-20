VALGRIND_FLAGS				= --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

SRC_GIFLIB_DIR				= view/QtGifImage/giflib/
OBJ_GIFLIB_DIR				= ../obj/GIFLIB/
GIF_LIBRARY					= giflib.a
BUILD_FOLDERS				:= $(shell mkdir -p $(OBJ_GIFLIB_DIR))
SRC_GIFLIB					:= $(wildcard $(SRC_GIFLIB_DIR)*.c)
OBJ_GIFLIB					:= $(patsubst $(SRC_GIFLIB_DIR)%.c,$(OBJ_GIFLIB_DIR)%.o,$(SRC_GIFLIB))


APP_NAME					= 3DViewer

all: install launch

install: $(GIF_LIBRARY)
	cmake -B build
	make -C build untitled
	cp build/untitled $(APP_NAME)

uninstall: clean
	rm -rf build
	rm -rf $(APP_NAME)

clean:
	rm -rf ../obj/
	rm -rf *.a
	rm -rf valgrind.txt

dvi:
	open README.md

dist: install
	tar -czf $(APP_NAME).tar.gz --directory=build/ .

launch:
	./$(APP_NAME)

tests: install
	make -C build tests
	./build/tests

$(GIF_LIBRARY): $(OBJ_GIFLIB)
	ar rc $(GIF_LIBRARY) $(OBJ_GIFLIB)
	ranlib $(GIF_LIBRARY)
	mv $(GIF_LIBRARY) lib$(GIF_LIBRARY)

$(OBJ_GIFLIB_DIR)%.o: $(SRC_GIFLIB_DIR)%.c
	gcc -c $< -o $@

clang:
	clang-format --style=google -i $(SRC_PROJECT_DIR)*
	clang-format --style=google -i $(SRC_TEST_DIR)*

.PHONY: all install uninstall clean dvi dist launch tests clang valgrind