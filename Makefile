CC=g++
CFLAGS=-std=c++11 -Wall
TARGET=Busca

BUILD_DIR = ./obj
BIN_DIR = ./bin
SRC_DIR = ./src
INCLUDE_DIR = ./include

${BUILD_DIR}/${TARGET}: ${BUILD_DIR}/ListaConsulta.o ${BUILD_DIR}/ListaEncadeada.o ${BUILD_DIR}/ListaIndice.o ${BUILD_DIR}/Palavra.o ${BUILD_DIR}/TabelaHash.o ${BUILD_DIR}/main.o
	${CC} ${CFLAGS} -o ./${BIN_DIR}/${TARGET} ${BUILD_DIR}/*.o

${BUILD_DIR}/ListaConsulta.o: ${INCLUDE_DIR}/ListaConsulta.hpp ${SRC_DIR}/ListaConsulta.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/ListaConsulta.cpp -o ${BUILD_DIR}/ListaConsulta.o

${BUILD_DIR}/ListaEncadeada.o: ${INCLUDE_DIR}/ListaEncadeada.hpp ${SRC_DIR}/ListaEncadeada.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/ListaEncadeada.cpp -o ${BUILD_DIR}/ListaEncadeada.o

${BUILD_DIR}/ListaIndice.o: ${INCLUDE_DIR}/Palavra.hpp ${SRC_DIR}/ListaIndice.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/ListaIndice.cpp -o ${BUILD_DIR}/ListaIndice.o

${BUILD_DIR}/Palavra.o: ${INCLUDE_DIR}/Palavra.hpp ${SRC_DIR}/Palavra.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/Palavra.cpp -o ${BUILD_DIR}/Palavra.o

${BUILD_DIR}/TabelaHash.o: ${INCLUDE_DIR}/TabelaHash.hpp ${SRC_DIR}/TabelaHash.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/TabelaHash.cpp -o ${BUILD_DIR}/TabelaHash.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/ListaConsulta.hpp ${INCLUDE_DIR}/ListaEncadeada.hpp ${INCLUDE_DIR}/Palavra.hpp ${INCLUDE_DIR}/TabelaHash.hpp ${INCLUDE_DIR}/FuncoesTamanhoArquivos.hpp ${SRC_DIR}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/ -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o