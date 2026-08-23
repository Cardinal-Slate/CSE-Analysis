/// cse/analysis.h — the Analysis domain: the reals ℝ as certified enclosures [lo, hi], type-first. A value
/// is a psda carrying the Real type (tag 'R'): payload = lo, rest = hi, each a ℚ bound. It stacks
/// concretely on Arith — the bound arithmetic is cse_arith_* — and names its type: cse_real_add takes Real
/// carriers, checked (cse_type_has). No field is supplied; the method is the type, and the type restricts
/// the carrier. Stacks on the spine + CSE-DSA + CSE-Types + CSE-Arith.
/// SPDX-License-Identifier: MIT OR Apache-2.0
#pragma once
#include "slate/psda.h"

/// the Real type — the tag a value must order level with to be accepted.
slate_psda *cse_real_type(void);

slate_psda *cse_real(slate_psda **pool, slate_psda *lo, slate_psda *hi);
slate_psda *cse_real_lift(slate_psda **pool, slate_psda *q);
slate_psda *cse_real_lo(slate_psda *x);
slate_psda *cse_real_hi(slate_psda *x);

/// interval addition: [a,b] + [c,d] = [a+c, b+d]. Operands must be Reals, or nothing.
slate_psda *cse_real_add(slate_psda **pool, slate_psda *x, slate_psda *y);
