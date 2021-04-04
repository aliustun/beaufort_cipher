/******************************************
 * BLG520E Cryptography  			      *
 * Project I  							  *
 * Istanbul Technical University          *
 * Spring 2021                            *
 * Ali Üstün                              *
 ******************************************/
#ifndef KASISKI_H
	#define KASISKI_H	

#define COUNT_MAX 255
#define MAX_PATTERN 32

/* 
 * This function finds the same pattern in the string, and returns
 * its location if there is any. Then, returns the key length.
 */
int findKeyLength(char *text, int stream_length, int pattern_size);


/*
 * This function finds the greatest common divisor of the distances between 
 * same patterns. 
 */
int findGCD(int *nums, int length);


/*
 * Finds the highest common fraction of two numbers.
*/
int hcf(int n1, int n2);

#endif