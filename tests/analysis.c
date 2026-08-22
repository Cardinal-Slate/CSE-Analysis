/* tests/analysis.c — wiring: Analysis (generic) + Arith (a field) = reals as rational enclosures.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include <stdio.h>
#include "cse/analysis.h"
#include "cse/field.h"
#include "cse/arith.h"
#include "prime.h"
#include "slate/psda.h"

static int fails = 0;
#define CHECK(c, m) do { if (!(c)) { printf("  FAIL %s\n", (m)); fails++; } } while (0)

static const cse_field Q = {
  cse_arith_add, cse_arith_sub, cse_arith_mul, cse_arith_neg, cse_arith_inv, cse_arith_div
};

static slate_psda arena[1024];
static slate_psda *pool;
static void pool_init(void) { int i; for (i = 0; i < 1023; i++) arena[i].next = &arena[i + 1]; arena[1023].next = 0; pool = &arena[0]; }

#define Qv(n,d) cse_arith_val(&pool, (n), (d))
static int bounds(slate_psda *x, long ln, long ld, long hn, long hd) {
  long n, d;
  cse_arith_read(cse_real_lo(x), &n, &d); if (n != ln || d != ld) return 0;
  cse_arith_read(cse_real_hi(x), &n, &d); return n == hn && d == hd;
}

int main(void) {
  pool_init();

  CHECK(bounds(cse_real_lift(&pool, Qv(1, 2)), 1, 2, 1, 2), "lift(1/2) = [1/2, 1/2]");

  slate_psda *sqrt2 = cse_real(&pool, Qv(1, 1), Qv(3, 2));
  CHECK(bounds(sqrt2, 1, 1, 3, 2), "√2 ∈ [1, 3/2] (an enclosure of rationals)");
  CHECK(bounds(cse_real_add(&Q, &pool, sqrt2, sqrt2), 2, 1, 3, 1), "√2 + √2 ∈ [2, 3]");
  CHECK(bounds(cse_real_add(&Q, &pool, cse_real_lift(&pool, Qv(1,2)), cse_real_lift(&pool, Qv(1,3))), 5, 6, 5, 6),
        "1/2 + 1/3 = [5/6, 5/6]");

  printf(fails ? "analysis: FAIL\n" : "analysis: ok\n");
  return fails ? 1 : 0;
}
