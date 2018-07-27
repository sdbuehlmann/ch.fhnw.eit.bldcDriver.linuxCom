PROJECT = bldcDriverLinuxCom
OBJS = src/$(PROJECT).o \
serializer/src/bldcDriverSerializer.o \
serializer/src/serializer.o

CC      = gcc
INC = -I"/opt/java/jdk1.8.0_102/include" -I"/opt/java/jdk1.8.0_102/include/linux" -I"./inc" -I"./serializer/inc"

all: $(OBJS)
	gcc -shared -o $(PROJECT).so $(OBJS) -O2

# erzeugen der .o-Dateien
%.o: %.c
	gcc -Wall -fPIC $(INC) -o $@ -c $<