/*
=== Advent of Code - 2020 ===
        === Day 4 ===
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

#include "../util/loadfile.h"
#include "../util/strtok_mp.h"

typedef struct passport {
  uint32_t byr;
  uint32_t iyr;
  uint32_t eyr;
  char* hgt;
  char* hcl;
  char* ecl;
  uint32_t pid;
  uint32_t cid;
} passport;

typedef struct pair {
  char* key;
  char* value;
} pair;

uint32_t get_amount(char* data) {
  char* tmp = data;
  uint32_t count;
  while ((tmp = strstr(tmp, "\n\n"))) {
    count++;
    tmp += 2;
  }
  return count;
}

void print_passport(passport* p) {
  uint32_t byr = p->byr;
  uint32_t iyr = p->iyr;
  uint32_t eyr = p->eyr;
  char* hgt = p->hgt;
  char* hcl = p->hcl;
  char* ecl = p->ecl;
  uint32_t pid = p->pid;
  uint32_t cid = p->cid;
  printf("byr:%d\niyr:%d\neyr:%d\nhgt:%s\nhcl:%s\necl:%s\npid:%" PRIu32
         "\ncid:%d\n\n",
         byr, iyr, eyr, hgt, hcl, ecl, pid, cid);
}

passport* data_to_passport(char* data) {
  passport* new = calloc(1, sizeof(passport));

  pair* data_array = calloc(8, sizeof(pair));
  int count = 0;
  char* prop;
  prop = strtok(data, ":\n ");
  do {
    data_array[count].key = prop;
    prop = strtok(NULL, ":\n ");
    data_array[count].value = prop;
    prop = strtok(NULL, ":\n ");
    count++;
  } while (prop);

  for (int i = 0; i < count; i++) {
    if (strcmp(data_array[i].key, "byr") == 0) {
      new->byr = atoi(data_array[i].value);
    }
    if (strcmp(data_array[i].key, "iyr") == 0) {
      new->iyr = atoi(data_array[i].value);
    }
    if (strcmp(data_array[i].key, "eyr") == 0) {
      new->eyr = atoi(data_array[i].value);
    }
    if (strcmp(data_array[i].key, "hgt") == 0) {
      new->hgt = data_array[i].value;
    }
    if (strcmp(data_array[i].key, "hcl") == 0) {
      new->hcl = data_array[i].value;
    }
    if (strcmp(data_array[i].key, "ecl") == 0) {
      new->ecl = data_array[i].value;
    }
    if (strcmp(data_array[i].key, "pid") == 0) {
      new->pid = (unsigned)atoi(data_array[i].value);
    }
    if (strcmp(data_array[i].key, "cid") == 0) {
      new->cid = atoi(data_array[i].value);
    }
  }
  // pruint32_t_passport(new);
  free(data_array);
  return new;
}

passport* get_passport_array(char* input, char* delimiter) {
  uint32_t count = 0;
  char* token;
  char* buffer = '\0';
  passport* array = calloc(10 * 1024, sizeof(passport));
  token = strtok_mp(input, "\n\n", &buffer);

  while (token) {
    // pruint32_tf("%s\nBREAK\n", token);
    array[count] = *data_to_passport(token);
    // pruint32_tf("%s\nBREAK\n", token);
    token = strtok_mp(NULL, "\n\n", &buffer);
    // pruint32_tf("\n");
    count++;
  }

  return array;
}

int main(int argc, char* args[]) {
  char* file = loadfile("input");
  int amount = 286;
  passport* passport_array = get_passport_array(file, "\n\n");
  int count = 0;

  for (int i = 0; i < amount; i++) {
    print_passport(&passport_array[i]);
    if (passport_array[i].byr && passport_array[i].eyr &&
        passport_array[i].iyr && passport_array[i].hgt &&
        passport_array[i].hcl && passport_array[i].ecl &&
        passport_array[i].pid) {
      printf("Passport #%d is valid.\n", i);
      printf("Valid passwords = %d\n", count++);
    }
  }
  printf("%d", count);
}