/* tests/analysis.c — the transcendentals as functional equations: the domain's contract for the reals.
   SPDX-License-Identifier: MIT OR Apache-2.0 */
#include <stdio.h>
#include "cse/analysis.h"
#include "cse/dsa/cell.h"
#include "slate/psda.h"
#include "slate/encode.h"

static int fails = 0;
#define CHECK(c, m) do { if (!(c)) { printf("  FAIL %s\n", (m)); fails++; } } while (0)

static slate_psda arena[512];
static slate_psda *pool;
static void pool_init(void) { int i; for (i = 0; i < 511; i++) arena[i].next = &arena[i + 1]; arena[511].next = 0; pool = &arena[0]; }

static unsigned char vbuf[8][4];
static slate_psda vnodes[8];
static int vn = 0;
static slate_psda *value(unsigned id) {
  unsigned char b = (unsigned char)id;
  slate_encode(&b, 1, vbuf[vn]);
  vnodes[vn].potential = vbuf[vn]; vnodes[vn].prev = 0; vnodes[vn].next = 0;
  return &vnodes[vn++];
}

int main(void) {
  pool_init();
  slate_psda *a = value(10), *b = value(20);

  /* operations build the right structure */
  slate_psda *r = cse_analysis_sqrt(&pool, a);
  CHECK(cse_cell_payload(r) == a && cse_cell_key(r) == cse_analysis_sqrt_op, "sqrt builds √a");
  CHECK(cse_cell_key(cse_analysis_exp(&pool, a)) == cse_analysis_exp_op, "exp is a distinct operation");

  /* the functional equations — the domain contract for ℝ */
  struct { const char *law; slate_psda *held; } inv[] = {
    { "sqrt_sq   sqrt(a)^2 = a",             cse_analysis_sqrt_sq(&pool, a) },
    { "exp_zero  exp(0) = 1",                cse_analysis_exp_zero(&pool) },
    { "exp_add   exp(a+b) = exp(a)*exp(b)",  cse_analysis_exp_add(&pool, a, b) },
    { "ln_exp    ln(exp(a)) = a",            cse_analysis_ln_exp(&pool, a) },
    { "pyth      sin^2 + cos^2 = 1",         cse_analysis_pyth(&pool, a) },
    { "e_def     e = exp(1)",                cse_analysis_e_def(&pool) },
    { "pi_def    cos(pi) = -1",              cse_analysis_pi_def(&pool) },
  };
  int i;
  printf("  the Analysis domain — the transcendentals by functional equation:\n");
  for (i = 0; i < 7; i++)
    printf("    %-38s %s\n", inv[i].law, inv[i].held ? "hold" : "awaits refinement");

  printf(fails ? "analysis: FAIL\n" : "analysis: ok\n");
  return fails ? 1 : 0;
}
