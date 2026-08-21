/// cse/analysis.h — the Analysis domain: ℝ. Field + completeness + the transcendental functions.
/// SPDX-License-Identifier: MIT OR Apache-2.0
///
/// Analysis stacks on Field. Two things distinguish the reals from the rationals:
///
///  1. Completeness — a real is a *certified bracket*: a compose(lo, hi) that provably contains the true
///     value, refined until its width ≤ 2⁻ᵖ. That is structure, not a receipt — the enclosure IS the
///     value's evidence, read straight off its composition. (See README.)
///  2. The transcendentals — √, exp, ln, sin, cos, atan, and the constants π, e. These are NOT defined by
///     a series here; a series is a *provider's* method. They are defined by their **functional
///     equations** — the same way + and × are defined by the ring axioms. exp is whatever satisfies
///     exp(0)=1 and exp(a+b)=exp(a)·exp(b); a provider (CSE-Refine) is correct iff it upholds them.
///
/// Operations build structure and compute nothing; `≡` is the spine's order at level; reduction is a
/// provider's job.
#pragma once
#include "slate/psda.h"
#include "cse/field.h"   /* Analysis = Field + completeness + transcendentals */

/// The transcendental operation atoms and the two constants.
extern slate_reading cse_analysis_sqrt_op;
extern slate_reading cse_analysis_exp_op;
extern slate_reading cse_analysis_ln_op;
extern slate_reading cse_analysis_sin_op;
extern slate_reading cse_analysis_cos_op;
extern slate_reading cse_analysis_atan_op;
extern slate_reading cse_analysis_pi;    /* π */
extern slate_reading cse_analysis_e;     /* e */

/// The operations — each builds a composition drawn from `pool`; none computes.
slate_psda *cse_analysis_sqrt(slate_psda **pool, slate_psda *a);
slate_psda *cse_analysis_exp (slate_psda **pool, slate_psda *a);
slate_psda *cse_analysis_ln  (slate_psda **pool, slate_psda *a);
slate_psda *cse_analysis_sin (slate_psda **pool, slate_psda *a);
slate_psda *cse_analysis_cos (slate_psda **pool, slate_psda *a);
slate_psda *cse_analysis_atan(slate_psda **pool, slate_psda *a);
slate_psda *cse_analysis_pi_val(slate_psda **pool);
slate_psda *cse_analysis_e_val (slate_psda **pool);

/// Equivalence — the spine's order at level (reduction supplied by a provider).
slate_psda *cse_analysis_eq(slate_psda *x, slate_psda *y);

/// ─── the invariants: the functional equations that define the transcendentals ───────────────────────
///   sqrt_sq   √a · √a ≡ a
///   exp_zero  exp(0) ≡ 1
///   exp_add   exp(a+b) ≡ exp(a) · exp(b)
///   ln_exp    ln(exp(a)) ≡ a
///   pyth      sin(a)² + cos(a)² ≡ 1
///   e_def     e ≡ exp(1)
///   pi_def    cos(π) ≡ −1
slate_psda *cse_analysis_sqrt_sq (slate_psda **s, slate_psda *a);
slate_psda *cse_analysis_exp_zero(slate_psda **s);
slate_psda *cse_analysis_exp_add (slate_psda **s, slate_psda *a, slate_psda *b);
slate_psda *cse_analysis_ln_exp  (slate_psda **s, slate_psda *a);
slate_psda *cse_analysis_pyth    (slate_psda **s, slate_psda *a);
slate_psda *cse_analysis_e_def   (slate_psda **s);
slate_psda *cse_analysis_pi_def  (slate_psda **s);
