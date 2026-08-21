# CSE-Analysis

The **analysis domain** for Cardinal-Slate — the reals `ℝ`. Two things separate the reals from the
rationals, and CSE-Analysis states both:

1. **Completeness.** A real is a *certified bracket* — a `compose(lo, hi)` that provably contains the
   true value, refined until its width ≤ 2⁻ᵖ. That enclosure **is** the value's evidence, read straight
   off its composition — there is no separate receipt. Order (`slate_order`) decides containment;
   `nothing outstanding lies level`, so an unrefined value is simply not-yet-decided.

2. **The transcendentals** — `√ exp ln sin cos atan` and the constants `π, e`. These are **not** defined
   by a series here. A series is a *provider's method*. They are defined by their **functional
   equations**, exactly as `+` and `×` are defined by the ring axioms:

```
sqrt_sq   √a · √a ≡ a
exp_zero  exp(0) ≡ 1
exp_add   exp(a+b) ≡ exp(a) · exp(b)
ln_exp    ln(exp(a)) ≡ a
pyth      sin(a)² + cos(a)² ≡ 1
e_def     e ≡ exp(1)
pi_def    cos(π) ≡ −1
```

`exp` is whatever satisfies `exp(0)=1` and `exp(a+b)=exp(a)·exp(b)`; a provider (CSE-Refine) is correct
iff it upholds these. The operations build structure; `≡` is the spine's `order` at `level`; reduction
(interval refinement) is the provider's job.

## Role

Depends on the spine, CSE-DSA, CSE-Arith, and CSE-Field. Third rung of `N ⊂ Z ⊂ Q ⊂ R ⊂ C`; Complex
stacks on top.

## Build

```
make          gate + standalone header + the functional-equation report, then libcse-analysis.a
make check    the gate and the test only
```

Deps first: `make -C ../CardinalSlate lib && make -C ../CSE-DSA lib && make -C ../CSE-Arith lib && make -C ../CSE-Field lib`.

## License

MIT OR Apache-2.0.
