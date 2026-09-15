/* src/analysis.c — reals as enclosures [lo,hi] over ℚ, type-first over opaque typing. A value is a ℚ pair
   (lo, hi) tagged with the Real type via cse_typed: its content is a cell(lo, hi), its type is an identity
   handle. The bound arithmetic is Arith's (cse_arith_*). Interval add checks its carriers have type Real by
   identity (cse_type_has), never reading their content. Slate-only.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include "cse/analysis.h"
#include "cse/arith.h"
#include "cse/types.h"
#include "cse/dsa/cell.h"

/* the Real type: an object with identity (its fields are never inspected) */
static slate_psda RTYPE;
slate_psda *cse_real_type(void) { return &RTYPE; }

slate_psda *cse_real(slate_psda **pool, slate_psda *lo, slate_psda *hi) {
  slate_psda *content = cse_cell(cse_cell_take(pool), lo, hi, 0);   /* lo = payload, hi = rest */
  return cse_typed(cse_cell_take(pool), content, &RTYPE);
}
slate_psda *cse_real_lift(slate_psda **pool, slate_psda *q) { return cse_real(pool, q, q); }
slate_psda *cse_real_lo(slate_psda *x) { return cse_cell_payload(cse_content(x)); }
slate_psda *cse_real_hi(slate_psda *x) { return cse_cell_rest(cse_content(x)); }

slate_psda *cse_real_add(slate_psda **p, slate_psda *x, slate_psda *y) {
  if (!cse_type_has(x, &RTYPE) || !cse_type_has(y, &RTYPE)) return 0;
  return cse_real(p, cse_arith_add(p, cse_real_lo(x), cse_real_lo(y)),
                     cse_arith_add(p, cse_real_hi(x), cse_real_hi(y)));
}
