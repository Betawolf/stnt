#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int isVowel(char c){
	return ('a' == c || 'e' == c || 'i' == c || 'o' == c || 'u' == c);
}

int main(int argn, char **argv){
	char * word = argv[1];
	char * newword;
	int wlen = strlen(word);
	printf("%s:%d\n",word,wlen);

	int firstvowelfired = 0;
	int skip = 0;
	int stepback = 0;

	newword = (char*) malloc(wlen*sizeof(char));

	for(int i = 0; i < wlen; i++){

		//Catch all but the first vowel.
		if(isVowel(word[i])){
			if (firstvowelfired){
				skip = 1;
			}
			firstvowelfired = 1;
		}

		//Don't duplicate.
		if(i > 2 && word[i] == word[i-1]){
			skip = 1;
		}

		//Fiddle with bits at the end.
		if ( i == wlen - 1){
			if (word[i] == 's'){
				word[i] = 'z';
			}
			else if (word[i] == 'y'){
				word[i] = 'i';
			}
			else if (word[i] == 'i'){
				word[i] = 'y';
			}
		}

		if (skip) {
			stepback++;
			skip = 0;
		}
		else {
			newword[i-stepback] = word[i];
		}
		
	}
	printf("%s\n",newword);
}
