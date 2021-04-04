/******************************************
 * BLG520E Cryptography  			      *
 * Project I  							  *
 * Istanbul Technical University          *
 * Spring 2021                            *
 * Ali Üstün                              *
 ******************************************/
#include "kasiski.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int hcf(int n1, int n2) {
    if (n2 != 0)
        return hcf(n2, n1 % n2);
    else
        return n1;
}

int findGCD(int nums[], int length) {
    int maxkeylen = 16;
    int keylen[24];
	int i,j;
	int gcd=0;
	int max=0;

    FILE *fptr = fopen("keylength_score.csv", "w+");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    for(int k = 0; k <= maxkeylen; k++) keylen[k] = 0;

    for (i = 0; i < length; i++) {
        for(j=maxkeylen; j>0 ; j--){
            if(nums[i] % j == 0){
                keylen[j]++;
            }
            if ((((100*keylen[j]+length/2)/length)*((100*keylen[j]+length/2)/length))*j > max){
                max = (((100*keylen[j]+length/2)/length)*((100*keylen[j]+length/2)/length))*j;
                gcd = j;
            }
        }
	}

    int total = 0;

    for(int k=maxkeylen; k>0; k--){
        total += (((100*keylen[k]+length/2)/length)*((100*keylen[k]+length/2)/length))*k;
    }

    float percents = 0;

    for(j=maxkeylen; j>1 ; j--){
        fprintf(fptr,"%.2f, ", (float)(((100*keylen[j]+length/2)/length)*((100*keylen[j]+length/2)/length))*j/total*100.0);
	}
    j = 1;
    fprintf(fptr,"%.2f ", (float)(((100*keylen[j]+length/2)/length)*((100*keylen[j]+length/2)/length))*j/total*100.0);
    fprintf(fptr,"\n");

    for(j=maxkeylen; j>1 ; j--){
        fprintf(fptr,"%d, ", (((100*keylen[j]+length/2)/length)*((100*keylen[j]+length/2)/length))*j);
	}
    j = 1;
    fprintf(fptr,"%d ", (((100*keylen[j]+length/2)/length)*((100*keylen[j]+length/2)/length))*j);
    fprintf(fptr,"\n");
    fclose(fptr);
	return gcd;
}

int findKeyLength(char *text, int stream_length, int pattern_size){
    int key_length;

	char *pattern;

	pattern = (char*) malloc((pattern_size+1)*sizeof(char));


    int length = 0;
    int distance;
    int numbers[COUNT_MAX];
    int count = 0;

    char pattern_list[MAX_PATTERN];

	for(int i = 0; i <= stream_length - 2*pattern_size + 1; i++){
		strncpy(pattern, text + i, pattern_size);
        
        for(int j = i + pattern_size; j <= stream_length - 2*pattern_size + 1; j++){
            if(!strncmp(pattern, (text + j), pattern_size)){
                distance = j - i;
                
                numbers[count] = distance;
                break;
            }
            else distance = 0;
        }
        if(distance != 0){
            length++;
            count++;
        }
        if(count >= COUNT_MAX)break;
	}

    if(count < COUNT_MAX){
        pattern_size = pattern_size + 1;
        for(int i = 0; i <= stream_length - 2*pattern_size + 1; i++){
		strncpy(pattern, text + i, pattern_size);
        
        for(int j = i + pattern_size; j <= stream_length - 2*pattern_size + 1; j++){
            if(!strncmp(pattern, (text + j), pattern_size)){
                distance = j - i;
                if(distance != numbers[count-1])
                    numbers[count] = distance;
                else distance = 0;
                break;
            }
            else distance = 0;
        }
        if(distance != 0){
            length++;
            count++;
        }
        if(count >= COUNT_MAX)break;
	}
    }

    key_length = findGCD(numbers, count);

    return key_length;
}
