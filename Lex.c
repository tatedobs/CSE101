#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "List.h"

int main(int argc, char * argv[]) {
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");
	int count = 0;
	int i = 0;
	char line[255];

	if(argc != 3){
		printf("Usage: Lex <input> <output>\n");
		exit(EXIT_FAILURE);
	}

	if(in == NULL){
		printf("Unable to read from file %s\n", argv[1]);
	}
	if(out == NULL){
		printf("Unable to write to file %s\n", argv[2]);
	}

	while(fgets(line, 255, in) !=NULL){
		count++;
	}

	char Word[count][255];
	rewind(in);


	while(fgets(line, 255, in) != NULL){
		strcpy(Word[i], line);
		i++;
	}

	fclose(in);



	List L = newList();
	append(L, 0);

	for(i = 1; i < count; i++) {
		moveFront(L);
		while(index(L) >= 0) {
			char *temp = Word[i];

			if(strncmp(Word[get(L)], temp, 255) > 0) {
				insertBefore(L, i);
				break;
			}
			moveNext(L);
		}
		if(index(L) < 0) {
			append(L, i);
		}
	}

	moveFront(L);

	for(i=0; i < count; i++) {
		fprintf(out, "%s", Word[get(L)]);
		moveNext(L);
	}

	fclose(out);
	freeList(&L);
}

