/******************************************
 * BLG520E Cryptography  			      *
 * Project I  							  *
 * Istanbul Technical University          *
 * Spring 2021                            *
 * Ali Üstün                              *
 ******************************************/
#include "pattern.h"

int match(char *a, char *b)
{
   int c;
   int position = 0;
   char *x, *y;
   
   x = a;
   y = b;
   
   while(*a)
   {
      while(*x==*y)
      {
         x++;
         y++;
         if(*x=='\0'||*y=='\0')
            break;        
      }  
      if(*y=='\0')
         break;
         
      a++;
      position++;
      x = a;
      y = b;
   }
   if(*a)
      return position;
   else  
      return -1;  
}