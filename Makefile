CXX=		g++-5
CPP=		${CXX} -E
CXXFLAGS=	-std=c++14  -O0 -Wall -Wextra -g
CPPFLAGS=	-I/opt/poco/include
LD=		${CXX}
LDFLAGS=	-std=c++14 -L/opt/poco/lib -Wl,-rpath=/opt/poco/lib
LIBS=		-lPocoFoundation -lPocoUtil -lPocoNet -pthread

SRC=		RequestHandlerFactory.cc RequestHandler.cc HttpSubsystem.cc \
		Praline.cc Topic.cc TopicList.cc TopicWriter.cc

TEST=		RequestHandlerTest.cc

OBJ=		${SRC:.cc=.o}

all: test praline

%.o: %.cc
	${CXX} ${CXXFLAGS} ${CPPFLAGS} -c -o $@ $<

%.d: %.cc
	${CPP} ${CXXFLAGS} ${CPPFLAGS} -pthread -I. $< -MM -o $@

praline: ${OBJ} main.o
	${LD} ${LDFLAGS} -o praline ${OBJ} main.o ${LIBS}

RequestHandlerTest: RequestHandlerTest.o ${OBJ}
	${CXX} ${CXXFLAGS} ${LDFLAGS} ${LIBS} -pthread -I. $^ -o $@

.PHONY: test
test: RequestHandlerTest
	${PWD}/RequestHandlerTest

.PHONY: clean
clean:
	@-rm *.o praline 2> /dev/null || true

-include ${SRC:%.cc=%.d}
-include ${TEST:%.cc=%.d}
