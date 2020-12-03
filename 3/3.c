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

#include <stdio.h>
#include <stdlib.h>

int check_collisions(int slope_x, int slope_y, int length, char *buffer) {
  int count = 0;
  int x = 0;
  int y = 0;

  while (x % 31 + y * 32 <= length) {
    if ('#' == buffer[(x % 31 + y * 32)]) {
      count++;
    }
    x += slope_x;
    y += slope_y;
  }

  return count;
}

int main(int argc, char *args[]) {
  int length;
  char *buffer;
  int part1, p2a, p2b, p2c, p2d;

  // open file
  FILE *file = fopen("input", "r");
  if (!file) {
    printf("File could not be found");
    exit(-1);
  }
  // get length of file
  fseek(file, 0L, SEEK_END);
  length = ftell(file);
  rewind(file);

  // allocate file size to buffer
  buffer = calloc(length, sizeof(char));

  // read file into buffer
  fread(buffer, sizeof(char), length, file);

  part1 = check_collisions(3, 1, length, buffer);
  p2a = check_collisions(1, 1, length, buffer);
  p2b = check_collisions(5, 1, length, buffer);
  p2c = check_collisions(7, 1, length, buffer);
  p2d = check_collisions(1, 2, length, buffer);

  printf("%d\n%d\n%d\n%d\n%d\n%ld", p2a, part1, p2b, p2c, p2d,
         part1 * (long)(p2a * (long)(p2b * (long)(p2c * p2d))));

  free(buffer);
  fclose(file);
}