/*
=== Advent of Code - 2020 ===
        === Day 8 ===
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** instructions = 0;
bool visited[sizeof(instructions)] = {0};
int32_t acc = 0;
uint32_t line = 0;

void execute() {
  if (visited[line]) return;
  visited[line] = true;
  char* op = calloc(4, sizeof(char));
  strncpy(op, instructions[line], 3);
  char sign = instructions[line][4];
  int step = atoi(instructions[line] + 5);
  printf("operation: %s, sign: %c, step: %d\n", op, sign, step);

  if (!memcmp(op, "acc", 3)) {
    if (sign == '+') {
      acc += step;
    } else {
      acc -= step;
    }
  }
  if (memcmp(op, "jmp", 3)) {
    line++;
  } else {
    if (sign == '+') {
      line += step;
    } else {
      line -= step;
    }
  }
  free(op);
  execute();
}

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  instructions = calloc(1, sizeof(char*));
  // each line is max 8 char + null terminator
  instructions[0] = calloc(9, sizeof(char));
  char buf[10] = {0};
  int i_amount = 0;
  while (fgets(buf, sizeof(buf), file)) {
    buf[strcspn(buf, "\n")] = 0;
    strncpy(instructions[i_amount], buf, 9);
    ++i_amount;
    instructions = realloc(instructions, (i_amount + 1) * sizeof(char*));
    instructions[i_amount] = calloc(9, sizeof(char));
    memset(buf, 0, 9);
  }
  fclose(file);
  execute();
  printf("%d\n", acc);
  for (int i = 0; i <= i_amount; i++) free(instructions[i]);
  free(instructions);
}