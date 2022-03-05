#include <iostream>
#include <math.h>
 
using namespace std;

#define N_RESULTS 3
#define N_EYES 3

int main() {
    string input;                 // each line inserted
    int results[N_RESULTS] = {0}; // all results
    int current = 0;              // current result index

    // get each line inserted
    while(getline(cin, input)) {
      // stop condition for each result
      if (input == "caw caw") {
        // global stop condition
        if (current == N_RESULTS-1) {
          break;
        }
        // update current index to calculate the next result
        current++;
      } else {
        // ensure will receive exactly 3 eyes
        int lenght = input.length();
        if (lenght != N_EYES) {
          continue;
        }
        // calculates each binary number and increment the current result
        int powerof = 0;
        for (int i = lenght-1; i >= 0; --i) {
          if (input[i] == '*') {
            results[current] += pow(2, powerof);
          }
          powerof++;
        }
      }
    }
    
    // show all results
    for (int i = 0; i < N_RESULTS; ++i) {
      cout << results[i] << endl;
    }

    return 0;
}