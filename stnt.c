#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>


int isVowel(char c){
	return ('a' == c || 'e' == c || 'i' == c || 'o' == c || 'u' == c);
}

char * stnt(char *word){
	char * newword;
	int wlen = strlen(word);

	int firstvowelfired = 0;
	int skip = 0;
	int stepback = 0;

	newword = (char*) malloc(wlen*sizeof(char));

	for(int i = 0; i < wlen; i++){
		char c = word[i];

		//Catch all but the first vowel.
		if(isVowel(c)){
			if (firstvowelfired){
				skip = 1;
			}
			firstvowelfired = 1;
		}

		if(i < wlen-1){
			char n = word[i+1];

			//Don't duplicate.
			if (c == n){
				if (n == 'o'){
					word[i] = 'u';
				}
				else{
					skip = 1;
				}
			}

			if ('g' == c && 'h' == n){
				word[i+1] = 'y';
				skip = 1;
			}

			if ('o' == c && 'u' == n){
				word[i] = 'u';
				word[i+1] = 'u';
			}


			if ('e' == c && 'w' == n){
				word[i] = 'u';
				word[i+1] = 'u';
			}

		}

 		//Fiddle with bits at the end.
		else {
			if (c == 's'){
				word[i] = 'z';
			}
			else if (c == 'y'){
				word[i] = 'i';
			}
			else if (c == 'i'){
				word[i] = 'y';
			}
			else if (c == 'c'){
				word[i] = 'k';
			}
		}

		if (skip) {
			stepback++;
			skip--;
		}
		else {
			newword[i-stepback] = word[i];
		}
		
	}
	return(newword);
}

int main(int argn, char **argv){
	char * word = argv[1];
	if (word[0] == '-'){
		int br, nbytes = 100;
		char *line;

		do {
			line = (char *) malloc(nbytes+1);
			br = getline(&line, (size_t *) &nbytes, stdin);
			if (br > 0){
				line[br-1] = 0;
				printf("%s\n",stnt(line));
			}
		} while (br > 0);

	}
	else {
		printf("%s\n",stnt(word));
	}
}
