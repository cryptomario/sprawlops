// WARNING: No checks are performed on input or output files. Make sure you do not read from untrustworthy files or overwrite data!

#include <unistd.h>
#include <string>
#include <random> 
#include "sprawlops-glob.h"
#include "sprawlops-io.h"
#include "sprawlops-io.cpp"


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
	if (skill >= srconst::veteran){
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

// Conducts a skill test (consisting of three attmpts), where all dice have the same color
// Input:  Skill level and difficulty
// Return: Test result - success, failure, wound, or death
// Uses rerolls for unlucky throws (#failures * 6 > #dice)
// Uses armor
int test_singlecolor(int skill, int difficulty){
	int i = 0;        // Counter for attempts in a test (up to tries = 3)
	int s = 0;        // Number of successes in an attempt (prob. 2/6) 
	int f = 0;        // Number of failures in an attempt (prob. 1/6) 
	int succ = 0;     // Number of successes in the test so far
	int damage = 0;   // damage taken
	int rr = rerolls; // local rerolls
	bool unlucky = false;   // unlucky test? needed for reroll 
	int ap = armor_points; // local armor points
	bool wound = false;     // not wounded before the test
	bool death = false;     // not dead before thetest 
	int throw_res[2] = {0, 0};   // Result of a single attempt: #failures, #successes
	int res = 0;      // result of a test (success, failure, wound, or death)
	int d = skill;    // Number of dice, needed to determine unluckiness
	if (skill >= srconst::veteran) d = skill - 2;
	while ((i < srconst::tries) && (succ < difficulty) && !wound && !death){ //Up to three attepts, until success, wound or death.
	  i++;
	  roll(skill, throw_res); //roll writes the number of failures and successes in an attempt into throw_res[2]
	  f = throw_res[0];
	  s = throw_res[1];
	  if (verbose) printf("test_sc: try %d) fail: %d; succ: %d\n", i, f, s);
	  if (f*6 > d) unlucky = true;
	  if (unlucky && rr > 0){ // use re-rolls for unlucky throws
	    rr = rr - 1;
	    roll(skill - s, throw_res); // keep successes, reroll all other dice
	    f = throw_res[0];     // do not keep earlier failures
	    s = s + throw_res[1]; // add old and new successes
	    if (verbose) printf("test_sc: re-try %d) fail: %d; succ: %d\n", i, f, s);
	  }
	  if (f - s > 0) {
	    damage = f - s;
	    if (ap > 0) {         // if there is damage and runner is wearing armor...
	      if (ap > damage) {
	        ap = ap - damage;     // either negate all the damage...
	        damage = 0;
	      } else {
	        damage = damage - ap; // or reduce damage as much as possible
	      }
	    }
	    if (i == 3 && ap > 0) { // in the last try, use armor to negate failures
	      if (ap > f) {
	        ap = ap - f;     // either negate all the failures...
	        f = 0;
	      } else {
	        f = f - ap; // or negate as many as possible
	      }
	    }
	    if (damage >= srconst::thresh_wound) wound = true;
	    if (damage >= srconst::thresh_death) death = true;
	  }
	  s = s - f;  // Every failure cancels a success
	  if (s > 0) succ = succ + s;  // Count successes from attempt towards total number of successes 
	} 
	if (death) res = srconst::DEATH; 
	else if (wound) res = srconst::WOUND; 
	else if (succ >= difficulty) res = srconst::SUCCESS; 
	else res = srconst::FAILURE;
	return res;
}

int main(int argc, char* argv[]) {
	int res;             // Test result
	int skill = 5;       // Default value to make testing easier
	int difficulty = 2;  // Default value to make testing easier
	int statistics[5] = {0, 0, 0, 0, 0};  // Holds the total number of tests and the number of each of the four possible test result: success, failure, wound, death.
	parse_input_cmdline(argc, argv);
	clear_outfile();
	for (difficulty = 1; difficulty <= max_difficulty; difficulty++){
	  printf(" W | == Difficulty %d ==\n", difficulty); 
	  for (skill = 1; skill <= max_skill; skill++){
	    for (int i = 0; i < nr_experiments; i++){
	      res = test_singlecolor(skill, difficulty);
	      statistics[srconst::TOTAL]++;
	      statistics[res]++;
	      if (verbose) printf("== main: experiment %d for skill %d with difficulty %d ==\n + %d | o %d | - %d | -- %d |\n", i, skill, difficulty, statistics[srconst::SUCCESS], statistics[srconst::FAILURE], statistics[srconst::WOUND], statistics[srconst::DEATH]);
	    }
	    if (verbose) printf("== main: end result of experiment for skill %d with difficulty %d ==\n + %d | o %d | - %d | -- %d | total %d; \n", skill, difficulty, statistics[srconst::SUCCESS], statistics[srconst::FAILURE], statistics[srconst::WOUND], statistics[srconst::DEATH], statistics[srconst::TOTAL]);
	    print_results(skill, difficulty, statistics);
	    for (int j = 0; j < 5; j++) statistics[j] = 0; //Reset
	  }
	}
	return 1;
}
