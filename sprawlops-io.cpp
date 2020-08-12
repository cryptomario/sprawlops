#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include "sprawlops-glob.h"

std::string outfile = "";

// Processes lines from an input file as if they were (short) command line options
// Input:  File to read from (infile)
// Return: 1 for successful execution
// Effect: Sets global variables according to the infile
int parse_input_file(std::string infile) {
	int ret = 1;
	std::string line;
	int i = 0;
	if (infile != "") {
	  std::ifstream myfile;
	  myfile.open (infile, std::ios::in);
	  while ( getline(myfile, line) ) {
	    std::istringstream iss(line);
	    std::vector<std::string> results(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
	    switch (results[0][1]) {
	    case 'n': 
	      nr_experiments = std::stoi(results[1]);
	      break;
	    case 'v': 
	      verbose = 1;
	      break;
	    case 'a': 
	      armor_points = std::stoi(results[1]);
	      break;
	    case 'r': 
	      rerolls = std::stoi(results[1]);
	      break;
	    case 'o': 
	      outfile = results[1];
	      break;
	    }
	  }
	  myfile.close();
	  return ret;// return the same return value as myfile.close()
	}
}

// Processes (short) command line options
// Input:  Command line arguments
// Return: 1 for successful execution
// Effect: Sets global variables according to the command line options
int parse_input_cmdline(int argc, char* argv[]) {
	int ret = 1;
	int opt;                // Command line options
	std::string infile;
	while ( (opt = getopt(argc, argv, "n:va:r:i:o:") ) != -1) {
	  switch (opt) {
	  case 'n': 
	    nr_experiments = atoi(optarg);
	    break;
	  case 'v': 
	    verbose = 1;
	    break;
	  case 'a': 
	    armor_points = atoi(optarg);
	    break;
	  case 'r': 
	    rerolls = atoi(optarg);
	    break;
	  case 'i': 
	    infile = optarg;
	    parse_input_file(infile);
	    break;
	  case 'o': 
	    outfile = optarg;
	    break;
	  default:
	    fprintf(stderr, 
	            "WARNING: No checks are performed on input or output files. Make sure you do not overwrite data!\n"
	            "Usage: %s [-n nr_experiments] [-v]  [-a armor_poits]  [-r nr_rerolls] [-i input_file] [-o output_file]\n"
	            "  -n  Number of repetitions of an experiment\n"
	            "  -v  Verbose\n"
	            "  -a  Number of armor points\n"
	            "  -r  Number of re-rolls\n"
	            "  -i  Input file containing command-line arguments\n"
	            "  -o  Append raw data to file as Comma Separated Values\n"
	            "Example usage: %s -n 100000\n", argv[0], argv[0]);
	    exit(EXIT_FAILURE);
	  }
	}
	return ret;
}

// Saves the output file (global variable) to empty 
// Input:  -
// Return: 1 for successful execution
// Effect: Deletes the contents of the output file in preparation for print_results
int clear_outfile() {
	int ret = 1;
	if (outfile != "") {
	  std::ofstream myfile;
	  myfile.open (outfile, std::ios::out);
	  myfile.close();
	}
	return ret;
}

// Prints the results of one experiment to standard out and into a file
// Input:  The skill and difficulty for the experiment, the resulting statistics
// Return: 1 for successful execution
// Effect: Prints one line to standard out
//         Appends one line to the output file (if it set)
int print_results(int skill, int difficulty, int statistics[]) {
	int ret = 1;
	float percentages[5] = {0, 0, 0, 0, 0};  // Percentages of the possible test results in an experiment (field BAD is used for the percentage of bad results, wound or death).
	percentages[srconst::SUCCESS] = static_cast<float>(statistics[srconst::SUCCESS]) * 100 / statistics[srconst::TOTAL];
	percentages[srconst::FAILURE] = static_cast<float>(statistics[srconst::FAILURE]) * 100 / statistics[srconst::TOTAL];
	percentages[srconst::WOUND]   = static_cast<float>(statistics[srconst::WOUND])   * 100 / statistics[srconst::TOTAL];
	percentages[srconst::DEATH]   = static_cast<float>(statistics[srconst::DEATH])   * 100 / statistics[srconst::TOTAL];
	percentages[srconst::BAD]     = static_cast<float>(statistics[srconst::WOUND]+statistics[srconst::DEATH]) * 100 / statistics[srconst::TOTAL];
	printf("%2d | + %4.1f | o %4.1f | - %4.1f | -- %4.1f | -/-- %4.1f |\n", skill, percentages[srconst::SUCCESS], percentages[srconst::FAILURE], percentages[srconst::WOUND], percentages[srconst::DEATH], percentages[srconst::BAD]);
	if (skill == max_skill) printf("\n");
	if (outfile != "") {
	  std::ofstream myfile;
	  myfile.open (outfile, std::ios::app);
	  myfile << skill << "; " << difficulty << "; " << statistics[srconst::SUCCESS] << "; " << statistics[srconst::FAILURE] << "; " << statistics[srconst::WOUND] << "; " << statistics[srconst::DEATH] << "; " << statistics[srconst::TOTAL] << ";\n";
	  myfile.close();
	}
	return ret;
}
