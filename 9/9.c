/*
=== Advent of Code - 2020 ===
        === Day 9 ===
      by Aoife Bradley

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool is_sum(long array[], int index) {
  long preamble_array[25] = {0};

  for (int k = 0; k < 25; ++k) {
    preamble_array[k] = array[index - k - 1];
  }

  for (int i = 0; i < 25; ++i) {
    long to_match = array[index] - preamble_array[i];
    for (int j = 0; j < 25; ++j) {
      if (j != i && to_match == preamble_array[j]) return true;
    }
  }

  return false;
}

long get_weakness(int data_length, long array[], long key) {
  for (int i = 0; i < data_length; ++i) {
    long sum = array[i];
    long smallest = array[i];
    long largest = array[i];
    for (int j = i + 1; j < data_length; ++j) {
      if (sum > key) break;
      if (sum == key) return smallest + largest;
      sum += array[j];
      if (array[j] < smallest) smallest = array[j];
      if (array[j] > largest) largest = array[j];
    }
  }
  return 0;
}

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  if (!file) return 0;

  int data_length = 1;
  long* xmas_data = calloc(data_length, sizeof(long));
  char buf[20] = {0};

  while (fgets(buf, 20, file)) {
    long num = atol(buf);
    xmas_data[data_length - 1] = num;
    xmas_data = realloc(xmas_data, ++data_length * sizeof(long));
    memset(buf, 0, 20);
  }
  fclose(file);

  for (int i = 25; i < data_length; ++i) {
    if (!is_sum(xmas_data, i)) {
      printf("%ld is the first non-valid number.\n", xmas_data[i]);
      printf("%ld is the encryption weakness.\n",
             get_weakness(data_length, xmas_data, xmas_data[i]));
      break;
    }
  }

  free(xmas_data);
}