PROJECT=s21_3DViewer
CC=gcc
# Флаги для компиляции
CFLAGS=-Wall -Werror -Wextra -std=c11 -g
# Флаги для компиляции с покрытием
COVERCOMPFLAGS=-fprofile-arcs -ftest-coverage
# Флаги для линковки с покрытием
COVERLINKFLAGS=-lgcov
CHKCOMPFLAGS=$(shell pkg-config --cflags check)
CHKLINKFLAGS=$(shell pkg-config --cflags --libs check)
#-lcheck_pic -lrt -lpthread -lsubunit -lm
# Папка с тестами
TESTDIR=tests
# Папка для объектных файлов - для ручных тестов и для автотеста
MANUALBUILDDIR=build_manual
AUTOTESTBUILDDIR=build_auto
# Имя исполняемого файла тестов
EXECNAME=s21_tests
# Список всех файлов "*.c" в текущей папке
PROJECTSRC=$(wildcard *.c)
# Список объектных файлов "*.о" тестов
TESTOBJ=$(patsubst %.c,%.o,$(wildcard $(TESTDIR)/*.c))
# Список объектных файлов "*.о" при компиляции для ручного тестирования
PROJECTMANUALOBJ=$(addprefix $(MANUALBUILDDIR)/, $(patsubst %.c,%.o,$(wildcard *.c)))
# Список объектных файлов "*.о" при компиляции для автотеста
PROJECTAUTOOBJ=$(addprefix $(AUTOTESTBUILDDIR)/, $(patsubst %.c,%.o,$(wildcard *.c)))
# Папка компиляции
BUILDFOLDER=./build
# Папка документации
MANUALFOLDER=./manual

now:=$(shell date)
VERSION = `date +"%Y.%m.%d"`
ARCHIVE = 3DViewerulator-$(VERSION)


OPENWITH = vi
ifeq ($(shell uname -s), Linux)
	OPENWITH = xdg-open
endif
ifeq ($(shell uname -s), Darwin)
	OPENWITH = open
endif

# Здесь должны быть перечислены все цели, которые не являются именами файлов.
# Поддерживать акутальность списка при редактировании целей!
.PHONY: all test gcov_report style clean clean_report rebuild leaks install uninstall dist dvi run

# Цель по умолчанию
all: install
#	@$(MAKE) --no-print-directory test
#	@$(MAKE) --no-print-directory gcov_report

test: $(EXECNAME)

# Запускам тесты без gcov_report
run_test: $(EXECNAME)
	@$(MAKE) --no-print-directory clean_report
	@./$(EXECNAME)

#
# ****** П О К Р Ы Т И Е ******
#

# Определение % покрытия кода тестами.
gcov_report: $(EXECNAME)
	@$(MAKE) --no-print-directory clean_report
	@echo "********** Starting test cases... **********"
	@./$(EXECNAME)
	@echo "*************** Done testing ***************"
	@lcov -o tests.info -c -d . --no-external
	@genhtml -o report tests.info

open_report: gcov_report
	@$(OPENWITH) report/index.html

#
# ****** Л И Н К О В К А ******
#

# Цель для сборки объектных файлов тестов в исполняемый файл + наша библиотека 3DViewer.
# Все -l флаги должны быть справа от имен объектных файлов!
$(EXECNAME): test_$(PROJECT).a $(TESTOBJ)
	@$(CC) $(TESTOBJ) test_$(PROJECT).a -o $(EXECNAME) $(CHKLINKFLAGS) $(COVERLINKFLAGS)

#
# ****** А Р Х И В И Р О В А Н И Е ******
#

$(PROJECT).a: $(PROJECTAUTOOBJ)
	@ar -rcs $@ $^

test_$(PROJECT).a: $(PROJECTMANUALOBJ)
	@ar -rcs $@ $^

#
# ****** К О М П И Л Я Ц И Я ******
#

# Цель для компиляции исходников для библиотеки "3DViewer.a"
# (АВТОТЕСТЫ)
$(PROJECTAUTOOBJ): $(AUTOTESTBUILDDIR)/%.o: %.c $(PROJECT).h
	@mkdir -p $(AUTOTESTBUILDDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Цель для компиляции исходников для библиотеки "3DViewer.a"
# (РУЧНЫЕ ТЕСТЫ)
$(PROJECTMANUALOBJ): $(MANUALBUILDDIR)/%.o: %.c $(PROJECT).h
	@mkdir -p $(MANUALBUILDDIR)
	@$(CC) $(CFLAGS) $(CHKCOMPFLAGS) $(COVERCOMPFLAGS) -c $< -o $@

# Цель для компиляции исходников (c-файлов) тестов в объектные (о-) файлы.
# Одинаково и для автотеста, и для ручного теста
$(TESTOBJ): $(TESTDIR)/%.o: $(TESTDIR)/%.c $(TESTDIR)/3DViewer_test.h
	@$(CC) $(CFLAGS) -c $< -o $@ 

#
# ****** В С П О М О Г А Т Е Л Ь Н О Е ******
#

# Исправление отступов для тех, у кого с этим беда :)
style:
	@echo "Correcting code style..."
	@cp ../materials/linters/.clang-format .
	@clang-format -i *.c *.h
	@clang-format -i $(TESTDIR)/*.c $(TESTDIR)/*.h
	@rm -rf ./.clang-format
	@echo "Done correcting code style."

# Общая очистка, при ее вызове автоматом срабатывает очистка отчетов.
clean:
	@echo "Cleaning..."
	@$(MAKE) --no-print-directory clean_report
	@rm -rf $(TESTDIR)/*.o
	@rm -rf $(MANUALBUILDDIR) $(AUTOTESTBUILDDIR)
	@rm -rf *.a 
	@rm -rf $(EXECNAME)
	@rm -rf *.tar
	@rm -rf $(MANUALFOLDER)
	@echo "Done cleaning."


# Отдельная цель для очистки отчетов о покрытии.
# Отчеты надо чистить перед повторным запуском проверки покрытия.
clean_report:
	@rm -rf $(MANUALBUILDDIR)/*.gcda
	@rm -rf report tests.info

rebuild:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory test

leaks: test
	@valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(EXECNAME)

doc:  
	gcc -Wall -Werror -Wextra -g *.c ./tests/*.c -lcheck_pic -lrt -lpthread -lsubunit -lm
	./a.out
	@valgrind --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./a.out

# Установка

install:
	mkdir $(BUILDFOLDER)
	cmake -S ./3DViewer/ -B $(BUILDFOLDER)
	cd $(BUILDFOLDER) && $(MAKE)

run:
	open -Fn $(BUILDFOLDER)/3DViewer.app

uninstall: 
	rm -rf $(BUILDFOLDER)
	rm -rf html
	rm -rf latex

dvi: 
	mkdir $(MANUALFOLDER)
	doxygen Doxyfile
	mv html latex $(MANUALFOLDER)
	open $(MANUALFOLDER)/html/index.html

dvi_open:
	open docs/html/index.html

dist: clean
	tar -cf $(ARCHIVE).tar ./*