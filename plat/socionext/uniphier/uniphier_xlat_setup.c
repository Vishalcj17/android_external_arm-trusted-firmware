/*
 * Copyright (c) 2017-2020, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <platform_def.h>

#include <common/debug.h>
#include <lib/xlat_tables/xlat_tables_v2.h>

#define UNIPHIER_REG_REGION_BASE	0x50000000ULL
#define UNIPHIER_REG_REGION_SIZE	0x20000000ULL

void uniphier_mmap_setup(void)
{
	VERBOSE("Trusted RAM seen by this BL image: %p - %p\n",
		(void *)BL_CODE_BASE, (void *)BL_END);
	mmap_add_region(BL_CODE_BASE, BL_CODE_BASE,
			round_up(BL_END, PAGE_SIZE) - BL_CODE_BASE,
			MT_MEMORY | MT_RW | MT_SECURE);

	/* remap the code section */
	VERBOSE("Code region: %p - %p\n",
		(void *)BL_CODE_BASE, (void *)BL_CODE_END);
	mmap_add_region(BL_CODE_BASE, BL_CODE_BASE,
			round_up(BL_CODE_END, PAGE_SIZE) - BL_CODE_BASE,
			MT_CODE | MT_SECURE);

	/* remap the coherent memory region */
	VERBOSE("Coherent region: %p - %p\n",
		(void *)BL_COHERENT_RAM_BASE, (void *)BL_COHERENT_RAM_END);
	mmap_add_region(BL_COHERENT_RAM_BASE, BL_COHERENT_RAM_BASE,
			BL_COHERENT_RAM_END - BL_COHERENT_RAM_BASE,
			MT_DEVICE | MT_RW | MT_SECURE);

	/* register region */
	mmap_add_region(UNIPHIER_REG_REGION_BASE, UNIPHIER_REG_REGION_BASE,
			UNIPHIER_REG_REGION_SIZE,
			MT_DEVICE | MT_RW | MT_SECURE);

	init_xlat_tables();
}
