LIB_DIR = lib
INCLUDE_DIR = include
MY_LOG_INCLUDE_DIR = ../my-log/include

all: libmylist.so

libmylist.so: src/my_list.c
	mkdir -p ${LIB_DIR}
	gcc -fPIC -shared -o ${LIB_DIR}/$@ -I${INCLUDE_DIR} -I${MY_LOG_INCLUDE_DIR} $?

clean:
	rm -fr ${LIB_DIR}
