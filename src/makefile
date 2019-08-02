INCLUDES := -I$(TOPDIR)/include -I$(INCLUDE_MY_LOG)
SOURCE := my_list.c
TARGET := libmylist.so
LIBFLAGS := -fPIC -shared
LIBDIR := $(TOPDIR)/lib

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(MKDIR) -p $(LIBDIR)
	$(CC) $(LIBFLAGS) $(CCFLAGS) $(MACROS) $(INCLUDES) -o $(LIBDIR)/$@ $?

clean:
	$(RM) -fr $(LIBDIR)

