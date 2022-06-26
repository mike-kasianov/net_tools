.PHONY: apue hard

CC 			= cc
CFLAGS 		= -Wall -g #-DNDEBUG
PING_TARGET = ping
SNIFFER_TARGET = sniffer
WTF_TARGET  = wtf
BUILD_DIR	= _build

${PING_TARGET}: clean
	@mkdir ${BUILD_DIR}
	@${CC} ${CFLAGS} src/${PING_TARGET}.c -o ${BUILD_DIR}/${PING_TARGET}

${SNIFFER_TARGET}: clean
	@mkdir ${BUILD_DIR}
	@${CC} ${CFLAGS} src/${SNIFFER_TARGET}.c -o ${BUILD_DIR}/${SNIFFER_TARGET}

${WTF_TARGET}: clean
	@mkdir ${BUILD_DIR}
	@${CC} ${CFLAGS} src/${WTF_TARGET}.c -o ${BUILD_DIR}/${WTF_TARGET}

snf: clean
	@mkdir ${BUILD_DIR}
	@${CC} ${CFLAGS} \
		src/sniffer/sniffer_socket.c \
		src/sniffer/ethernet_frame.c \
		src/sniffer/ip_packet.c \
		src/sniffer/humanize.c \
		src/sniffer/main.c -o ${BUILD_DIR}/snf

clean:
	@rm -rf ${BUILD_DIR}