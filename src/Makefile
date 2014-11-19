PROG=swd-adapter
SRCS= ../contrib/CMSIS_DAP/Firmware/DAP.c \
	../contrib/CMSIS_DAP/Firmware/JTAG_DP.c \
	../contrib/CMSIS_DAP/Firmware/SW_DP.c \
	DAP_config.c

# CPPFLAGS+= -I../contrib/CMSIS_DAP/Firmware
CPPFLAGS+= -D'__forceinline=inline __attribute__((__always_inline__))'
CPPFLAGS+= -D'__weak=__attribute__((__weak__))'

include ../contrib/mchck/toolchain/mchck.mk
