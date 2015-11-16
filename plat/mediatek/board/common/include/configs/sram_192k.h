/*
 * Copyright (c) 2015, ARM Limited and Contributors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * Neither the name of ARM nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific
 * prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __SRAM_192K_H__
#define __SRAM_192K_H__

/*******************************************************************************
 * Platform memory map related constants
 ******************************************************************************/
/*
 * MT8173 SRAM memory layout
 * 0x100000 +-------------------+
 *          | shared mem (4KB)  |
 * 0x101000 +-------------------+
 *          |                   |
 *          |   BL3-1 (124KB)   |
 *          |                   |
 * 0x120000 +-------------------+
 *          |   DMA buf (4KB)   |
 * 0x121000 +-------------------+
 *          |  reserved (60KB)  |
 * 0x130000 +-------------------+
 */
/* TF txet, ro, rw, xlat table, coherent memory ... etc.
 * Size: release: 128KB, debug: 128KB
 */
#define TZRAM_BASE		(0x100000)
#if DEBUG
#define TZRAM_SIZE		(0x20000)
#else
#define TZRAM_SIZE		(0x20000)
#endif

/* DMA buffer: 4KB */
/* The start address of this region should be aligned to page boundary(4KB) */
#define DMA_BUF_BASE		(TZRAM_BASE + TZRAM_SIZE)
#define DMA_BUF_SIZE		(0x1000)

/* Reserved: 60KB */
#define TZRAM2_BASE		(DMA_BUF_BASE + DMA_BUF_SIZE)
#define TZRAM2_SIZE		(0xF000)

/* shared memory: 4KB
 * We provide this memory region for earlier boot stage to pass board specific
 * arguments to ARM TF. */
#define BL31_SHARED_MEM_BASE	(0x100000)
#define BL31_SHARED_MEM_SIZE	(0x1000)

/*******************************************************************************
 * BL31 specific defines.
 ******************************************************************************/
/*
 * Put BL3-1 at the top of the Trusted SRAM (just below the shared memory, if
 * present). BL31_BASE is calculated using the current BL3-1 debug size plus a
 * little space for growth.
 */
#define BL31_BASE		(TZRAM_BASE + 0x1000)
#define BL31_LIMIT		(TZRAM_BASE + TZRAM_SIZE)
#define TZRAM2_LIMIT		(TZRAM2_BASE + TZRAM2_SIZE)

/*******************************************************************************
 * Platform specific page table and MMU setup constants
 ******************************************************************************/
#define ADDR_SPACE_SIZE		(1ull << 32)
#define MAX_XLAT_TABLES		4
#define MAX_MMAP_REGIONS	16

#endif /* __SRAM_192K_H__ */