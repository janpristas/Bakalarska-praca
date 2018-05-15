/**
 * Program klienta pre komunikacne protokoly DLMS/COSEM a IEC 104
 * Funkcia na nacitanie vstupnych parametrov
 * Autor: Jan Pristas, Vysoke uceni technicke v Brne, Fakulta informacnich technologii
 **/

#include "getopt.h"

/**
 * Funkcia na nacitanie vstupnych parametrov
 */
void params(int argc, char *argv[], struct Options &options, struct OptionArgs &optionArgs) {
	int c = 0;
	int index = 0;
	opterr = 0;

	while ((c = getopt_long(argc, argv, "ha:p:i:o:12", long_options, &index)) != EOF) {
		switch(c) {
			case 'h':
				options.help = 1;
				break;
			case 'a':
				options.addr = 1;
				optionArgs.addr = optarg;
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

	/* Kontrola spravnych kombinacii zadanych parametrov */
	if ((options.help == 0) && (options.addr == 0)) {
		errorMsg(EADR);
	} else if ((options.help == 1) && ((options.addr == 1) || (options.port == 1) || (options.input == 1) || (options.output == 1))) {
		errorMsg(EHLP);
	} else if (options.help == 1) {
		helpMessage();
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