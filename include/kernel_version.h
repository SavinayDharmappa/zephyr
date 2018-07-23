/* kernel version support */

/*
 * Copyright (c) 2015 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _kernel_version__h_
#define _kernel_version__h_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * The kernel version has been converted from a string to a four-byte
 * quantity that is divided into two parts.
 *
 * Part 1: The three most significant bytes represent the kernel's
 * numeric version, x.y.z. These fields denote:
 *       x -- major release
 *       y -- minor release
 *       z -- patchlevel release
 * Each of these elements must therefore be in the range 0 to 255, inclusive.
 *
 * Part 2: The least significant byte is reserved for future use.
 */
#define SYS_KERNEL_VER_MAJOR(ver) (((ver) >> 24) & 0xFF)
#define SYS_KERNEL_VER_MINOR(ver) (((ver) >> 16) & 0xFF)
#define SYS_KERNEL_VER_PATCHLEVEL(ver) (((ver) >> 8) & 0xFF)

struct version_header {
	/** Always equal to $B!N */
	u8_t magic[4];

	/** Header format version */
	u32_t version;
	u8_t major;
	u8_t minor;
	u8_t patch;

	/**
	 * Human-friendly version string, free format (not NULL terminated)
	 * Advised format is: PPPPXXXXXX-YYWWTBBBB
	 *  - PPPP  : product code
	 *  - XXXXXX: binary info. Usually contains information such as the
	 *    binary type (bootloader, application), build variant (unit
	 *    tests, debug, release), release/branch name
	 *  - YY    : year last 2 digits
	 *  - WW    : work week number
	 *  - T     : build type, e.g. [W]eekly, [L]atest, [R]elease,
	 *  [P]roduction, [F]actory, [C]ustom
	 *  - BBBB  : build number, left padded with zeros
	 * Examples:
	 *  - A101BOOT01-1503W0234
	 *  - CCCKAPP123-1502R0013
	 */
	char version_string[20];

	/**
	 * Micro-SHA1 (first 4 bytes of the SHA1) of the binary payload
	 * excluding this header. It allows to uniquely identify the
	 * exact binary used. In the case the header is located in the
	 * middle of the payload, the SHA1 has to be computed from two
	 * disjoint buffers.
	 */
	u8_t hash[4];

	/**
	 * Position of the payload start relative to the address of this
	 * structure
	 */
	s32_t offset;

	/** Filled with zeros, can be eventually used for 64 bits support */
	u8_t reserved_1[4];

	/** Size of the payload in bytes, including this header */
	u32_t size;

	/** Filled with zeros, can be eventually used for 64 bits support */
	u8_t reserved_2[4];
} __packed;

/** The global version header struct */
extern struct version_header version_header;

/* kernel version routines */

extern u32_t sys_kernel_version_get(void);

#ifdef __cplusplus
}
#endif

#endif /* _kernel_version__h_ */
