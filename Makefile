# ������
CC = gcc

# ����ѡ������-gѡ�������ɵ�����Ϣ
CFLAGS = -Wall -g -I./lib/e_paper -I./lib/e_paper_test -I./lib/Fonts -I./lib/GUI -I./lib -I./user -I./conf -I./hardware -fPIC

# ����ѡ��
LDFLAGS = -fPIC

# ����ʱ��Ҫ�Ŀ�
LIBS = -lm -lwiringPi -lwiringPiDev -pthread 

# �ļ���׺
SUFFIXES = .c .o

# Ŀ�������
TARGET = main

# ����.c�ļ�
SRCS = $(shell find ./lib/e_paper ./lib/e_paper_test ./lib/Fonts ./lib/GUI ./system ./conf ./user ./conf ./hardware -name '*.c')

# ����.h�ļ�
HDRS = $(shell find ./lib/e_paper ./lib/e_paper_test ./lib/Fonts ./lib/GUI ./system ./conf ./user ./conf ./hardware -name '*.h')

# ����.o�ļ�
OBJS = $(SRCS:.c=.o)

# Ĭ��Ŀ��
all: $(TARGET)

# ����Ŀ��
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

# ����Դ�ļ�
%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# �����ļ�
CLEAN_FILES := *.o

clean:
	find . -type f -name '$(CLEAN_FILES)' -exec rm -f {} \;
	@echo "All .o files have been removed."

.PHONY: clean