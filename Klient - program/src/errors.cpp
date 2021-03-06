/**
 * Program klienta pre komunikacne protokoly DLMS/COSEM a IEC 104
 * Funkcie na vypis chybovych sprav a napovedy
 * Autor: Jan Pristas, Vysoke uceni technicke v Brne, Fakulta informacnich technologii
 **/

#include "errors.h"

/**
 * Funkcia pre vypis napovedy
 */
void helpMessage() {
	std::cout << "Client program for communication protocol DLMS. " << std::endl << \
	"Usage: ./client [-h (--help)] [-p (--port) <port>] [-i (--input) <input_file>] [-o (--output) <output_file>] -a (--address) <ip_address>" << std::endl;
	exit(EHELP);
}

/**
 * Funkcia na vypis chybovych sprav
 */
void errorMsg(int e_code) {
	switch(e_code) {
		case EARG:
			std::cerr << "Wrong input arguments! Usage: ./client [-h (--help)] [-p (--port) <port>] [-i (--input) <input_file>] [-o (--output) <output_file>] -a (--address) <ip_address>" << std::endl;
			exit(EARG);		
		case EADR:
			std::cerr << "If parameter -h (--help) is not set, parameter -a (--address) is mandatory." << std::endl;
			exit(EADR);
		case ENUM:
			std::cerr << "Port value has to be unsigned number." << std::endl;
			exit (ENUM);
		case EPORT:
			std::cerr << "Port value has to be number in range 0..65535." << std::endl;
			exit(EPORT);
		case EPROT:
			std::cerr << "One of protocols IEC104 and DLMS has to be set. But don't both at the same time." << std::endl;
			exit(EPROT);
		case EHLP:
			std::cerr << "Help message request has to be set individual, without any other parameter." << std::endl;
			exit(EHLP);
		case EFILE:
			std::cerr << "Opening file error." << std::endl;
			exit(EFILE);
		case ESOCK:
			std::cerr << "Opening socket error." << std::endl;
			exit(ESOCK);
		case EADDR:
			std::cerr << "IP address is not correct." << std::endl;
			exit(EADDR);
		case ECON:
			std::cerr << "Connecting problem." << std::endl;
			exit(ECON);
		case ESEND:
			std::cerr << "Sending message error." << std::endl;
			exit(ESEND);
		case EREAD:
			std::cerr << "Reading answer error." << std::endl;
			exit(EREAD);
		case ERECV:
			std::cerr << "Receive answer error." << std::endl;
			exit(ERECV);
		default:
			std::cerr << "Unknown error." << std::endl;
			exit(EUNK);
	}
}