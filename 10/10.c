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

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void part1(int list[], int length) {
  int onejoltcnt = 0;
  int threejoltcnt = 0;  // starts at 1 to account for the 3 jolt diff between
                         // final adapter and phone
  int cur_cmp = 0;

  for (int i = 1; i < length; ++i) {
    if (list[i] - cur_cmp == 1) {
      ++onejoltcnt;
    } else {
      ++threejoltcnt;
    }
    cur_cmp = list[i];
  }

  printf(
      "1 Jolt Difference Amount: %d, 3 Jolt Difference Amount: %d, Multipled: "
      "%d\n",
      onejoltcnt, threejoltcnt, onejoltcnt * threejoltcnt);
}

void part2(int list[], int length) {
  int essential_amount = 2;
  int *essential_workers = calloc(essential_amount, sizeof(int));
  for (int i = 0; i < length; ++i) {
    if (list[i + 1] - list[i - 1] > 3) {
      essential_workers[essential_amount - 1] = i;
      essential_workers =
          realloc(essential_workers, ++essential_amount * sizeof(int));
    }
  }
  essential_amount--;
  // find each sections possiblity count
}

int main(int argc, char *args[]) {
  FILE *file = fopen("input", "r");
  if (!file) return 1;
  int list_length = 2;
  int *ratings_list = calloc(list_length, sizeof(int));

  char buf[5] = {0};

  while (fgets(buf, 5, file)) {
    ratings_list[list_length - 1] = atoi(buf);
    ratings_list = realloc(ratings_list, ++list_length * sizeof(int));
    memset(buf, 0, 4);
  }
  list_length--;
  for (int i = 0; i < list_length; i++) {
    for (int j = i; j > 0 && ratings_list[j - 1] > ratings_list[j]; j--) {
      int tmp = ratings_list[j];
      ratings_list[j] = ratings_list[j - 1];
      ratings_list[j - 1] = tmp;
    }
  }
  ratings_list[list_length] = ratings_list[list_length - 1] + 3;
  list_length++;
  for (int k = 0; k < list_length; ++k) printf("%d\n", ratings_list[k]);

  part1(ratings_list, list_length);
  part2(ratings_list, list_length);
  free(ratings_list);
  fclose(file);
}