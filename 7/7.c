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
#include <string.h>

#include "../util/get_filesize.h"
#include "../util/hashset.h"

typedef struct {
  int amount;
  char* bag_type;
} pair;

// for each line, if the bag isn't in the table, add it.
// for each contained bag, if it isn't in the table add it
// then tell outer bag it contains that bag, and the inner bag it is
// contained by the outer bag

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  size_t length = get_filesize(file);
  char* input = calloc(length, sizeof(char));
  fread(input, sizeof(char), length, file);
  fclose(file);
  char* ptr = input;
  while (ptr < input + length) {
    uint32_t crc = 0L;
    char* pos = strstr(ptr, "bags contain");
    if (pos) {
      while (ptr + 1 != pos) {
        crc = _mm_crc32_u8(crc, *ptr);
        ptr++;
      }
      printf("%" PRIu32 "\n", crc);
      while (ptr < input + length && *ptr != '\n') {
        ptr++;
      }
    }
    ptr++;
  }
  free(input);
}
