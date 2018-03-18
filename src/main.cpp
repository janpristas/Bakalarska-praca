/**
 *
 **/

#include "client.h"

int main(int argc, char *argv[]) {
	struct Options options;
	struct OptionArgs optionArgs;
	std::vector<std::string> message;
	std::vector<std::string> answer;

	message.clear();
	answer.clear();

	/* Input params check */
	params(argc, argv, options, optionArgs);

	if (options.input == 1) {
		std::ifstream inputFile;
		inputFile.open(optionArgs.input, std::ios::binary);
		if (inputFile) {
			readInputFile(inputFile, message);
			inputFile.close();
		} else {
			errorMsg(EFILE);
		}
	} else {
		readInputFile(std::cin, message);
	}

	if (options.tcp == 1) {
		tcpMessage(message, answer, optionArgs);
	} else {
		udpMessage(message, answer, optionArgs);
	}

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