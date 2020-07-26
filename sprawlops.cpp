#include <unistd.h>
#include <iostream>
#include <fstream>
#include <random> 

#define TOTAL 0
#define BAD 0
#define SUCCESS 1
#define FAILURE 2
#define WOUND 3
#define DEATH 4

// Global constants fixed by me
int nr_runners = 1;     // Number of runners in a group
int nr_experiments = 5; // Number of repetitions of an experiment (default value, can be overwritten by command line arguments)
int max_skill = 10;
int max_difficulty = 5;

// Global constants fixed by the game
int tries = 3;          // Number of attempts per test
int veteran = 5;        // Skill 5 gives an auto-success at the cost of two dice
int thresh_wound = 1;   // One uncanceled failure wounds a runner 
int thresh_death = nr_runners + 1; // A runner dies, when there are more uncanceled failures than runners in a group

// Global variables
int verbose = 0;
std::string outfile;

// One attempt for a skill test
// Input:  Skill level
// Return: 1 for successful execution
// Effect: Writes result of attempt (#failures, #successes) into array throw_res 
int roll(int skill, int throw_res[]){
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::minstd_rand gen(rd()); //Linear congruential generator, seeded with rd()
  std::uniform_int_distribution<> distrib(1, 6);
  int s = 0;        // Number of successes in an attempt (prob. 2/6) 
  int f = 0;        // Number of failures in an attempt (prob. 1/6) 
  int roll = 0;     // Result of a single die roll
  int d = skill;    // Number of dice
  if (skill >= veteran){
    d = skill - 2;
    s = 1;
  }
  for (int i = 0; i < d; i++){
    roll = distrib(gen);
    if (verbose) printf("roll: %d) rolled %d\n", i, roll);
    if (roll == 1) f++;
    if (roll == 5 || roll == 6) s++;
  }
  throw_res[0] = f;
  throw_res[1] = s;
  if (verbose) printf("roll: fail: %d; succ: %d\n", f, s);
  return 1;
}

// Attempts a skill test, where all dice have the same color
// Input:  Skill level and difficulty
// Return: Test result - success, failure, wound, or death
int test_singlecolor(int skill, int difficulty){
  int i = 0;        // Counter for attempts in a test (up to tries = 3)
  int s = 0;        // Number of successes in an attempt (prob. 2/6) 
  int f = 0;        // Number of failures in an attempt (prob. 1/6) 
  int succ = 0;     // Number of successes in the test so far
  bool wound = false;     // not wounded before the test
  bool death = false;     // not dead before thetest 
  int throw_res[2] = {0, 0};   // Result of a single attempt: #failures, #successes
  int res = 0;      // result of a test (success, failure, wound, or death)
  while ((i < tries) && (succ < difficulty) && !wound && !death){ //Up to three attepts, until success, wound or death.
    i++;
    roll(skill, throw_res); //roll writes the number of failures and successes in an attempt into throw_res[2]
    f = throw_res[0];
    s = throw_res[1];
    if (verbose) printf("test_sc: try %d) fail: %d; succ: %d\n", i, f, s);
    if (f - s >= thresh_wound) wound = true;
    if (f - s >= thresh_death) death = true;
    s = s - f;  // Every failure cancels a success
    if (s > 0) succ = succ + s;  // Count successes from attempt towards total number of successes 
  } 
  if (death) res = DEATH; 
  else if (wound) res = WOUND; 
  else if (succ >= difficulty) res = SUCCESS; 
  else res = FAILURE;
  return res;
}

int parse_input(int argc, char* argv[]) {
  int opt;                // Command line options
  while ( (opt = getopt(argc, argv, "vn:f:") ) != -1) {
    switch (opt) {
    case 'v': 
      verbose = 1;
      break;
    case 'n': 
      nr_experiments = atoi(optarg);
      break;
    case 'f': 
      outfile = optarg;
      break;
    default:
      fprintf(stderr, 
              "Usage: %s [-v] [-n nr_experiments] [-f output_file]\n"
              "  -v  Verbose\n"
              "  -n  Number of repetitions of an experiment\n"
              "  -f  Write raw data to file as Comma Separated Values\n"
              "Example usage: %s -n 100000\n", argv[0], argv[0]);
      exit(EXIT_FAILURE);
    }
  }
  return 1;
}

int print_results(int skill, int difficulty, int statistics[]){
  float percentages[5] = {0, 0, 0, 0, 0};  // Percentages of the possible test results in an experiment (field BAD is used for the percentage of bad results, wound or death).
  percentages[SUCCESS] = static_cast<float>(statistics[SUCCESS]) * 100 / statistics[TOTAL];
  percentages[FAILURE] = static_cast<float>(statistics[FAILURE]) * 100 / statistics[TOTAL];
  percentages[WOUND]   = static_cast<float>(statistics[WOUND])   * 100 / statistics[TOTAL];
  percentages[DEATH]   = static_cast<float>(statistics[DEATH])   * 100 / statistics[TOTAL];
  percentages[BAD]     = static_cast<float>(statistics[WOUND]+statistics[DEATH]) * 100 / statistics[TOTAL];
  if (skill == 1) printf(" W | == Difficulty %d ==\n", difficulty); 
  printf("%2d | + %4.1f | o %4.1f | - %4.1f | -- %4.1f | -/-- %4.1f |\n", skill, percentages[SUCCESS], percentages[FAILURE], percentages[WOUND], percentages[DEATH], percentages[BAD]);
  if (skill == max_skill) printf("\n");
  if (outfile != "") {
    std::ofstream myfile;
    myfile.open (outfile, std::ios::app);
    myfile << skill << "; " << difficulty << "; " << statistics[SUCCESS] << "; " << statistics[FAILURE] << "; " << statistics[WOUND] << "; " << statistics[DEATH] << "; " << statistics[TOTAL] << ";\n";
    myfile.close();
  }
  return 1;
}    

int main(int argc, char* argv[]) {
  int res;             // Test result
  int skill = 5;       // Default value to make testing easier
  int difficulty = 2;  // Default value to make testing easier
  int statistics[5] = {0, 0, 0, 0, 0};  // Holds the total number of tests and the number of each of the four possible test result: success, failure, wound, death.
  parse_input(argc, argv);
  for (difficulty = 1; difficulty <= max_difficulty; difficulty++){
    for (skill = 1; skill <= max_skill; skill++){
      for (int i = 0; i < nr_experiments; i++){
        res = test_singlecolor(skill, difficulty);
        statistics[TOTAL]++;
        statistics[res]++;
        if (verbose) printf("== main: experiment %d for skill %d with difficulty %d ==\n + %d | o %d | - %d | -- %d |\n", i, skill, difficulty, statistics[SUCCESS], statistics[FAILURE], statistics[WOUND], statistics[DEATH]);
      }
      if (verbose) printf("== main: end result of experiment for skill %d with difficulty %d ==\n + %d | o %d | - %d | -- %d | total %d; \n", skill, difficulty, statistics[SUCCESS], statistics[FAILURE], statistics[WOUND], statistics[DEATH], statistics[TOTAL]);
      print_results(skill, difficulty, statistics);
      for (int j = 0; j < 5; j++) statistics[j] = 0; //Reset
    }
  }
  return 1;
}
