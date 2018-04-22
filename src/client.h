/**
 * Author: Jan Pristas, Brno University Of Technology, Faculty Of Information Technologies
 **/

#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <vector>

#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#include "getopt.h"
#include "crc.h"

/* Constants */
const int buffsize = 8192;

void readInputFile(std::istream& in, std::vector<std::string> &message, struct Options options);
void writeOutputToFile(std::ostream& out, std::vector<std::string> answer);
int tcpMessage(std::vector<std::string> message, std::vector<std::string> &answer, struct Options options, struct OptionArgs optionArgs);
int udpMessage(std::vector<std::string> message, std::vector<std::string> &answer, struct OptionArgs optionArgs);


