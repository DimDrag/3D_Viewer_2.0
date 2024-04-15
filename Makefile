CC = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
CGFLAGS = -fprofile-arcs -ftest-coverage --coverage -O0
TARGET = 3D_Viewer
SRC = ./3D_Viewer/model
TEST_DIR = ./tests
TEST = ./tests/test
TEST_FLAGS = -lgtest -lpthread
MEMORY_CHECKER = valgrind -s --leak-check=full --show-leak-kinds=all
REPORT_DIR = ./report

all: install

build:
	mkdir build
	cd build && qmake ../$(TARGET)/$(TARGET).pro && make

install: build .desktop_file
	mkdir $(HOME)/.3d_viewer

.desktop_file:
	printf "[Desktop Entry]\n \
	Encoding=UTF-8\n \
	Version=1.0\n \
	Type=Application\n \
	Terminal=false\n \
	Exec=$(PWD)/build/3D_Viewer\n \
	Name=3D Viewer\n \
	Icon=$(PWD)/3D_Viewer/logo.png\n" > $(HOME)/.local/share/applications/3d_viewer.desktop

uninstall:
	rm -rf $(HOME)/.local/share/applications/3d_viewer.desktop
	rm -rf $(HOME)/.3d_viewer/setting.dat

dvi: $(TARGET).pdf
	open $(TARGET).pdf
	doxygen Doxyfile
	open ./html/index.html

$(TARGET).pdf: info/$(TARGET).tex
	texi2pdf -q -c info/$(TARGET).tex -o $(TARGET).pdf

dist:
	tar -czf $(TARGET).tar.gz $(TARGET)

test:
	$(CC) $(CFLAGS) $(TEST_DIR)/*.cc $(SRC)/parser.cc $(SRC)/figure.cc $(TEST_FLAGS) -o $(TEST)
	$(TEST)

gcov_report: clean
	$(CC) $(CFLAGS) $(CGFLAGS) $(TEST_DIR)/*.cc $(SRC)/parser.cc $(SRC)/figure.cc $(TEST_FLAGS) -o $(TEST)
	$(TEST)
	rm -rf ./*tests.gc* ./*main.gc*
	lcov -d . -q -c -o $(REPORT_DIR)/report.info --no-external
	genhtml -o $(REPORT_DIR) $(REPORT_DIR)/report.info
	rm -rf ./*.gc*
	open ./$(REPORT_DIR)/index.html


style_check:
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -n -style=Google

style_fix:
	@find . \( -name '*.h' -o -name '*.cc' \) -print0 | xargs -0 clang-format -i -style=Google

cppcheck:
	cppcheck --std=c++17 --language=c++ --enable=warning \
	$(TARGET)/main.cc $(TARGET)/model/* $(TARGET)/view/* $(TARGET)/controller/*

cpplint:
	cpplint --recursive --filter=-legal/copyright,-build/include_subdir,-build/header_guard \
	$(TARGET)/main.cc $(TARGET)/model/* $(TARGET)/view/* $(TARGET)/controller/*

memory_leaks_check: test
	CK_FORK=no $(MEMORY_CHECKER) $(TEST)

clean:
	rm -rf build*
	rm -rf report/*
	rm -rf *.pdf
	rm -rf *.gz
	rm -rf tests/test
	rm -rf html latex
