#ifndef SPRAWLOPS_CONST
#define SPRAWLOPS_CONST

// Global constants fixed by me
int nr_runners = 1;     // Number of runners in a group
int nr_experiments = 5; // Number of repetitions of an experiment (default value, can be overwritten by command line arguments)
int max_skill = 10;
int max_difficulty = 5;
// Global variables
int verbose = 0;
int armor_points = 0;   // each armor point compensates one wound 
int rerolls = 0;        // rerolls allow rerolling any number of dice in an attempt

namespace srconst{
	constexpr int TOTAL {0};
	constexpr int BAD {0};
	constexpr int SUCCESS {1};
	constexpr int FAILURE {2};
	constexpr int WOUND {3};
	constexpr int DEATH {4};
	// Global constants fixed by the game
	constexpr int tries {3};          // Number of attempts per test
	constexpr int veteran {5};        // Skill 5 gives an auto-success at the cost of two dice
	constexpr int thresh_wound {1};   // One uncanceled failure wounds a runner 
	int thresh_death = nr_runners + 1; // A runner dies, when there are more uncanceled failures than runners in a group
}

#endif
