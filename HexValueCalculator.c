


void fillColor(struct Color *p, struct Data d, char type)
{
    if (type=='R')
    {
        strcpy(p->name,"Red");
        p->red = d.r;
        p->green = d.g;
        p->blue = d.b;
    }
    else if (type=='G')
    {
        strcpy(p->name,"Green");
        p->red = d.r;
        p->green = d.g;
        p->blue = d.b;
    }
    else if (type=='B')
    {
        strcpy(p->name,"Blue");
        p->red = d.r;
        p->green = d.g;
        p->blue = d.b;
    }
}

void displayHexCodeAsString(const struct Color *s, int n)
{
    int k, j, quotient = 1;
    char temp;
    char hex[17]="0123456789ABCDEF";
    char hexvalue[9];
    int i = 0;
    #define BASE 16
    while (quotient != 0)
    {
        quotient = n / BASE;
        hexvalue[i] = hex[n % BASE];
        n = n / BASE;
        i++;
    }
    k = strlen (hexvalue);
    j = k/2;
    int l = 0;
    while(l<j)
    {
        temp = hexvalue[i];
        hexvalue[l] = hexvalue[k - l -1];
        hexvalue[k- l -1] = temp;
        l++;
    }
    printf("The hex value of the colour is: %s", hexvalue);
}
