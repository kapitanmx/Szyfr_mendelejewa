#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

size_t textLen(char* text) {
	return sizeof(text) / sizeof(text[0]);
}

size_t charListLen(char* charList) {
	return sizeof(charList) / sizeof(charList[0]);
}

/* Lista pierwiastkow (ich symboli) z tablicy Mendelejewa
(numer indeksu w tablicy odpowiada liczbie atomowej pierwiastka) */

char* charList[] = { '\0',
	'H', 'He', 'Li', 'Be', 'B',
	'C', 'N', 'O', 'F', 'Ne',
	'Na', 'Mg', 'Al', 'Si', 'P', 
	'S', 'Cl', 'Ar', 'K', 'Ca',
	'Sc', 'Ti', 'V', 'Cr', 'Mn',
	'Fe', 'Co', 'Ni', 'Cu', 'Zn', 
	'Ga', 'Ge', 'As', 'Se', 'Br',
	'Kr', 'Rb', 'Sr', 'Y', 'Zr',
	'Nb', 'Mo', 'Tc', 'Ru', 'Rh',
	'Pd', 'Ag', 'Cd', 'In', 'Sn',
	'Sb', 'Te', 'I', 'Xe', 'Cs', 
	'Ba', 'La', 'Ce', 'Pr', 'Nd', 
	'Pm', 'Sm', 'Eu', 'Gd', 'Tb', 
	'Dy', 'Ho', 'Er', 'Tm', 'Yb', 
	'Lu', 'Hf', 'Ta', 'W', 'Re',
	'Os', 'Ir', 'Pt', 'Au', 'Hg',
	'Tl', 'Pb', 'Bi', 'Po', 'At',
	'Rn', 'Fr', 'Ra', 'Ac', 'Th',
	'Pa', 'U', 'Np', 'Pu', 'Am',
	'Cm', 'Bk', 'Cf', 'Es', 'Fm',
	'Md', 'No', 'Lr', 'Rf', 'Db', 
	'Sg', 'Bh', 'Hs', 'Mt', 'Ds',
	'Rg', 'Cn', 'Nh', 'Fl', 'Mc',
	'Lv', 'Ts', 'Og', '\0'
};

bool isEncodable(char* text, char charList[]) {
	for (size_t i = 0; i < textLen(text); i++) {
		if (text[i] != charList[i] && charList[i] == NULL) {
			return false;
		}
		return true;
	}
}


void checkText(char* text, char charList[])
{
	if (text == NULL) 
	{
		printf("Brak wprowadzonego tekstu. Wprowadz tekst.");
	}
	if (!isEncodable(text, charList)) 
	{
		printf("Nie da sie zaszyfrowac danego tekstu");
	}
}

void encode(char* text, char charList[], int k) {
	char* encodedText;
	int* result;
	for (int i = 0; i < textLen(text); i++) {
		if (text[i] == charList[i]) {
			result += strcspn(charList, charList[i]);
		}
	}
}

int main() {
	char* text = (char*)malloc(sizeof(text));
	printf("Program szyfrujacy podany tekst\n");
	printf("Wprowadz tekst: ");

	return 0;
}