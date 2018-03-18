/**
 *
 **/

#include <iostream>
#include <getopt.h>
#include "errors.h"

const int def_port = 4059;

/* Struct definitions */
const struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"address", required_argument, 0, 'a'},
		{"tcp", no_argument, 0, 't'},
		{"udp", no_argument, 0, 'u'},
		{"port", no_argument, 0, 'p'},
		{"file", no_argument, 0, 'f'},
		{0, 0, 0, 0}
};

struct Options {
	bool help = 0;
	bool addr = 0;
	bool port = 0;
	bool tcp = 0;
	bool udp = 0;
	bool input = 0;
	bool output = 0;
};

struct OptionArgs {
	std::string addr;
	int port = def_port;
	std::string input;
	std::string output;
};

void params(int argc, char *argv[], struct Options &options, struct OptionArgs &optionArgs);
