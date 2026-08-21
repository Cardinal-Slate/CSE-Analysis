/* kernel/atoms.c — Analysis's transcendental atoms and constants, spelled in bytes below the seam.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include "slate/psda.h"

static const unsigned char A_SQRT[] = { 'q', 0 };
static const unsigned char A_EXP[]  = { 'x', 0 };
static const unsigned char A_LN[]   = { 'l', 0 };
static const unsigned char A_SIN[]  = { 's', 0 };
static const unsigned char A_COS[]  = { 'c', 0 };
static const unsigned char A_ATAN[] = { 't', 0 };
static const unsigned char A_PI[]   = { 'p', 0 };
static const unsigned char A_E[]    = { 'E', 0 };

slate_reading cse_analysis_sqrt_op = A_SQRT;
slate_reading cse_analysis_exp_op  = A_EXP;
slate_reading cse_analysis_ln_op   = A_LN;
slate_reading cse_analysis_sin_op  = A_SIN;
slate_reading cse_analysis_cos_op  = A_COS;
slate_reading cse_analysis_atan_op = A_ATAN;
slate_reading cse_analysis_pi      = A_PI;
slate_reading cse_analysis_e       = A_E;
