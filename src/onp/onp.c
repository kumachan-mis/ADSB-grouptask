// S. Wu, U. Manber, and G. Myers. An O(NP) sequence comparison algorithm. Information Processing Letter. 35(6) 317-332 (1990)
// https://www.janelia.org/our-research/former-labs/myers-lab
#include <stdio.h>
#include <string.h>

static inline int max(const int x, const int y) {
  return (x > y) ? x : y;
}

int snake(const char* str1, const char* str2, int len1, int len2, int x, int y) {
  while (x < len1 && y < len2 && str1[x] == str2[y]) {
    x++;
    y++;
  }
  return y;
}

int levenshtein_onp(const char* M, const char* N, const int lm, const int ln) {
  if (lm > ln) return levenshtein_onp(N, M, ln, lm);

  int fp[lm + ln + 1];
  int offset = lm + 1;
  int delta = ln - lm;
  int i, p, k;

  for (i = 0; i < lm + ln + 1; i++) {
    fp[i] = -1;
  }

  for (p = 0; fp[delta + offset] != ln; p++) {
    for (k = -p; k < delta; k++) {
      fp[k + offset] = snake(M, N, lm, ln, k, max(fp[k + 1 + offset], fp[k - 1 + offset] + 1));
    }

    for (k = delta + p; k > delta; k--) {
      fp[k + offset] = snake(M, N, lm, ln, k, max(fp[k + 1 + offset], fp[k - 1 + offset] + 1));
    }

    fp[delta + offset] = snake(M, N, lm, ln, delta, max(fp[delta + 1 + offset], fp[delta - 1 + offset] + 1));
  }
  return delta + (p - 1);
}

int main(void) {
  char* M = "kntnisshit";
  char* N = "kntnlove";
  int lm = strlen(M);
  int ln = strlen(N);
  printf("%d\n", levenshtein_onp(M, N, lm, ln));
  return 0;
}
