/**
 * Author: Jan Pristas, Brno University Of Technology, Faculty Of Information Technologies
 **/

#include "getopt.h"

void params(int argc, char *argv[], struct Options &options, struct OptionArgs &optionArgs) {
	int c = 0;
	int index = 0;
	opterr = 0; // Turn off getopt error messages

	while ((c = getopt_long(argc, argv, "ha:tup:i:o:12", long_options, &index)) != EOF) {
		switch(c) {
			case 'h':
				options.help = 1;
				break;
			case 'a':
				options.addr = 1;
				optionArgs.addr = optarg;
				break;
			case 't':
				options.tcp = 1;
				break;
			case 'u':
				options.udp = 1;
				break;
			case 'p':
				if (isdigit(*optarg)) {
					options.port = 1;
					optionArgs.port = std::stoi(optarg);
					if ((optionArgs.port < 0) || (optionArgs.port > 65535)) {
						errorMsg(EPORT);
					} else {
						break;
					}
				} else {
					errorMsg(ENUM);
				}
			case 'i':
				options.input = 1;
				optionArgs.input = optarg;
				break;
			case 'o':
				options.output = 1;
				optionArgs.output = optarg;
				break;
			case '1':
				options.iec = 1;
				break;
			case '2':
				options.dlms = 1;
				break;
			case '?':
				errorMsg(EARG);
			default:
				errorMsg(EARG);
		}
	}

	if ((options.help == 0) && (options.addr == 0)) {
		errorMsg(EADR);
	} else if ((options.help == 1) && ((options.addr == 1) || (options.tcp == 1) || (options.udp == 1) || (options.port == 1) || (options.input == 1) || (options.output == 1))) {
		errorMsg(EHLP);
	} else if (options.help == 1) {
		helpMessage();
	}

	if ((options.tcp == 1) && (options.udp == 1)) {
		errorMsg(ETU);
	} else if ((options.tcp == 0) && (options.udp == 0)) {
		errorMsg(EUT);
	}

	if ((options.iec == 1) && (options.dlms == 1)) {
		errorMsg(EPROT);
	} else if ((options.iec == 0) && (options.dlms == 0)) {
		errorMsg(EPROT);
	}

	if (options.port == 0) {
		if (options.iec == 1) {
			optionArgs.port = def_iec_port;
		} else {
			optionArgs.port = def_dlms_port;
		}
	}
}