/*
=== Advent of Code - 2020 ===
        === Day 6a ===
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
#include <string.h>

#include "../util/loadfile.h"
#include "../util/strtok_mp.h"

int main(int argc, char* args[]) {
  char* input = loadfile("input");
  size_t length = strlen(input);
  char* ptr = input;
  int16_t total = 0;
  bool flag[26] = {0};
  int cnt = 0;
  while (ptr < input + length) {
    for (int i = 'a'; i <= 'z'; i++) {
      if (*ptr == i && !(flag[i - 'a'])) {
        flag[i - 97] = true;
        cnt++;
        break;
      }
    }
    ptr++;
    if (*ptr == '\n' && *(ptr + 1) == '\n') {
      total += cnt;
      cnt = 0;
      memset(flag, 0, sizeof(flag));
      ptr += 2;
    }
  }
  total += cnt;
  printf("\n%d\n", total);

  free(input);
}