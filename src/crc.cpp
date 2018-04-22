/**
 * Client program for SCADA communication protocol DLMS
 * Author: Jan Pristas, Brno University Of Technology, Faculty Of Information Technologies
 **/

#include "crc.h"

unsigned long crcmask;
unsigned long crchighbit;
unsigned long crcinit_direct;
unsigned long crcinit_nondirect;
unsigned long crctab[256];

unsigned long reflect(unsigned long crc, int bitnum) {

	// reflects the lower 'bitnum' bits of 'crc'

	unsigned long i, j=1, crcout=0;

	for (i=(unsigned long)1<<(bitnum-1); i; i>>=1) {
		if (crc & i) crcout|=j;
		j<<= 1;
	}
	return (crcout);
}

void generate_crc_table() {

	// make CRC lookup table used by table algorithms

	int i, j;
	unsigned long bit, crc;

	for (i=0; i<256; i++) {

		crc=(unsigned long)i;
		if (refin) crc=reflect(crc, 8);
		crc<<= order-8;

		for (j=0; j<8; j++) {

			bit = crc & crchighbit;
			crc<<= 1;
			if (bit) crc^= polynom;
		}			

		if (refin) crc = reflect(crc, order);
		crc&= crcmask;
		crctab[i]= crc;
	}
}

unsigned long crctable(unsigned char* p, unsigned long len) {

	// normal lookup table algorithm with augmented zero bytes.
	// only usable with polynom orders of 8, 16, 24 or 32.

	unsigned long crc = crcinit_nondirect;

	if (refin) crc = reflect(crc, order);

	if (!refin) while (len--) crc = ((crc << 8) | *p++) ^ crctab[ (crc >> (order-8))  & 0xff];
	else while (len--) crc = ((crc >> 8) | (*p++ << (order-8))) ^ crctab[ crc & 0xff];

	if (!refin) while (++len < order/8) crc = (crc << 8) ^ crctab[ (crc >> (order-8))  & 0xff];
	else while (++len < order/8) crc = (crc >> 8) ^ crctab[crc & 0xff];

	if (refout^refin) crc = reflect(crc, order);
	crc^= crcxor;
	crc&= crcmask;

	return(crc);
}

void computeCRC() {
	int i;
	unsigned long bit, crc;

	// at first, compute constant bit masks for whole CRC and CRC high bit
	crcmask = ((((unsigned long)1<<(order-1))-1)<<1)|1;
	crchighbit = (unsigned long)1<<(order-1);

	generate_crc_table();

	// compute missing initial CRC value
	crcinit_direct = crcinit;
	crc = crcinit;
	for (i=0; i<order; i++) {

		bit = crc & 1;
		if (bit) crc^= polynom;
		crc >>= 1;
		if (bit) crc|= crchighbit;
	}	
	crcinit_nondirect = crc;
}



















