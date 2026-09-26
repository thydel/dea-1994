#include <stdio.h>

#include "bit-field.h"
#include "gapp-defs.h"
#include "gapp-arch.h"

/*
 * gapp context layout
 *
 * externals      internals                     instructions
 * -------------- ----------------------------- -------------------
 * ---------- --- -------------- -------------- -------------------
 *   19   18   17   16   15   14   13   12   11    9    6    3    0
 * _EOW _NOS _RAM __BW __CY __SM ___C __EW __NS RAMI __CI _EWI _NSI
 * --------- ---- -------------- -------------- ---- ---- ---- ----
 *         2    1              3              3    2    3    3    3
 * -------------- ----------------------------- -------------------
 *              3                             6                  11
 * ----------------------------------------------------------------
 *                                                               19
 *
 */

static Bit_Field_Spec gapp_input_spec[] = {
  "NSI", 3, "EWI", 3, "CI", 3, "RAMI", 2, /* Instructions group */
				/* Registers group */
  "NS", 1, "EW", 1, "C", 1,	/* communication and alu input */
  "SM", 1, "CY", 1, "BW", 1,	/* alu output */
				/* External bits group */
  "RAM", 1,			/* implement ram as neighboorood bit */
  "NOS", 1, "EOW", 1,		/* NS and EW axe */
  0, 0
};

static Bit_Field_Spec gapp_output_spec[] = {
  "NNS", 1, "NEW", 1, "NC", 1,
  "NSM", 1, "NCY", 1, "NBW", 1,
  "NRAM", 1,
  0, 0
};

static Bit_Field_Spec gapp_instruction_spec[] = {
  "NSINS", 3, "EWINS", 3, "CINS", 3, "RAMINS", 2,
  0, 0
};

#define GAPP_IREG_SIZE (GAPP_NS_SIZE + GAPP_EW_SIZE + GAPP_C_SIZE)
#define GAPP_OREG_SIZE (GAPP_SM_SIZE + GAPP_CY_SIZE + GAPP_BW_SIZE) 

static Bit_Field_Spec gapp_iparts_spec[] = {
  "INS", GAPP_NSI_SIZE + GAPP_EWI_SIZE + GAPP_CI_SIZE + GAPP_RAMI_SIZE,
  "REG", GAPP_IREG_SIZE + GAPP_OREG_SIZE,
  "EXT", GAPP_RAM_SIZE + GAPP_NOS_SIZE + GAPP_EOW_SIZE,
  0, 0
};

/*
 * ALU
 */

static int gapp_alu[] = {	/* SM CY BW */
  0,				/* 0  0  0 */
  5,				/* 1  0  1 */
  4,				/* 1  0  0 */
  2,				/* 0  1  0 */
  5,				/* 1  0  1 */
  3,				/* 0  1  1 */
  2,				/* 0  1  0 */
  7				/* 1  1  1 */
};

Gapp_Pe_Spec gapp_pe_spec = {
  gapp_input_spec,
  gapp_output_spec,
  gapp_instruction_spec,
  gapp_iparts_spec,
  gapp_alu
};
