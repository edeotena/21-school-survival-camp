CC=gcc
CFLAGS=-Wall -Wextra -Werror
SRC_PATH=../
MAIN=main_executable_module.c

PATHS= \
	   $(SRC_PATH)data_libs \
	   $(SRC_PATH)data_module \
	   $(SRC_PATH)yet_another_decision_module

DEC= \
	   $(SRC_PATH)yet_another_decision_module/decision.c

IO = \
	   $(SRC_PATH)data_libs/data_io.c

IO_MACRO= \
	   $(SRC_PATH)data_libs/data_io_macro.c

STAT= \
	   $(SRC_PATH)data_libs/data_stat.c

PROCESS= \
	   $(SRC_PATH)data_module/data_process.c

SAVE=../../build/Quest_

all: clean rebuild

rebuild:
	$(CC) $(addprefix -I,$(PATHS)) $(CFLAGS) $(MAIN) $(DEC) $(IO) $(STAT) $(PROCESS) -o $(SAVE)3

clean:
	rm -rf *.o ../../build/* *.out *.a *.os

data_stat.a:
	$(CC) -c $(CFLAGS) $(STAT) -o data_stat.o
	ar -rc libdata_stat.a data_stat.o
	rm -rf data_stat.o
	ranlib libdata_stat.a
	cp libdata_stat.a ./../../build

build_with_static: data_stat.a
	$(CC) $(addprefix -I,$(PATHS)) $(CFLAGS) $(MAIN) $(DEC) $(IO) $(PROCESS) -L. -ldata_stat -o $(SAVE)5

data_process: data_stat.a
	$(CC) $(CFLAGS) -c -fPIC -I $(SRC_PATH)data_libs $(STAT) $(PROCESS)
	$(CC) -shared -o libdata_process.so data_process.o data_stat.o
	rm -rf data_process.o
	cp libdata_process.so ./../../build

build_with_dynamic: data_process
	$(CC) $(addprefix -I,$(PATHS)) $(CFLAGS) $(MAIN) $(DEC) $(IO) $(STAT) -o $(SAVE)6 -D SHARED

build_with_macro:
	$(CC) $(addprefix -I,$(PATHS)) $(CFLAGS) $(MAIN) $(DEC) $(IO_MACRO) $(STAT) $(PROCESS) -o $(SAVE)4 -D MACRO
