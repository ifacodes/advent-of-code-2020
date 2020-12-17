/*
=== Advent of Code - 2020 ===
        === Day 7 ===
    by Aoife Bradley

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <inttypes.h>
#include <nmmintrin.h>
#include <stdbool.h>
#include <string.h>

#include "../util/get_filesize.h"

typedef struct {
  char* bag;
  uint32_t contains[8];
} bag;

bag bags[65536] = {0};

uint32_t hasher(char* string) {
  uint32_t crc = 0L;
  for (int i = 0; string[i] != 0; i++) {
    crc = _mm_crc32_u8(crc, string[i]);
  }
  return crc % 65536;
}

bool bagchk(uint32_t hash) {
  // printf("%s -> ", bags[hash].bag);
  bool result = 0;
  if (!strncmp(bags[hash].bag, "shiny gold", 11)) {
    // printf("Found Gold!\n");
    return true;
  }
  // this checks 1, 3, 5, 7 of the 'contains' array, the hash locations
  for (int i = 1; i <= 7; i += 2) {
    int next_hash = bags[hash].contains[i];
    if (next_hash) result = bagchk(next_hash);
    if (result) {
      // printf("Found Gold!\n");
      return true;
    }
  }
  // printf("No More!\n");
  return result;
}

int part2(uint32_t hash) {
  int cnt = 1;
  if (bags[hash].contains[0]) {
    for (int i = 0; i <= 6; i += 2) {
      uint32_t next_hash = bags[hash].contains[i + 1];
      if (next_hash) cnt += bags[hash].contains[i] * part2(next_hash);
    }
  }

  return cnt;
}

int part1() {
  int cnt = 0;
  int forcnt = 0;
  for (int i = 0; i < 65536; i++) {
    if (forcnt == 594) {
      break;
    }
    if (bags[i].bag) {
      forcnt++;
      if (bagchk(i)) cnt++;
    }
  }
  return cnt - 1;
}

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  if (!file) return 0;
  size_t length = get_filesize(file);
  char* input = calloc(length, sizeof(char));
  fread(input, sizeof(char), length, file);
  fclose(file);
  char* ptr = input;
  uint32_t shiny_hash = 0L;
  while (ptr < input + length) {
    char* pos = strstr(ptr, " bags contain");
    if (!pos) continue;
    bag new_bag;
    memset(new_bag.contains, 0, sizeof(new_bag.contains));
    int bag_array_index = 0;
    size_t loc = pos - ptr;
    new_bag.bag = calloc(loc + 1, sizeof(char));
    strncpy(new_bag.bag, ptr, loc);
    uint32_t hash = hasher(new_bag.bag);
    if (!strncmp(new_bag.bag, "shiny gold", 11)) shiny_hash = hash;
    bags[hash] = new_bag;
    ptr += loc + 14;
    if (*ptr == 'n') {
      while (ptr < input + length && *ptr != '\n') ptr += 2;
      if (ptr < input + length && *ptr == '\n') ptr++;
      continue;
    }
    while (ptr < input + length && *ptr != '\n') {
      bags[hash].contains[bag_array_index] = atoi(ptr);
      bag_array_index++;
      ptr += 2;
      pos = ptr;
      while (!(*pos == ',' || *pos == '.')) ++pos;
      loc = pos - 4 - ptr;
      if (ptr[loc] == 'b') loc--;
      char* tmp = calloc(loc + 1, sizeof(char));
      strncpy(tmp, ptr, loc);
      bags[hash].contains[bag_array_index] = hasher(tmp);
      free(tmp);
      bag_array_index++;
      ptr = pos;
      if (ptr + 2 < input + length && *ptr == '.') {
        ptr++;
      } else {
        ptr += 2;
      }
    }
    ptr++;
  }
  printf("Part 1: %d\n", part1());
  printf("Part 2: %d\n", part2(shiny_hash) - 1);
  for (int i = 0; i < 65536; i++) {
    free(bags[i].bag);
  }
  free(input);
}
