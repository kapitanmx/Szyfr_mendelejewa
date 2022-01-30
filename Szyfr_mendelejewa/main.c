#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MENDELEEVE_LENGTH 119
#define MENDELEEVE_COLS_LENGTH 2
#define RESULT_LEN 100
typedef struct string{
	char* str;
	// methods
	void (*append)(struct string*, struct string*);
	int (*len)(struct string*);
	bool (*equal)(struct string*,struct string*);
	void (*lower)(struct string*);
	void (*slice)(struct string*, struct string*, int, int);
	bool (*empty)(struct string*);
	void (*print)(struct string);
	void (*flush)(struct string*);
	void (*append_char)(struct string*,char);
};

struct string new_string(int size){
	struct string s;
	if(size == 0){
		size =1; //for safety
	}
	s.str = (char*) malloc(sizeof(char)*size);
	return s;
}
// tworzy slice ze stringa, pobiera dane z old_str i zapisuje w slice_str, z przedziału from - to.
void string_slice(struct string *old_str, struct string *slice_str, int from,int to){
	if(old_str != NULL && slice_str != NULL) {
		if(!old_str->empty(old_str) && to < old_str->len(old_str) && from < to) {
			slice_str->str = malloc(sizeof(char)* to-from+1);
			int str_pos=0;
			for(int i=from;i<=to;i++) {
				slice_str->str[str_pos] = old_str->str[i];
				str_pos++;
			}
		}
	}
}

// sprawdza czy string jest pusty
bool string_empty(struct string* s){
	if(s != NULL && s->str != NULL){
		return s->str[0] == '\0';
	}
	return true;
}
// dodaje string do stringa, string source pełni rolę stringa dst (docelowego)
void string_append(struct string* source, struct string* to_append){
	int source_size = 0;
	int append_size = 0;
	if(source != NULL && source->len != NULL && to_append->len != NULL && !to_append->empty(to_append)) {
		source_size = source->len(source);
		append_size = to_append->len(to_append);
		if(source_size == 0) {
			source->str = to_append->str;
			return;
		}
		char *new_str = NULL;
		new_str = malloc(sizeof(char)*(source_size+append_size+1));
		strcpy(new_str,source->str);
		int iter = source_size;
		for(int i=0; i<append_size;i++){
			new_str[iter]= to_append->str[i];
			iter++;
		}
		source->str = new_str;
	}
}
// dodaje char do stringa, string source pełni rolę stringa dst (docelowego)
void string_append_char(struct string* source, char to_append){
	int source_size = 0;
	int append_size = 0;
	if(source != NULL && source->len != NULL) {
		source_size = source->len(source);
		if(source_size == 0) {
			source->str = malloc(sizeof(char));
			strcpy(source->str,&to_append);
			return;
		}
		char *new_str = NULL;
		new_str = malloc(sizeof(char)*(source_size+append_size+1));
		strcpy(new_str,source->str);
		new_str[source_size-1] = to_append;
		source->str = new_str;
	}
}

// podaje długość stringa
int string_len(struct string *s){
	int len=0;
	if((*s).str != NULL) {
		for(char *ptr = s->str;*ptr;*++ptr){
			len++;
		}
	}
	return len;
}
// sprawdza czy stringi są równe
bool string_equal(struct string *s1, struct string *s2) {
	if(s1 == NULL && s2 == NULL) {
		return true;
	}
	if(s1->str == NULL && s2->str == NULL){
		return true;
	}

	if(s1->len != NULL && s1->str != NULL && s2->len != NULL && s2->str != NULL) {
		int s1_len = s1->len(s1);
		int s2_len = s2->len(s2);
		if(s1_len != s2_len){
			return false;
		}
		for(int i=0;i<s1_len;i++){
			if(s1->str[i]!=s2->str[i]){
				return false;
			}
		}
		return true;
	}
	
	return false;
}
// konwertuje string s na małe litery.
void string_lower(struct string *s){
	int size_s = s->len(s);
	char *arr;
	arr = malloc(sizeof(char)*size_s);
	int i =0;
	if(size_s>0){
		for(char* ptr= arr,i=0; i<size_s; i++,*++ptr){
			*ptr = (char) tolower((int) s->str[i]);
		}
		s->str = arr;
	}
	
}
void string_flush(struct string *s){
	s->str = NULL;
}

