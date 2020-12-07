/*
=== Advent of Code - 2020 ===
        === Day 6b ===
      by Aoife Bradley

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../util/get_filesize.h"

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  size_t length = get_filesize(file);
  char* input = calloc(length, sizeof(char));
  fread(input, sizeof(char), length, file);
  fclose(file);
  char* ptr = input;
  int16_t total = 0;
  bool prev_flag[26] = {0};
  bool curr_flag[26] = {0};
  bool first_line = true;
  int cnt = 0;
  int last_cnt = 0;
  while (ptr < input + length) {
    for (int i = 'a'; i <= 'z'; i++) {
      if (first_line) {
        if (*ptr == i && !(curr_flag[i - 'a'])) {
          curr_flag[i - 'a'] = true;
          cnt++;
          break;
        }
      } else {
        if (*ptr == i && prev_flag[i - 'a']) {
          curr_flag[i - 'a'] = true;
          cnt++;
          break;
        }
      }
    }
    if (*ptr == '\n') {
      memcpy(prev_flag, curr_flag, sizeof(curr_flag));
      memset(curr_flag, 0, sizeof(curr_flag));
      if (first_line) first_line = false;
      last_cnt = cnt;
      cnt = 0;
    }
    if (*ptr == '\n' && *(ptr + 1) == '\n') {
      total += last_cnt;
      last_cnt = 0;
      memset(prev_flag, 0, sizeof(prev_flag));
      first_line = true;
      ptr += 2;
    } else {
      ptr++;
    }
  }
  total += cnt;
  printf("%d\n", total);
  free(input);
}