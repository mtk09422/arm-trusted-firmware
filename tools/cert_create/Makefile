#
# Copyright (c) 2015, ARM Limited and Contributors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# Neither the name of ARM nor the names of its contributors may be used
# to endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#

PROJECT		:= cert_create
PLAT		:= none
V		:= 0
DEBUG		:= 0
BINARY		:= ${PROJECT}
OPENSSL_DIR	:= /usr

OBJECTS := src/cert.o \
           src/ext.o \
           src/key.o \
           src/main.o \
           src/tbb_cert.o \
           src/tbb_ext.o \
           src/tbb_key.o \
           src/sha.o

CFLAGS := -Wall -std=c99

# Check the platform
ifeq (${PLAT},none)
  $(error "Error: Unknown platform. Please use PLAT=<platform name> to specify the platform")
endif
PLAT_MAKEFILE		:=	platform.mk
PLAT_INCLUDE	:=	$(shell find ../../plat/ -wholename '*/${PLAT}/${PLAT_MAKEFILE}' |	\
				sed 's/${PLAT_MAKEFILE}/include/')
ifeq ($(PLAT_INCLUDE),)
  $(error "Error: Invalid platform '${PLAT}'")
endif

ifeq (${DEBUG},1)
  CFLAGS += -g -O0 -DDEBUG -DLOG_LEVEL=40
else
  CFLAGS += -O2 -DLOG_LEVEL=20
endif
ifeq (${V},0)
	Q := @
else
	Q :=
endif

# Make soft links and include from local directory otherwise wrong headers
# could get pulled in from firmware tree.
INC_DIR := -I ./include -I ${PLAT_INCLUDE} -I ${OPENSSL_DIR}/include
LIB_DIR := -L ${OPENSSL_DIR}/lib
LIB := -lssl -lcrypto

CC := gcc
RM := rm -rf

.PHONY: all clean

all: clean ${BINARY}

${BINARY}: ${OBJECTS} Makefile
	@echo "  LD      $@"
	@echo 'const char build_msg[] = "Built : "__TIME__", "__DATE__; \
                const char platform_msg[] = "${PLAT}";' | \
                ${CC} -c ${CFLAGS} -xc - -o src/build_msg.o
	${Q}${CC} src/build_msg.o ${OBJECTS} ${LIB_DIR} ${LIB} -o $@

%.o: %.c
	@echo "  CC      $<"
	${Q}${CC} -c ${CFLAGS} ${INC_DIR} $< -o $@

clean:
	${Q}${RM} -f src/build_msg.o ${OBJECTS}

realclean: clean
	${Q}${RM} -f ${BINARY}
