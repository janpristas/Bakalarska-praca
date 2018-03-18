/**
 *
 **/

#include <iostream>

enum eCodes {
	EHELP, // Request for help message
	EARG, // Wrong input arguments
	EADR, // Ip address is mandatory
	ENUM,
	EPORT,
	EHLP,
	ETU,
	EUT,
	EFILE,
	ESOCK,
	EADDR,
	ECON,
	ESEND,
	EREAD,
	EBIND,
	ERECV,
	EUNK // Unknown error
};

void helpMessage();
void errorMsg(int e_code);