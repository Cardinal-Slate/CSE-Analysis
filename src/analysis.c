/* src/analysis.c — reals as enclosures [lo,hi] over ℚ, type-first. A value carries the tag 'R'
   (kernel/tag.c); its bounds are ℚ values and its arithmetic is Arith's (cse_arith_*). Interval add checks
   its carriers have type Real (cse_type_has); a foreign carrier is refused. Slate-only.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include "cse/analysis.h"
#include "cse/arith.h"
#include "cse/types.h"
#include "cse/dsa/cell.h"

slate_psda *cse_real(slate_psda **pool, slate_psda *lo, slate_psda *hi) {
  return cse_cell(cse_cell_take(pool), lo, hi, cse_real_type()->potential);   /* tag 'R', lo/hi = payload/rest */
}
slate_psda *cse_real_lift(slate_psda **pool, slate_psda *q) { return cse_real(pool, q, q); }
slate_psda *cse_real_lo(slate_psda *x) { return cse_cell_payload(x); }
slate_psda *cse_real_hi(slate_psda *x) { return cse_cell_rest(x); }

slate_psda *cse_real_add(slate_psda **p, slate_psda *x, slate_psda *y) {
  if (!cse_type_has(x, cse_real_type()) || !cse_type_has(y, cse_real_type())) return 0;
  return cse_real(p, cse_arith_add(p, cse_real_lo(x), cse_real_lo(y)),
                     cse_arith_add(p, cse_real_hi(x), cse_real_hi(y)));
}
