/**
 * Program klienta pre komunikacne protokoly DLMS/COSEM a IEC 104
 * Funkcie na nacitanie prikazov a komunikaciu so serverom
 * Autor: Jan Pristas, Vysoke uceni technicke v Brne, Fakulta informacnich technologii
 **/

#include "client.h"

/**
 * Funkcia na precitanie vstupneho suboru s prikazmi
 */
void readInputFile(std::istream& in, std::vector<std::string> &message, struct Options options) {
	unsigned int x, a, b;
	std::string tmp, str;

	str.clear();
	tmp.clear();

	/* Kontrola protokolu, pre DLMS/COSEM sa prepocitava kontrolny sucet CRC16 */
	if (options.iec == 1) {
		getline(in, str, '~');

		while (!in.fail()) {
			message.push_back(str);
			getline(in, str, '~');
		}
	} else {
		getline(in, str, '?');

		while (!in.fail()) {
			for (int i = 1; i < str.length()-3; i++) {
				tmp += str[i];
			}

			computeCRC();

			/* Invertovanie bytov kontrolneho suctu, kvoli spravnemu zapisu */
			x = crctable((unsigned char *)tmp.c_str(), tmp.length());
			a = (x & (FIRSTBYTE)) >> 8;
			b = x & SECONDBYTE;

			str[str.length()-3] = b;
			str[str.length()-2] = a;

			message.push_back(str);

			str.clear();
			tmp.clear();

			getline(in, str, '?');
		}
	}
}

/**
 * Funkcia na zapis odpovedi od servera do vystupneho suboru
 */
void writeOutputToFile(std::ostream& out, std::vector<std::string> answer) {
	for (std::vector<std::string>::iterator it = answer.begin(); it != answer.end(); ++it) {
		out << *it << '?';
	}
}

/**
 * Funkcia na komunikaciu so serverom
 */
int tcpMessage(std::vector<std::string> message, std::vector<std::string> &answer, struct Options options, struct OptionArgs optionArgs) {
	bool isReceiving = true;
	char buffer[buffsize];
	int sock = 0, rc;
	struct sockaddr_in addr;
	struct timeval timeout;

	timeout.tv_sec = 1;
	timeout.tv_usec = 500000;

	/* Vytvorenie socketu */
	if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
		errorMsg(ESOCK);
	}

	memset(&addr, '0', sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(optionArgs.port);

	if (inet_pton(AF_INET, optionArgs.addr.c_str(), &addr.sin_addr) <= 0) {
		errorMsg(EADDR);
	}

	/* Vytvorenie spojenia so serverom */
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		errorMsg(ECON);
	}

	/* Postupne zasielanie/prijimanie sprav */
	for (std::vector<std::string>::iterator it = message.begin(); it != message.end(); ++it) {
		if ((send(sock, (*it).c_str(), (*it).length(), 0)) < 0) {
			errorMsg(ESEND);
		} else {
			std::cout << "Send" << std::endl;
		}

		memset(buffer, '\0', sizeof(buffer));

		/* Pri protokole IEC 104 sa caka, kym server odosle vsetky spravy, kvoli jeho asynchronnej strukture */
		if (options.dlms == 1) {
			if ((recv(sock, buffer, sizeof(buffer), 0)) > 0) {
				std::cout << "Received" << std::endl;
				answer.push_back(buffer);
				memset(buffer, '\0', sizeof(buffer));
			}
		} else {
			while (isReceiving) {
				fd_set Set;

				FD_ZERO(&Set);
				FD_SET(sock, &Set);

				rc = select(sock + 1, &Set, NULL, NULL, &timeout);
				
				switch(rc) {
					case 0:
					case -1:
						isReceiving = false;
						break;
					default:
						if ((recv(sock, buffer, sizeof(buffer), 0)) > 0) {
							std::cout << "Received" << std::endl;
							answer.push_back(buffer);
							memset(buffer, '\0', sizeof(buffer));
						} else {
							errorMsg(ERECV);
						}
						break;
				}
			}
			isReceiving = true;
		}
	}

	close(sock);

	return 0;
}


















