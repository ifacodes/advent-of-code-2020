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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/get_filesize.h"

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  if (!file) return 0;
  size_t length = get_filesize(file);
  char* input = calloc(length, sizeof(char));
  fread(input, sizeof(char), length, file);
  fclose(file);
  char* ptr = input;
  int passports = 0;
  int keys = 0;
  char buf[9];
  while (ptr < input + length) {
    if (*ptr == '\n') {
      passports += keys == 7;
      keys = 0;
      ptr++;  // skip the newline
    }
    buf[8] = 0;
    memcpy(buf, ptr, 3);
    if (!memcmp(buf, "byr", 3)) {
      memcpy(buf, ptr + 4, 4);
      buf[4] = '\0';
      int year = atoi(buf);
      if (year >= 1920 && year <= 2002) keys++;
      ptr += 3;  // skip key and colon
    }
    if (!memcmp(buf, "iyr", 3)) {
      memcpy(buf, ptr + 4, 4);
      buf[4] = '\0';
      int year = atoi(buf);
      if (year >= 2010 && year <= 2020) keys++;
      ptr += 3;  // skip key and colon
    }
    if (!memcmp(buf, "eyr", 3)) {
      memcpy(buf, ptr + 4, 4);
      buf[4] = '\0';
      int year = atoi(buf);
      if (year >= 2020 && year <= 2030) keys++;
      ptr += 3;  // skip key and colon
    }
    if (!memcmp(buf, "hgt", 3)) {
      if (*(ptr + 7) == 'c') {
        memcpy(buf, ptr + 4, 3);
        buf[3] = '\0';
        int hgt = atoi(buf);
        if (hgt >= 150 && hgt <= 193) keys++;
      } else {
        memcpy(buf, ptr + 4, 2);
        int hgt = atoi(buf);
        if (hgt >= 59 && hgt <= 76) keys++;
      }
      ptr += 3;  // skip key and colon
    }
    if (!memcmp(buf, "hcl", 3)) {
      if (*(ptr + 4) == '#') {
        memcpy(buf, ptr + 5, 6);
        for (int i = 0; i < 6; ++i) {
          if (!((buf[i] >= '0' && buf[i] <= '9') ||
                (buf[i] >= 'a' && buf[i] <= 'f'))) {
            break;
          }
        }
        keys++;
      }
      ptr += 3;  // skip key and colon
    }
    if (!memcmp(buf, "ecl", 3)) {
      if (!(memcmp(ptr + 4, "amb", 3)) || !(memcmp(ptr + 4, "blu", 3)) ||
          !(memcmp(ptr + 4, "brn", 3)) || !(memcmp(ptr + 4, "gry", 3)) ||
          !(memcmp(ptr + 4, "grn", 3)) || !(memcmp(ptr + 4, "hzl", 3)) ||
          !(memcmp(ptr + 4, "oth", 3)))
        keys++;
      ptr += 3;  // skip key and colon
    }
    if (memcmp(buf, "pid", 3) == 0) {
      char* pid = ptr + 4;
      int cnt = 0;
      while (*pid >= '0' && *pid <= '9') {
        cnt++;
        pid++;
      }
      if (cnt == 9) keys++;
      ptr += 3;  // skip key and colon
    }
    while ((*ptr != ' ') && (*ptr != '\n')) {
      ptr++;  // skip the value
      if (!*ptr) break;
    }
    ptr++;
  }
  printf("%d\n", passports);
  free(input);
}