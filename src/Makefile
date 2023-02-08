BD = ../build/
APP = $(BD)3DViewer_v2.app

all: install

build: copy_pro
	cd $(BD); qmake 3DViewer_v2.pro
	make -C $(BD)

copy_pro: 
	cp 3DViewer_v2/3DViewer_v2.pro $(BD)
	cp 3DViewer_v2/* $(BD)

install: build
	mkdir $(HOME)/Desktop/3DViewer_v2/
	cp -rf $(APP) $(HOME)/Desktop/3DViewer_v2/
	make clean

uninstall:
	rm -rf $(HOME)/Desktop/3DViewer_v2/

dvi: 
	open documentation.html

dist: install
	@rm -rf $(HOME)/Desktop/Archive_3DViewer_v2.0.tar.gz
	cp -r $(HOME)/Desktop/3DViewer_v2/3DViewer_v2.app .
	@tar -czvf Archive_3DViewer_v2.0.tar.gz documentation.html ./objectives 3DViewer_v2.app
	mv Archive_3DViewer_v2.0.tar.gz $(HOME)/Desktop/

tests: clean
	g++ test.cc ./3DViewer_v2/model.cc ./3DViewer_v2/affine_transformation.cpp ./3DViewer_v2/matrix_oop.cpp -o tests -lgtest -std=c++17
	./tests

check: tests
	cp -f ../materials/linters/.clang-format 3DViewer_v2/.clang-format
	clang-format -n 3DViewer_v2/*.cc 3DViewer_v2/*.h
	cppcheck --language=c++ --enable=all --suppressions-list=suppresionlist.cfg 3DViewer_v2/*.cpp 3DViewer_v2/*.cc 3DViewer_v2/*.h
	rm -rf 3DViewer_v2/.clang-format
	CK_FORK=no leaks --atExit -- ./tests

gcov_report: clean
	g++ --coverage test.cc ./3DViewer_v2/model.cc ./3DViewer_v2/affine_transformation.cpp ./3DViewer_v2/matrix_oop.cpp -o tests -lgtest -std=c++17
	./tests
	lcov -t "test" --no-external -o tests.info -c -d ./
	genhtml -o report tests.info
	open ./report/index.html

clean:
	rm -rf *.gcda *.gcno *.info ./tests
	rm -rf ./report
	rm -rf $(BD)*
