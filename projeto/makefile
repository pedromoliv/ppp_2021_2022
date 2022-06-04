vpath %.c source/
vpath %.h source/

CC		  		= gcc
FLAGS	 		= -Wall -Wextra -g
OBJS	  		= main.o
PROG	  		= projeto

all:			${PROG} ${PROG_MNODE}

clean:
				rm -f ${OBJS} ${PROG}

${PROG}:	    ${OBJS}
			    ${CC} ${FLAGS} ${OBJS} -o $@

.c.o:
				${CC} ${FLAGS} $< -c -o $@

main.o: main.c inc.h
projeto: main.o