// printuje stringa
void string_print(struct string s){
	for(int i=0;i<s.len(&s);i++){
		printf("%c",s.str[i]);
	}
}
// inicjalizuje string, bez tego nic nie będzie działać prawidłowo! należy wywołać zaraz po deklaracji stringa.
void string_init(struct string *s){
	s->str = NULL;
	s->len = string_len;
	s->append = string_append;
	s->equal = string_equal;
	s->empty = string_empty;
	s->lower = string_lower;
	s->slice = string_slice;
	s->print = string_print;
	s->flush = string_flush;
	s->append_char = string_append_char;
}

// rozwiązuje problem przkeazywania kolumny jako stringa celem porównania
void mendeleeve_col_resolver(struct string* dst,char col[MENDELEEVE_COLS_LENGTH] ){
	if(dst!= NULL){
		for(int i=0;i<MENDELEEVE_COLS_LENGTH;i++){
			if(col[i]!='\0'){
				dst->append_char(dst,col[i]);
			}	
		}
	}
}

typedef struct finder{
	void* (*find)(void*, void*)
};

struct finder new_finder(void* (*engine)(void*, void*)){
	struct finder f;
	f.find = engine;
	return f;
}

int finder_mendelevee(struct string* what,char where[][MENDELEEVE_COLS_LENGTH]){
	if(what != NULL && where != NULL) {
		struct string normalized;
		string_init(&normalized);
		int what_size = what->len(what);
		normalized.str = malloc(sizeof(char)* what_size);
		strcpy(normalized.str,what->str);
		normalized.lower(&normalized);
		for(int i=1; i<MENDELEEVE_LENGTH; i++){
			struct string s;
			string_init(&s);
			mendeleeve_col_resolver(&s,where[i]);
			if(normalized.equal(what,&s)){
				return i;
			}
	 	}
	}
	 return 0; // It's safe, it points to an empty string
}

typedef struct error{
	struct string *message;
};

void new_error(struct error *e,char *message){
	e = malloc(sizeof(struct error));
	string_init(&e->message);
	e->message = message;
}

typedef struct result{
	struct string* out;
	struct error *err;
};

void new_result(struct result *r, void* out, struct error* err){
	r = malloc(sizeof(struct result));
	r-> out = out;
	r-> err = err;
}

void result_string(struct string *result, int *array){
	if(array !=NULL){
		struct string buffer;
		string_init(&buffer);
		int target_len;
		for(int i=0;i<RESULT_LEN&&array[i] != -1;i++){
			target_len = 3;
			if(array[i]<10){
				target_len = 1;
			}
			if(array[i]> 9 && array[i]<100){
				target_len = 2;
			}
			buffer.str = malloc(sizeof(char)*target_len);
			buffer.str = (char) array[i];
			//result->append(result,&buffer);
			result->append_char(result,'*');
		}
	}
}
typedef struct encoder{
	void (*encode)(void*,void*,void*,char [][MENDELEEVE_COLS_LENGTH], char);
};

struct encoder new_encoder(void (*engine)(void*,void*,void*, char [][MENDELEEVE_COLS_LENGTH],char)){
	struct encoder e;
	e.encode = engine;
	return e;
}

