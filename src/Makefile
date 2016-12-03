PROG=swd-adapter
SRCS= swd-adapter.c swd-adapter.desc \
	../contrib/CMSIS_DAP/Firmware/DAP.c \
	../contrib/CMSIS_DAP/Firmware/JTAG_DP.c \
	../contrib/CMSIS_DAP/Firmware/SW_DP.c \
	DAP_config.c serial.c

# CPPFLAGS+= -I../contrib/CMSIS_DAP/Firmware
CPPFLAGS+= -D'__forceinline=inline __attribute__((__always_inline__))'
CPPFLAGS+= -D'__weak=__attribute__((__weak__))'
CPPFLAGS+= -DSTACK_SIZE=0x300
CPPFLAGS+= -I. -I../contrib/CMSIS_DAP/Firmware

DFUPID=2000

BOARD= simple-swd-adapter

include ../mchck/build/mchck.mk
