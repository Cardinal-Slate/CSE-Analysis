/* kernel/tag.c — the Real type identity: a psda whose potential is the tag 'R'. Below the seam, because a
   tag is raw reading bytes. Every Real value orders level with this node. cse_type_has checks it.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include "cse/analysis.h"
#include "slate/psda.h"

static const unsigned char TAG_R[] = { 'R', 0 };
static slate_psda RTYPE = { TAG_R, 0, 0 };
slate_psda *cse_real_type(void) { return &RTYPE; }
