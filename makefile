.PHONY: test

export MACROS :=
export CCFLAGS := 
export CC := gcc
export RM := rm
export MKDIR := mkdir
export TOPDIR := $(shell pwd)
export INCLUDE_MY_LOG := $(TOPDIR)/../my-log/include

SRCDIR := src
TESTDIR := test

ifeq (${DEBUG},1)
    MACROS := $(MACROS) -DDEBUG
    CCFLAGS := -ggdb
endif

all:
	$(MAKE) -C $(SRCDIR)

test:
	$(MAKE) -C $(TESTDIR)

clean:
	$(MAKE) -C $(SRCDIR) clean
	$(MAKE) -C $(TESTDIR) clean

