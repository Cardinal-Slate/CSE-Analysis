/* src/analysis.c — reals as enclosures over an opaque component field. Composes F's operations on a
   CSE-DSA cell; names no concrete field. Slate-only.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include "cse/analysis.h"
#include "cse/dsa/cell.h"

slate_psda *cse_real(slate_psda **pool, slate_psda *lo, slate_psda *hi) {
  return cse_cell(cse_cell_take(pool), lo, hi, 0);
}
slate_psda *cse_real_lift(slate_psda **pool, slate_psda *q) { return cse_real(pool, q, q); }
slate_psda *cse_real_lo(slate_psda *x) { return cse_cell_payload(x); }
slate_psda *cse_real_hi(slate_psda *x) { return cse_cell_rest(x); }

slate_psda *cse_real_add(const cse_field *F, slate_psda **p, slate_psda *x, slate_psda *y) {
  return cse_real(p, F->add(p, cse_real_lo(x), cse_real_lo(y)),
                     F->add(p, cse_real_hi(x), cse_real_hi(y)));
}
