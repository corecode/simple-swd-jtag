SOC+=	kinetis/MKL27Z4
TARGET=	MKL27Z256VFM4

DFUVID?=	2323
DFUPID?=	0001

SRCS-board=	board.c
SRCS-board.dir= ${PROJECTDIR}/src/board
SRCS.libs+=	board
