#ifndef SPRAWLOPS_IO
#define SPRAWLOPS_IO

int parse_input_file(std::string infile);
int parse_input_cmdline(int argc, char* argv[]);
int clear_outfile();
int print_results(int skill, int difficulty, int statistics[]);

#endif
