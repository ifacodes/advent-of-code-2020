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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../util/loadfile.h"
#include "../util/strtok_mp.h"

typedef struct passport {
  int byr;
  int iyr;
  int eyr;
  char* hgt;
  char* hcl;
  char* ecl;
  int pid;
  int cid;
} passport;

int main(int argc, char* args[]) {
  char* file = loadfile("input");
  char* buffer = '\0';
  char* token;
  int count;

  token = strtok_mp(file, "\n\n", &buffer);

  while (token) {
    printf("%s\nBREAK\n", token);
    token = strtok_mp(NULL, "\n\n", &buffer);
  }
}