CXX=		clang++-3.6
CXXFLAGS=	-std=c++14 -stdlib=libc++ -O2 -Wall -Wextra -g
CPPFLAGS=	-I/opt/poco/include
LD=		${CXX}
LDFLAGS=	-std=c++14 -stdlib=libc++ -L/opt/poco/lib -Wl,-rpath=/opt/poco/lib
LIBS=		-lPocoFoundation -lPocoUtil -lPocoNet

SRC=		RequestHandlerFactory.cc HttpSubsystem.cc Praline.cc main.cc
OBJ=		${SRC:.cc=.o}

all: praline

%.o: %.cc
	${CXX} ${CXXFLAGS} ${CPPFLAGS} -c -o $@ $^

praline: ${OBJ}
	${LD} ${LDFLAGS} -o praline ${OBJ} ${LIBS}

.PHONY: clean
clean:
	-rm *.o praline
