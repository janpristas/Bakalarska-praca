/**
 * Program klienta pre komunikacne protokoly DLMS/COSEM a IEC 104
 * Funkcia na nacitanie vstupnych parametrov
 * Autor: Jan Pristas, Vysoke uceni technicke v Brne, Fakulta informacnich technologii
 **/

#include <iostream>
#include <getopt.h>
#include "errors.h"

const int def_dlms_port = 4059;
const int def_iec_port = 2404;

/* Struktura vstupnych parametrov */
const struct option long_options[] = {
		{"help", no_argument, 0, 'h'},
		{"address", required_argument, 0, 'a'},
		{"iec", no_argument, 0, '1'},
		{"dlms", no_argument, 0, '2'},
		{"port", no_argument, 0, 'p'},
		{"input", no_argument, 0, 'i'},
		{"output", no_argument, 0, 'o'},
		{0, 0, 0, 0}
};

/* Struktura zadanych parametrov */
struct Options {
	bool help = 0;
	bool addr = 0;
	bool port = 0;
	bool iec = 0;
	bool dlms = 0;
	bool input = 0;
	bool output = 0;
};

/* Struktura hodnot zadanych parametrov */
struct OptionArgs {
	std::string addr;
	int port;
	std::string input;
	std::string output;
};

void params(int argc, char *argv[], struct Options &options, struct OptionArgs &optionArgs);
