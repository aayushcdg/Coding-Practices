/*
   program:         ajain74_PRG355B.231.L1.c
   student name:    Aayush Jain
   student number:  125609214
   section:         PRG355B
   purpose:         Solution to lab #1
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void spacesToXs(char *x)
{
    int i=0;
    while (*(x+i))
        {
            if (*(x+i) == ' ')
                *(x+i) = 'X';
            i++;
        }
     
}


unsigned int howManyVowels(const char *s)
{
    int i = 0;
    unsigned int num = 0;
     while (s[i]) {
         if (*(s+i) == 'a' || *(s+i) == 'e' || *(s+i) == 'i' || *(s+i) == 'o' || *(s+i) == 'u' || *(s+i) == 'A' || *(s+i) == 'E' || *(s+i) == 'I' || *(s+i) == 'O' || *(s+i) == 'U')
           num++;
         i++;
       }
     return num;
}


void mirrorImage(char *s)
{

    int i, k, j, p;
    unsigned int l = strlen(s);
     if(l<4)
    {
        printf("Length of string must be >=4 for: ");
        
    }
    else{
        k=0;
        i=(l-1)/2 -1;
        while (k<((i/2)+1))
        {
            p = *(s+k);
            *(s+k)=*(s+i);
            *(s+i)=p;
            k++;
            i--;
        }
        k=(l-1)/2;
        j=k+1;
        i= l-1;
        while(j<=(k+l)/2)
        {
            p= *(s+j);
            *(s+j)=*(s+i);
            *(s+i)=p;
            j++;
            i--;
        }
    }
}

