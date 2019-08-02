.PHONY: test

TARGET := test_my_list
SOURCE := test_my_list.c
INCLUDES := -I$(TOPDIR)/include -I$(INCLUDE_MY_LOG)
LIBSDIR := -L$(TOPDIR)/lib
LIBS := -lmylist

test: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CCFLAGS) $(MACROS) $(INCLUDES) $(LIBSDIR) -o $@ $? $(LIBS)

clean:
	$(RM) -f $(TARGET)
