/*
=== Advent of Code - 2020 ===
        === Day 8b ===
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

bool execute(char** program, int line_amount, int32_t* final_acc) {
  bool visited[1000] = {0};
  uint32_t line = 0;
  while (!visited[line] && line < line_amount) {
    char* op = calloc(4, sizeof(char));
    strncpy(op, program[line], 3);
    char sign = program[line][4];
    int step = atoi(program[line] + 5);
    visited[line] = true;
    printf("operation: %s, sign: %c, step: %d\n", op, sign, step);

    if (!memcmp(op, "acc", 3)) {
      if (sign == '+') {
        *final_acc += step;
      } else {
        *final_acc -= step;
      }
      line++;
    }
    if (!memcmp(op, "jmp", 3)) {
      if (sign == '+') {
        line += step;
      } else {
        line -= step;
      }
    }
    if (!memcmp(op, "nop", 3)) {
      line++;
    }
    free(op);
  }
  return line >= line_amount ? true : false;
}

int part2(char** program, int line_amount) {
  char** this_program = calloc(line_amount, sizeof(char*));
  for (int k = 0; k < line_amount; ++k) {
    this_program[k] = calloc(9, sizeof(char));
    memcpy(this_program[k], program[k], 9 * sizeof(char));
  }

  for (int i = 0; i < line_amount; ++i) {
    int result = 0;
    char new_cmd[10] = {0};
    if (!memcmp(program[i], "jmp", 3)) {
      sprintf(new_cmd, "nop%s", program[i] + 3);
    } else if (!memcmp(program[i], "nop", 3)) {
      sprintf(new_cmd, "jmp%s", program[i] + 3);
    }
    if (new_cmd[0]) {
      strncpy(this_program[i], new_cmd, 9);
      printf("new line: %s\n", this_program[i]);
      if (execute(this_program, line_amount, &result)) {
        for (int j = 0; j < line_amount; ++j) {
          free(this_program[j]);
        }
        free(this_program);
        return result;
      } else {
        strcpy(this_program[i], program[i]);
        printf("%s\n", this_program[i]);
      }
    }
  }
  return 0;
}

int main(int argc, char* args[]) {
  FILE* file = fopen("input", "r");
  if (!file) return 0;
  char** instructions = 0;
  int32_t acc = 0;
  int i_amount = 0;
  char buf[10] = {0};
  instructions = calloc(1, sizeof(char*));
  // each line is max 8 char + null terminator
  instructions[0] = calloc(9, sizeof(char));

  while (fgets(buf, sizeof(buf), file)) {
    buf[strcspn(buf, "\n")] = 0;
    strncpy(instructions[i_amount], buf, 9);
    ++i_amount;
    instructions = realloc(instructions, (i_amount + 1) * sizeof(char*));
    instructions[i_amount] = calloc(9, sizeof(char));
    memset(buf, 0, 9);
  }
  fclose(file);
  execute(instructions, i_amount, &acc);
  printf("part1: %d\npart2: %d\n", acc, part2(instructions, i_amount));
  for (int i = 0; i <= i_amount; i++) free(instructions[i]);
  free(instructions);
}