#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdbool.h>

/* Lista pierwiastkow (ich symboli) z tablicy Mendelejewa
(numer indeksu w tablicy odpowiada liczbie atomowej pierwiastka) */

const char *charList[] = {
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

size_t textLen(char* text) {
	return sizeof(text) / sizeof(text[0]);
}

size_t charListLen(char charList[]) {
	return sizeof(charList) / sizeof(charList[0]);
}

bool isEncodable(char* text, char charList[]) {
	for (size_t i = 0; i < textLen(text); i++) {
		if (((text[i] && text[i+1]) || (text[i]) == charList[i]) &&
			(charList[i] != NULL)) 
		{
			return true;
		} 
	}
	return false;
}

void checkText(char* text, char* charList)
{
	if (text == NULL) 
	{
		printf("Brak wprowadzonego tekstu. Wprowadz tekst.");
	}
	if (!isEncodable(text, charList)) 
	{
		printf("Nie da sie zaszyfrowac danego tekstu");
	}
	printf("Wprowadzony tekst: %s", text);
}

char* encodedText(char* text, char* result, char* charList) {
	int charIndex;
	for (int i = 0; i < textLen(text); i++) {
		if (!isEncodable(text, charList)) {
			return 0;
		}
		if (((text[i] && text[i+1]) || (text[i]) == charList[i]) &&
			((text[i] && text[i+1]) || (text[i]) != NULL) &&
			(charList[i] != NULL))
		{
			if (text[i] == ' ') {
				result[i] += '**';
			}
			charIndex = strcspn(charList, text);
			result[i] += (charIndex + 1) + '*';
		}
	}
	return result;
}

int main() {
	char* text = (char*)malloc(sizeof(text));
	char* result = (char*)malloc(sizeof(result));
	printf("Program szyfrujacy podany tekst\n");
	printf("Wprowadz tekst: ");
	scanf_s("%s", &text);
	checkText(text, charList);
	printf("Wprowadzony tekst: %s\n", text);
	printf("Tekst po zaszyfrowaniu: %s\n", encodedText(text, result, charList));
	return 0;
}