/*
=== Advent of Code - 2020 ===
        === Day 5 ===
      by Aoife Bradley

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <inttypes.h>
#include <string.h>

#include "../util/loadfile.h"

int main(int argc, char* args[]) {
  char* input = loadfile("input");
  size_t length = strlen(input);
  char* ptr = input;
  int8_t row = 0;
  int8_t col = 0;
  int16_t seat_id = 0;
  int16_t highest_id = 0;
  int16_t array[960];
  int cnt = 0;
  int cnt2 = 0;
  while (ptr < input + length) {
    if (cnt < 7 && *ptr != 'F') {
      row = row | 1;
    } else if (cnt > 6 && *ptr != 'L') {
      col = col | 1;
    }

    if (cnt < 9 && cnt != 6) {
      if (cnt < 6) {
        row = row << 1;
      } else {
        col = col << 1;
      }
    }
    ptr++;
    cnt++;
    if (cnt == 10) {
      seat_id = row << 3;
      seat_id = seat_id + col;
      if (highest_id < seat_id) {
        highest_id = seat_id;
      }
      array[cnt2] = seat_id;
      row = 0;
      col = 0;
      ptr++;
      cnt = 0;
      cnt2++;
    }
  }

  printf("the highest id is: %d\n", highest_id);

  for (int i = 1; i < 960; i++) {
    for (int j = i; i > 0 && array[j - 1] > array[j]; j--) {
      int16_t tmp = array[j];
      array[j] = array[j - 1];
      array[j - 1] = tmp;
    }
  }
  for (int k = 0; k < 960; k++) {
    if (array[k + 1] != array[k] + 1 && array[k] != 998)
      printf("my seat id is: %d\n", array[k] + 1);
  }
}