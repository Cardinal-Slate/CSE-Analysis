/// cse/analysis.h — the Analysis domain: the reals ℝ as certified enclosures [lo, hi] over a component
/// field. Generic over cse_field — it never names its component. Supply Arith and the bounds are
/// rationals. Interval arithmetic composed from the field's operations. Stacks on spine + CSE-DSA + the
/// field interface. SPDX-License-Identifier: MIT OR Apache-2.0
#pragma once
#include "slate/psda.h"
#include "cse/field.h"

slate_psda *cse_real(slate_psda **pool, slate_psda *lo, slate_psda *hi);
slate_psda *cse_real_lift(slate_psda **pool, slate_psda *q);
slate_psda *cse_real_lo(slate_psda *x);
slate_psda *cse_real_hi(slate_psda *x);

/// interval addition over the field F: [a,b] + [c,d] = [a+c, b+d].
slate_psda *cse_real_add(const cse_field *F, slate_psda **pool, slate_psda *x, slate_psda *y);
