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

int main(int argc, char* args[]) {
  char* file = loadfile("input");
  char* ptr = file;
  int passports = 0;
  int keys = 0;
  int length = strlen(file);
  while (ptr < file + length) {
    if (*ptr != 'c') {  // key is cid
      keys++;
    }
    while ((*ptr != ' ') && (*ptr != '\n')) {
      ptr++;  // skip the value
      if (!*ptr) break;
    }
    ptr++;  // skip the space or newline
    if (*ptr == '\n') {
      passports += keys == 7;
      keys = 0;
      ptr++;  // skip the newline
    }
  }
  passports += keys == 7;
  printf("%d\n", passports);
}