/**
 * Program klienta pre komunikacne protokoly DLMS/COSEM a IEC 104
 * Autor: Jan Pristas, Vysoke uceni technicke v Brne, Fakulta informacnich technologii
 **/

#include "client.h"

int main(int argc, char *argv[]) {
	struct Options options;
	struct OptionArgs optionArgs;
	std::vector<std::string> message;
	std::vector<std::string> answer;

	message.clear();
	answer.clear();

	/* Kontrola vstupnych parametrov */
	params(argc, argv, options, optionArgs);

	/* Nacitanie prikazov */
	if (options.input == 1) {
		std::ifstream inputFile;
		inputFile.open(optionArgs.input, std::ios::binary);
		if (inputFile) {
			readInputFile(inputFile, message, options);
			inputFile.close();
		} else {
			errorMsg(EFILE);
		}
	} else {
		readInputFile(std::cin, message, options);
	}

	/* Komunikacia so serverom */
	tcpMessage(message, answer, options, optionArgs);

	/* Zapis odpovedi od servera */
	if (options.output == 1) {
		std::ofstream outputFile;
		outputFile.open(optionArgs.output, std::ios::binary);
		if (outputFile) {
			writeOutputToFile(outputFile, answer);
			outputFile.close();
		} else {
			errorMsg(EFILE);
		}
	} else { 
		writeOutputToFile(std::cout, answer);
	}	

	return 0;
}
