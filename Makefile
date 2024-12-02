# 编译器
CC = gcc

# 编译选项，添加了-g选项以生成调试信息
CFLAGS = -Wall -g -I./lib/e_paper -I./lib/e_paper_test -I./lib/Fonts -I./lib/GUI -I./lib -I./user -I./conf -I./hardware -fPIC

# 链接选项
LDFLAGS = -fPIC

# 链接时需要的库
LIBS = -lm -lwiringPi -lwiringPiDev -pthread 

# 文件后缀
SUFFIXES = .c .o

# 目标程序名
TARGET = main

# 所有.c文件
SRCS = $(shell find ./lib/e_paper ./lib/e_paper_test ./lib/Fonts ./lib/GUI ./system ./conf ./user ./conf ./hardware -name '*.c')

# 所有.h文件
HDRS = $(shell find ./lib/e_paper ./lib/e_paper_test ./lib/Fonts ./lib/GUI ./system ./conf ./user ./conf ./hardware -name '*.h')

# 所有.o文件
OBJS = $(SRCS:.c=.o)

# 默认目标
all: $(TARGET)

# 链接目标
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# 编译源文件
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理文件
CLEAN_FILES := *.o

clean:
	find . -type f -name '$(CLEAN_FILES)' -exec rm -f {} \;
	@echo "All .o files have been removed."

.PHONY: clean