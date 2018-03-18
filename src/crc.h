/**
 *
 **/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define FIRSTBYTE	0b1111111100000000
#define SECONDBYTE	0b0000000011111111

const int order = 16;
const unsigned long polynom = 0x1021;
const unsigned long crcinit = 0xffff;
const unsigned long crcxor = 0xffff;
const int refin = 1;
const int refout = 1;

unsigned long reflect(unsigned long crc, int bitnum);
void generate_crc_table();
unsigned long crctable(unsigned char* p, unsigned long len);
void computeCRC();


