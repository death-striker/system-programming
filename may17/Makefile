  BIN = binary/
  OBJ = object/
  INC = include/
  SRC = source/
  CFLAG = -c
  OFLAG = -o
  all:  build-server build-client
  build-server: ${OBJ}func.o
		g++  ${OFLAG} ${BIN}server06 ${SRC}server.cpp ${OBJ}func.o
  ${OBJ}func.o:
		g++ ${CFLAG} ${OFLAG} ${OBJ}func.o ${SRC}func.cpp
  build-client:
		g++ ${OFLAG} ${BIN}client06 ${SRC}client.cpp
  start-server:
		./${BIN}server06
  start-client:
		./${BIN}client06
  clean:
		rm $(OBJ)func.o
		rm ${BIN}client06
		rm ${BIN}server06

