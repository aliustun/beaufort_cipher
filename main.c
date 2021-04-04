/******************************************
 * BLG520E Cryptography  			      *
 * Project I  							  *
 * Istanbul Technical University          *
 * Spring 2021                            *
 * Ali Üstün                              *
 ******************************************/

#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "kasiski.h"
#include "cryptanalysis.h"

int main(int argc, char *argv[]){

	FILE *ciphertext_txt;
	FILE *plaintext_txt;
	char *ciphertext 	= NULL;
	char *plaintext 	= NULL; 

	size_t stream_length;

	/*Opens the ciphertext.txt*/
	if((ciphertext_txt = fopen("./ciphertext_3.txt", "r")) == NULL){
		printf("cannot open ciphertext_3.txt!!!\n");
		exit(1);
	}

	/*Finds the size of the file in bytes*/
	fseek(ciphertext_txt, 0, SEEK_END);
	stream_length = ftell(ciphertext_txt);
	ciphertext = (char*) malloc((stream_length+1)*sizeof(char));

	/*Goes to beginning of the file and pass the file into a string*/
	fseek(ciphertext_txt, 0, SEEK_SET);
	fread(ciphertext, stream_length, 1, ciphertext_txt);

	/*Creates a new pointer to save a vigenere version of ciphertext*/
	
	char *vigenere_cipher 	= NULL;
	vigenere_cipher = (char*) malloc((stream_length+1)*sizeof(char));

	for(int i = 0; i < stream_length; i++){
		vigenere_cipher[i] = 'Z' - (ciphertext[i]-'A');
	}

	//printf("new key: %s\n", "HAMDI"-"AAAAA" + "CIPHE");

	FILE *fptr = fopen("vigenere_transformed.txt", "w+");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }

	fprintf(fptr,"%s", vigenere_cipher);

	fclose(fptr);
	

	/*Finds the highest probabity key length*/
	int pattern_size = 3;
	int key_length = findKeyLength(vigenere_cipher, stream_length, pattern_size);

	printf("key_length is %d\n", key_length);

	freq_analysis(vigenere_cipher, stream_length, key_length);
	
	system("pause");
	return 0;
}
