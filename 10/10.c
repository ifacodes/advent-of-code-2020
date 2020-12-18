/*
=== Advent of Code - 2020 ===
        === Day 10 ===
      by Aoife Bradley

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTLET_RATING 0

void part1(int list[], int length) {
  int onejoltcnt = 0;
  int threejoltcnt = 0;
  int cur_cmp = 0;

  for (int i = 0; i < length; ++i) {
    if (list[i] - cur_cmp == 1)
      printf("previous: %d, current: %d, new 1 jolt diff: %d\n", cur_cmp,
             list[i], ++onejoltcnt);
    if (list[i] - cur_cmp == 3)
      printf("previous: %d, current: %d, new 3 jolt diff: %d\n", cur_cmp,
             list[i], ++threejoltcnt);
    cur_cmp = list[i];
  }

  printf(
      "1 Jolt Difference Amount: %d, 3 Jolt Difference Amount: %d, Multipled: "
      "%d\n",
      onejoltcnt, threejoltcnt, onejoltcnt * ++threejoltcnt);
}

int main(int argc, char *args[]) {
  FILE *file = fopen("input", "r");
  if (!file) return 1;

  int list_length = 1;
  int *ratings_list = calloc(list_length, sizeof(int));

  char buf[5] = {0};

  while (fgets(buf, 5, file)) {
    ratings_list[list_length - 1] = atoi(buf);
    ratings_list = realloc(ratings_list, ++list_length * sizeof(int));
    memset(buf, 0, 4);
  }
  list_length--;

  for (int i = 1; i < list_length; i++) {
    for (int j = i; j > 0 && ratings_list[j - 1] > ratings_list[j]; j--) {
      int tmp = ratings_list[j];
      ratings_list[j] = ratings_list[j - 1];
      ratings_list[j - 1] = tmp;
    }
  }

  part1(ratings_list, list_length);
  free(ratings_list);
  fclose(file);
}