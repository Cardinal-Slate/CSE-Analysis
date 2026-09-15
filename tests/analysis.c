/* tests/analysis.c — reals as rational enclosures, type-first. No field is wired; Analysis stacks on Arith
   directly, and a value carries the Real tag. The op refuses a foreign carrier.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include <stdio.h>
#include "cse/analysis.h"
#include "cse/arith.h"
#include "cse/types.h"
#include "prime.h"
#include "slate/psda.h"

static int fails = 0;
#define CHECK(c, m) do { if (!(c)) { printf("  FAIL %s\n", (m)); fails++; } } while (0)

static slate_psda arena[4096];
static slate_psda *pool;
static void pool_init(void) { int i; for (i = 0; i < 4095; i++) arena[i].next = &arena[i + 1]; arena[4095].next = 0; pool = &arena[0]; }

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
  CHECK(bounds(cse_real_add(&pool, sqrt2, sqrt2), 2, 1, 3, 1), "√2 + √2 ∈ [2, 3]");
  CHECK(bounds(cse_real_add(&pool, cse_real_lift(&pool, Qv(1,2)), cse_real_lift(&pool, Qv(1,3))), 5, 6, 5, 6),
        "1/2 + 1/3 = [5/6, 5/6]");

  /* type-first: a value has the Real tag, and add restricts its carrier to Reals */
  CHECK(cse_type_has(sqrt2, cse_real_type()) != 0, "a value has type Real");
  CHECK(cse_real_add(&pool, Qv(1,1), sqrt2) == 0, "add refuses a ℚ where a Real is required");

  printf(fails ? "analysis: FAIL\n" : "analysis: ok\n");
  return fails ? 1 : 0;
}
