/*
=== Advent of Code - 2020 ===
        === Day 1 ===
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

#include "../util/hashset.h"

int main(int argc, char *args[]) {
  element *set = calloc(1024, sizeof(element));

  // number array
  int list[199];
  int count = 0;

  // tmp line alllocation
  char line[6];
  // open input file
  FILE *fp = fopen("input", "r");

  if (!fp) {
    printf("no file error!");
    exit(-1);
  }
  // input into hashset
  while (fgets(line, sizeof(line), fp)) {
    // remove carriage return and newline
    line[strcspn(line, "\r\n")] = 0;
    // add to number array for later querying
    list[count] = atoi(line);
    // convert to integer from string and add to hashset
    hashset_add(set, list[count]);
    count++;
  }
  fclose(fp);

  // loop through and find the number equal to the hash of 2020 - current number
  // in list
  for (int i = 0; i < 199; i++) {
    int result = hashset_find(set, 2020 - list[i]);
    if (result != 1) {
      printf("%d\n", result);
    }
  }

  printf("PART TWO \n\n");

  // subtract a number in list from 2020 then loop the list and
  // return if a loop number subtracted from that first number exists
  for (int j = 0; j < 199; j++) {
    int num1 = 2020 - list[j];
    for (int k = 0; k < 199; k++) {
      int result = hashset_find(set, num1 - list[k]);
      if (result != 1) {
        printf("num1: %d\nnum2: %d\nnum3: %d\nmultiple: %d\n\n", list[j],
               list[k], result, list[j] * list[k] * result);
        break;
      }
    }
  }
  hashset_free(set);
  return 0;
}
