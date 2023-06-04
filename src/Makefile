.PHONY: all install uninstall clean dvi dist launch tests style valgrind

APP_NAME = 3DViewer

OS := $(shell uname -s)
ifeq ($(OS), Linux)
  OPEN = ./build/$(APP_NAME)
endif
ifeq ($(OS), Darwin)
	OPEN = open build/$(APP_NAME).app
endif

all: install launch

install:
	cmake -B build
	make -C build 3DViewer

uninstall:
	$(MAKE) clean
	rm -rf build

clean:
	rm -rf valgrind.txt 3DViewer.tar.gz

dvi:
	open README.md

dist:
	$(MAKE) install
	tar -czf $(APP_NAME).tar.gz --directory=build/ .

launch:
	$(OPEN)

tests: install
	make -C build tests
	./build/tests

style:
	clang-format -style=Google -n controller/*.cc controller/*.h model/*.cc model/*.h
	clang-format -style=Google -n view/*.cc view/*.h tests/*.cc tests/*.h
	clang-format -style=Google -n view/QtGifImage/gifimage/* view/QtGifImage/giflib/*