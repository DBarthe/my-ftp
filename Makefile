##
## Makefile for myftp in /home/bade/Dev/tek2/Unix/PSU_2013_myftp
## 
## Made by Barthelemy Delemotte
## Login   <delemo_b@epitech.net>
## 
## Started on Tue Apr  8 11:52:09 2014 Barthelemy Delemotte
## Last update Fri Apr 11 20:16:23 2014 Barthelemy Delemotte
##

DEBUG ?= 1

CC ?= gcc

SERV_PATH = ./serv
CLI_PATH = ./cli
COMMON_PATH = ./common

COMMON_INCPATH = $(COMMON_PATH)/includes
SERV_INCPATH = $(SERV_PATH)/includes
CLI_INCPATH = $(CLI_PATH)/includes

COMMON_SRCPATH = $(COMMON_PATH)/src
SERV_SRCPATH = $(SERV_PATH)/src
CLI_SRCPATH = $(CLI_PATH)/src

SERV_INCLUDES = -I $(COMMON_INCPATH) -I $(SERV_INCPATH)
CLI_INCLUDES = -I $(COMMON_INCPATH) -I $(CLI_INCPATH)
INCLUDES =

SERV_SRC = $(wildcard $(SERV_SRCPATH)/*.c) 	\
	$(wildcard $(SERV_SRCPATH)/*/*.c)	\
	$(wildcard $(COMMON_SRCPATH)/*.c)

CLI_SRC = $(wildcard $(CLI_SRCPATH)/*.c) \
	$(wildcard $(CLI_SRCPATH)/*/*.c) \
	$(wildcard $(COMMON_SRCPATH)/*.c)

SERV_OBJ = $(SERV_SRC:.c=.o)
CLI_OBJ = $(CLI_SRC:.c=.o)

CFLAGS = -Wall -Wextra  $(INCLUDES)
DBGFLAGS = -ggdb3 -DDEBUG
NDBGFLAGS = -DNDEBUG
OFLAGS = -O3
LDFLAGS =

RM = rm -vf

SERV_TARGET = server
CLI_TARGET = client

ifeq ($(DEBUG), 1)
CFLAGS += $(DBGFLAGS)
else
CFLAGS += $(NDBGFLAGS) $(OFLAGS)
endif

all: $(SERV_TARGET) $(CLI_TARGET)

$(SERV_TARGET): INCLUDES = $(SERV_INCLUDES)
$(SERV_TARGET): $(SERV_OBJ)
	$(CC) $(CFLAGS) -o $(SERV_TARGET) $(SERV_OBJ) $(LDFLAGS)

$(CLI_TARGET): INCLUDES = $(CLI_INCLUDES)
$(CLI_TARGET): $(CLI_OBJ)
	$(CC) $(CFLAGS) -o $(CLI_TARGET) $(CLI_OBJ) $(LDFLAGS)


clean:
	$(RM) $(SERV_OBJ) $(CLI_OBJ)

fclean: clean
	$(RM) $(SERV_TARGET) $(CLI_TARGET)

re: fclean all
