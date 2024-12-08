CFLAGS = -Wall -Werror -Wextra
CXXFLAGS = -std=c++17
TARGET = CalcSmart
FILES = model/calc_model.cpp model/loan_model.cpp model/deposit_model.cpp
OBJECTS = *.o *.out *.a
COV_FILES = *.gcda *.gcno report gcov_report.* gcov_report *.info *.dSYM
VIEW_DIRS = view/build view/CalcSmart.pro.user
BUILD_DIRS = ../build ../dist view/CalcSmart.app view/*.o view/Makefile ../dist

.PHONY: all tests gcov_report style check_style clean install uninstall dist dvi calc_model.a build rebuild run_app

all: tests

install:
	@echo "Start installation"
	@mkdir -p ../build
	@echo "Running qmake and make in the view directory"
	@cd ./view && qmake && make
#	@mv CalcSmart.app ../build/$(TARGET).app
	@cp -R ../build/$(TARGET).app ~/Desktop/$(TARGET).app
	@echo "Cleaning up..."
	@make clean -C ./view
	@echo "┏=========================================┓"
	@echo "┃    The installation was successful.     ┃"
	@echo "┃     The project is located in the       ┃"
	@echo "┃    build folder and on the desktop.     ┃"
	@echo "┗=========================================┛"
	@make run_app

run_app:
	@echo "Opening $(TARGET).app"
	open ../build/$(TARGET).app

uninstall:
	@rm -rf ~/Desktop/$(TARGET).app ../build
	@echo "Uninstall completed successfully"

calc_model.a: build
	ar rc calc_model.a *.o
	ranlib calc_model.a
	rm *.o

build: $(FILES)
	@echo "Building object files from source files..."
	g++ -c $(CFLAGS) $(CXXFLAGS) $(FILES)

clean:
	@echo "Cleaning up..."
	rm -rf $(OBJECTS) $(COV_FILES) unit_test report
	rm -rf $(VIEW_DIRS) $(BUILD_DIRS)
	@echo "Cleanup completed."

rebuild:
	@echo "Rebuilding targets..."
	make clean
	make build

style:
	@echo "Applying code style with clang-format..."
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -i *.cpp model/*.cpp model/*.h controller/*.cpp controller/*.h view/*.cpp view/*.h tests/*.cpp
	rm .clang-format
	@echo "Code style applied."

check_style:
	@echo "Checking code style with clang-format..."
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -style=Google -n *.cpp model/*.cpp model/*.h controller/*.cpp controller/*.h view/*.cpp view/*.h tests/*.cpp
	rm .clang-format
	@echo "Code style checked."

tests: clean calc_model.a tests/calc_tests.cpp
	@echo "Running unit tests..."
	g++ -lgtest $(CXXFLAGS) --coverage calc_model.a ./tests/calc_tests.cpp -o unit_test
	./unit_test

gcov_report: clean
	@echo "Generating code coverage report..."
	g++ --coverage tests/calc_tests.cpp $(FILES) -o gcov_report -lgtest $(CXXFLAGS)
	./gcov_report
	lcov -t "unit_test" -o test.info -c -d . --ignore-errors inconsistent,inconsistent,inconsistent,...
	genhtml -o report test.info --ignore-errors inconsistent
	open ./report/index.html

dvi:
	@open ../README_RUS.md

dist:
	@echo "Creating distribution package..."
	@mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp ../README_RUS.md ../dist && cp ../README.md ../dist
	@cd ../dist && tar cvzf $(TARGET)_v2.0.tgz *
	@cd ../dist && rm -rf $(TARGET).app README.md README_RUS.md
	@echo "The build was successfully archived"