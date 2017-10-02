CC = g++
DEBUG = -g -DDEBUG
CFLAGS = -Wall -std=c++11 $(DEBUG)
LFLAGS = -Wall -std=c++11 $(DEBUG)

SRC = \
../src/AsyncWriter.cpp \
../src/Compute.cpp \

INCLUDE_HEADER_LOCATION=\
-I../src/

LINK_LIB_LOCATION=\
# -L../../
LINK_LIB_NAME=\
-ltbb \
-pthread \
# -lblas \
# -llapack \
# -ldl

compile:
	${CC} -o test.out ${CFLAGS} main.cpp ${SRC} ${INCLUDE_HEADER_LOCATION} ${LINK_LIB_LOCATION} ${LINK_LIB_NAME}

clean:
	rm -f test_async_result.txt
	rm -f test_async_ID.txt
	rm -f test.out


