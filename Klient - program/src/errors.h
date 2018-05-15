/**
 * Program klienta pre komunikacne protokoly DLMS/COSEM a IEC 104
 * Funkcie na vypis chybovych sprav a napovedy
 * Autor: Jan Pristas, Vysoke uceni technicke v Brne, Fakulta informacnich technologii
 **/

#include <iostream>

enum eCodes {
	EHELP, // Ziadost o vypis napovedy
	EARG, // Zle vstupne argumenty
	EADR, // IP adresa je povinny udaj, ak nie je ziadane o napovedu
	ENUM, // Hodnota musi byt ciselna
	EPORT, // Hodnota portu mimo povoleny rozsah
	EHLP, // Ziadost o napovedu nemoze byt kombinovana s inym parametrom
	EPROT, // Jeden z protokolov DLMS/COSEM, IEC 104 musi byt zadany
	EFILE, // Chyba pri otvarani suboru
	ESOCK, // CHyba pri vytvarani socketu
	EADDR, // Zla IP adresa
	ECON, // Chyba pri vytvarani spojenia
	ESEND, // Chyba pri zasielani spravy
	EREAD, // CHyba pri citani spravy
	ERECV, // Chyba pri prijimani spravy
	EUNK // Neznama chyba
};

void helpMessage();
void errorMsg(int e_code);