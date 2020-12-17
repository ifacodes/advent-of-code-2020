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
  while (ptr < input + length) {
    if (*ptr == '\n') {
      passports += keys == 7;
      keys = 0;
      ptr++;  // skip the newline
    }
    if (*ptr != 'c') {  // key is cid
      keys++;
    }
    while ((*ptr != ' ') && (*ptr != '\n')) {
      ptr++;  // skip the value
      if (!*ptr) break;
    }
    ptr++;  // skip the space or newline
  }
  passports += keys == 7;
  printf("%d\n", passports);

  free(input);
}