void encoder_mendeleeve(struct finder* f,struct string *text,struct result* r, char mendelevee[][MENDELEEVE_COLS_LENGTH],char separator) {
	int res[RESULT_LEN];
	int iterator = 0;
	int main_ptr = 0;
	for(int i=0;i<RESULT_LEN;i++){
		res[i]=-1;
	}
	if(text->len(text) == 0) {
		char message[] = "no text given";
		struct error e;
	    new_error(&e,&message);
		new_result(r,NULL,&e);
		return;
	}
	if(f == NULL) {
		char message[] = "finder required";
		struct error e;
	    new_error(&e,&message);
		new_result(r,NULL,&e);
		return;
	}
	if(mendelevee == NULL) {
		char message[] = "mendelevee required";
		struct error e;
	    new_error(&e,&message);
		new_result(r,NULL,&e);
		return;
	}
	if(separator == '\0'){
		separator = "*";
	}
	int text_len = text->len(text);
	for(int main_ptr=0; main_ptr<text_len;){
		struct string str_slice;
		string_init(&str_slice);
		str_slice.slice(text,&str_slice,main_ptr,main_ptr+1);
		int found =f->find(&str_slice,mendelevee);
		if(found != 0){
			res[iterator++]= found;
			main_ptr +=2;
			continue;
		} 
		if(main_ptr<text_len){
			str_slice.flush(&str_slice);
			str_slice.append_char(&str_slice,text->str[main_ptr]);
			found = f->find(&str_slice,mendelevee);
			if(found != 0) {
				res[iterator++]= found;
				main_ptr++;
				continue;
			}
			char message[] = "could not encode";
				struct error e;
	    		new_error(&e,&message);
				new_result(r,NULL,&e);
				return;
		}
	}
	// for(int i=0;i<100;i++){
	// 	printf("%d",res[i]);
	// 	printf("*");
	// }
	struct string result_str;
	string_init(&result_str);
	result_string(&result_str,&res);
	return new_result(&result_str,&result_str,NULL);
}


// bool isEncodable(char* text, char charList[]) {
// 	for (size_t i = 0; i < textLen(text); i++) {
// 		if (text[i] != charList[i] && charList[i] == NULL) {
// 			return false;
// 		}
// 		return true;
// 	}
// }


// void checkText(char* text, char charList[])
// {
// 	if (text == NULL) 
// 	{
// 		printf("Brak wprowadzonego tekstu. Wprowadz tekst.");
// 	}
// 	if (!isEncodable(text, charList)) 
// 	{
// 		printf("Nie da sie zaszyfrowac danego tekstu");
// 	}
// }

// void encode(char* text, char charList[], int k) {
// 	char* encodedText;
// 	int* result;
// 	for (int i = 0; i < textLen(text); i++) {
// 		if (text[i] == charList[i]) {
// 			result += strcspn(charList, charList[i]);
// 		}
// 	}
// }

int main() {

	/* Lista pierwiastkow (ich symboli) z tablicy Mendelejewa
(numer indeksu w tablicy odpowiada liczbie atomowej pierwiastka) */
char mendelevee[119][MENDELEEVE_COLS_LENGTH]= {
	"","h","li","be","b",
	"c", "n", "o", "f", "ne",
	"na", "mg", "al", "si", "p", 
	"s", "cl", "ar", "k", "ca",
	"sc", "ti", "v", "cr", "mn",
	"fe", "co", "ni", "cu", "zn", 
	"ga", "ge", "as", "se", "br",
	"kr", "rb", "sr", "y", "zr",
	"nb", "mo", "tc", "ru", "rh",
	"pd", "ag", "cd", "in", "sn",
	"sb", "te", "i", "xe", "cs", 
	"ba", "la", "ce", "pr", "nd", 
	"pm", "sm", "eu", "gd", "tb", 
	"dy", "ho", "er", "tm", "yb", 
	"lu", "hf", "ta", "w", "re",
	"os", "ir", "pt", "au", "hg",
	"tl", "pb", "bi", "po", "at",
	"rn", "fr", "ra", "ac", "th",
	"pa", "u", "np", "pu", "am",
	"cm", "bk", "cf", "es", "fm",
	"md", "no", "lr", "rf", "db", 
	"sg", "bh", "hs", "mt", "ds",
	"rg", "cn", "nh", "fl", "mc",
	"lv", "ts", "og"
};
 	struct string text;
	string_init(&text);
	text.str = "li";
	// text.slice(&text,&text2,1,4);
	
	

	struct finder f = new_finder(finder_mendelevee);
	struct encoder e = new_encoder(encoder_mendeleeve);
	printf("Program szyfrujacy podany tekst\n");
	printf("Wprowadz tekst: ");
	// scanf("%s",&text.str);
	struct result r;
	e.encode(&f,&text,&r,mendelevee,'*');
	if(r.err != NULL) {
		printf("error occured:");
		r.err->message->print(*r.err->message);
	}
	if(r.err == NULL && r.out != NULL){
		printf("Result:");
		r.out->print(*r.out);
	}

	return 0;
}