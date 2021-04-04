/******************************************
 * BLG520E Cryptography  			      *
 * Project I  							  *
 * Istanbul Technical University          *
 * Spring 2021                            *
 * Ali Üstün                              *
 ******************************************/
#include <stdio.h>
#include "cryptanalysis.h"

void freq_analysis(char *text, int textLength, int keyLength) {
    int i, c, count[10][26]={{0}}, x;

    FILE *fptr = fopen("freq_analysis.csv", "w+");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }

    for(i = 0; i<25; i++){
        fprintf(fptr, "%c, ", i + 'A');
    }
    fprintf(fptr, "%c\n", 25 + 'A');
    
    for(i=0; i<keyLength; i++){
        for (c=i; c<textLength; c=c+keyLength) {
        /** Considering characters from 'A' to 'Z' only and ignoring others. */
          if (text[c] >= 'A' && text[c] <= 'Z') {
             x = text[c] - 'A';
             count[i][x]++;
          }
       }

       for (c = 0; c < 25; c++){
           fprintf(fptr, "%d, ", count[i][c]);
       }
       fprintf(fptr, "%d\n", count[i][25]);
       printf("i:%d \n", i);
    }

    fclose(fptr);
    return;
}
