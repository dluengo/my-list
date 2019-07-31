LIB_DIR := lib
INCLUDE_DIR := include
MY_LOG_INCLUDE_DIR := ../my-log/include
MACROS :=
CCFLAGS := 

ifeq (${DEBUG},1)
    MACROS := $(MACROS) -DDEBUG
    CCFLAGS := -ggdb
endif

.PHONY: all clean test

all: libmylist.so

libmylist.so: src/my_list.c
	mkdir -p ${LIB_DIR}
	gcc ${MACROS} ${CCFLAGS} -fPIC -shared -o ${LIB_DIR}/$@ -I${INCLUDE_DIR} -I${MY_LOG_INCLUDE_DIR} $?

clean:
	rm -fr ${LIB_DIR} test/test_my_list

test: test_my_list

test_my_list: test/test_my_list.c
	gcc ${MACROS} ${CCFLAGS} -o test/$@ -I${MY_LOG_INCLUDE_DIR} -I${INCLUDE_DIR} -Llib/ $? -lmylist
