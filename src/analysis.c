/* src/analysis.c — the Analysis domain: the transcendentals defined by their functional equations.
   SPDX-License-Identifier: MIT OR Apache-2.0

   Each transcendental builds a composition; its meaning is the equations below — exp is whatever obeys
   exp(0)=1 and exp(a+b)=exp(a)·exp(b); √ is whatever squares back to its argument; and so on. The ring/
   field operations come from Arith/Field. Equivalence is the spine's order at level; the refinement that
   makes these hold on real values is a provider's job (CSE-Refine). */
#include "cse/analysis.h"
#include "cse/dsa/cell.h"

static slate_psda *un(slate_psda **pool, slate_reading op, slate_psda *a) {
  return cse_cell(cse_cell_take(pool), a, 0, op);
}
static slate_psda *konst(slate_psda **pool, slate_reading k) {
  slate_psda *c = cse_cell_take(pool); c->potential = k; c->prev = 0; c->next = 0; return c;
}

slate_psda *cse_analysis_sqrt(slate_psda **p, slate_psda *a) { return un(p, cse_analysis_sqrt_op, a); }
slate_psda *cse_analysis_exp (slate_psda **p, slate_psda *a) { return un(p, cse_analysis_exp_op,  a); }
slate_psda *cse_analysis_ln  (slate_psda **p, slate_psda *a) { return un(p, cse_analysis_ln_op,   a); }
slate_psda *cse_analysis_sin (slate_psda **p, slate_psda *a) { return un(p, cse_analysis_sin_op,  a); }
slate_psda *cse_analysis_cos (slate_psda **p, slate_psda *a) { return un(p, cse_analysis_cos_op,  a); }
slate_psda *cse_analysis_atan(slate_psda **p, slate_psda *a) { return un(p, cse_analysis_atan_op, a); }
slate_psda *cse_analysis_pi_val(slate_psda **p) { return konst(p, cse_analysis_pi); }
slate_psda *cse_analysis_e_val (slate_psda **p) { return konst(p, cse_analysis_e); }

slate_psda *cse_analysis_eq(slate_psda *x, slate_psda *y) {
  return (slate_order(x, y).potential == slate_level()) ? x : 0;
}

/* √a · √a ≡ a */
slate_psda *cse_analysis_sqrt_sq(slate_psda **s, slate_psda *a) {
  slate_psda *r = cse_analysis_sqrt(s, a);
  return cse_analysis_eq(cse_arith_mul(s, r, r), a);
}
/* exp(0) ≡ 1 */
slate_psda *cse_analysis_exp_zero(slate_psda **s) {
  return cse_analysis_eq(cse_analysis_exp(s, cse_arith_zero_val(s)), cse_arith_one_val(s));
}
/* exp(a+b) ≡ exp(a) · exp(b) */
slate_psda *cse_analysis_exp_add(slate_psda **s, slate_psda *a, slate_psda *b) {
  return cse_analysis_eq(cse_analysis_exp(s, cse_arith_add(s, a, b)),
                         cse_arith_mul(s, cse_analysis_exp(s, a), cse_analysis_exp(s, b)));
}
/* ln(exp(a)) ≡ a */
slate_psda *cse_analysis_ln_exp(slate_psda **s, slate_psda *a) {
  return cse_analysis_eq(cse_analysis_ln(s, cse_analysis_exp(s, a)), a);
}
/* sin(a)² + cos(a)² ≡ 1 */
slate_psda *cse_analysis_pyth(slate_psda **s, slate_psda *a) {
  slate_psda *si = cse_analysis_sin(s, a), *co = cse_analysis_cos(s, a);
  return cse_analysis_eq(cse_arith_add(s, cse_arith_mul(s, si, si), cse_arith_mul(s, co, co)),
                         cse_arith_one_val(s));
}
/* e ≡ exp(1) */
slate_psda *cse_analysis_e_def(slate_psda **s) {
  return cse_analysis_eq(cse_analysis_e_val(s), cse_analysis_exp(s, cse_arith_one_val(s)));
}
/* cos(π) ≡ −1 */
slate_psda *cse_analysis_pi_def(slate_psda **s) {
  return cse_analysis_eq(cse_analysis_cos(s, cse_analysis_pi_val(s)),
                         cse_arith_neg(s, cse_arith_one_val(s)));
}
