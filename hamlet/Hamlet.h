struct string {
    char * place;
    unsigned int length;
};

enum {
    END = -2,
    LESS,
    EQUAL,
    MORE,
    BEGIN
};


unsigned int Bytesnumb (FILE * file)
{

    unsigned int Number = 0;
    unsigned int pos = fseek (file, 0L, SEEK_END);

    assert (pos == 0);

    Number = ftell (file);

    rewind (file);

    return Number;
}
char * Buffctor (unsigned int nbytes)
{
    char * buff = (char *) calloc (nbytes + 1, sizeof (char *));

    assert (buff != NULL);

    return buff;
}
void Freader (char * buff, unsigned int nbytes, FILE * file)
{
    unsigned int numbcheck = fread (buff, sizeof(char), nbytes, file);

    if (numbcheck != nbytes) {
        printf ("Number of read symbols:    %u\n", numbcheck);
        printf ("Number of symbols if file: %u\n", nbytes);
    }
}

unsigned int Linesnumb (char * buff, unsigned int nbytes)
{
    unsigned int Lnumb = 0;

    for (int i = 0; i < nbytes; i++)
    {
        if (* (buff + i) == '\n')
        {
            * (buff + i) = '\0';
            Lnumb++;
            i++;
            while (* (buff + i) == '\t' || * (buff + i) == ' ')
            {
                i++;
            }
            if ( *(buff + i) == '\n')
            {
                Lnumb--;
            }
            i--;
        }
    }

    return Lnumb;
}

void Passtrash (char * buff, unsigned int * i)
{
    unsigned int numb = * i;
    numb++;
    while ((* (buff + numb) == '\t') || (* (buff + numb) == ' '))
    {
        numb++;
    }
    if ( * (buff + numb) == '\0')
    {
        numb++;
    }
    numb--;
    * i = numb;
}

struct string * Strinit (char * buff, unsigned int nlines, unsigned int nbytes)
{
    assert (nlines != 0);
    struct string * mass = (struct string *) calloc (nlines, sizeof (struct string));
    assert (mass != NULL);
    unsigned int j = 0;
    unsigned int length = 0;
    for (unsigned int i = 0; i < nbytes || j < nlines; i++)
    {
        length++;
        if (* (buff + i) == '\0')
        {
            length = length - 1;
            ((mass + j) -> place) = (buff + i) - length;
            ((mass + j) -> length) = length;
            j++;
            Passtrash (buff, &i);
            length = 0;
        }
    }
    return mass;
}

unsigned int Maxline (struct string * indexmass, unsigned int nlines)
{
    unsigned int max = indexmass -> length;

    for (unsigned int i = 0; i < nlines; i++)
    {
        if ((indexmass + i) -> length >= max)
        {
            max = (indexmass + i) -> length;
        }
    }

    return max;
}

char My_Toupper (char c)
{
    char newc = 0;
    newc = c;
    if ((c >= 'a')&&(c <= 'z'))
    {
        newc = c - 32;
    }
    return newc;
}

// возвращает -1, если символ == буква
// возвращает  1, если символ != буква
int Not_Alpha (char c)
{
    if (((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int Symbcomp (char * symb1, char * symb2)
{
    return (My_Toupper (* symb1) < My_Toupper (* symb2)) ? LESS : MORE;
}

int StrcompB (char * str1, unsigned int length1,
               char * str2, unsigned int length2)
{
    while ((* str1 != '\0') && (* str2 != '\0'))
    {
        while (Not_Alpha (* str1) == 1)
        {
            str1++;
        }
        while (Not_Alpha (* str2) == 1)
        {
            str2++;
        }
        if ((* str1 == '\0') && (* str2 == '\0'))
        {
            return (length1 < length2) ? LESS : MORE;
        }
        if (My_Toupper (* str1) != My_Toupper (* str2))
        {
            return Symbcomp (str1, str2);
        }
        str1++;
        str2++;
    }
    if (length1 == length2)
    {
        return EQUAL;
    }
    return (length1 < length2) ? LESS : MORE;
}
// сравнение строк с конца
int StrcompE (char * str1, unsigned int length1,
               char * str2, unsigned int length2)
{
    str1 += length1;
    str2 += length2;
    int temp1 = length1;
    int temp2 = length2;
    while (temp1 > 0 && temp2 > 0) {
        while (Not_Alpha (* str1) == 1)
        {
            str1--;
            temp1--;
        }
        while (Not_Alpha (* str2) == 1)
        {
            str2--;
            temp2--;
        }
        if (My_Toupper (* str1) != My_Toupper (* str2))
        {
            return Symbcomp (str1, str2);
        }
        str1--;
        temp1--;
        str2--;
        temp2--;
    }
    if ((Not_Alpha (* str1) == 1) && (Not_Alpha (* str2) == 1))
    {
        return (My_Toupper (* str1) < My_Toupper (* str2)) ? LESS : MORE;
    }
    return (length1 < length2) ? LESS : MORE;
}
// сортировочка
void Strsort (struct string * indexmass, int nlines, int mode)
{
    for (unsigned int npass = 0; npass < nlines - 1; npass++)
    {
        for (unsigned i = 0; i < nlines - npass - 1; i++)
        {
            int resultcmp = 0;

            if (mode == BEGIN)
            {
                resultcmp = StrcompB ((indexmass + i) -> place, (indexmass + i) -> length,
                                      (indexmass + i + 1) -> place, (indexmass + i + 1) -> length);
            }

            if (mode == END)
            {
                resultcmp = StrcompE ((indexmass + i) -> place, (indexmass + i) -> length,
                                      (indexmass + i + 1) -> place, (indexmass + i + 1) -> length);
            }

            if (resultcmp != LESS)
            {
                char * tempad = (indexmass + i) -> place;
                unsigned int templ = (indexmass + i) -> length;

                (indexmass + i) -> place = (indexmass + i + 1) -> place;
                (indexmass + i) -> length = (indexmass + i + 1) -> length;

                (indexmass + i + 1) -> place = tempad;
                (indexmass + i + 1) -> length = templ;
            }

        }
    }
}
// бредогенератор
struct string * PulpGtor (struct string * indexmass, unsigned int nlines, unsigned int plines)
{
    struct string * poemass = (struct string *) calloc (nlines, sizeof (struct string));
    srand (time(NULL));
    int delta = 5;
    int np = 0;
    for (int i = 0; i < plines / 4; i++)
    {
        int rifm1 = rand () % nlines;
        int rifm2 = rand () % nlines;
        for (int j = 0; j < 4; j++)
        {
            (poemass + np) -> place = (indexmass + rifm1 + rand () % delta) -> place;
            (poemass + np) -> length = (indexmass + rifm2 + rand () % delta) -> length;
            np++;
        }
    }
    return poemass;
}

// вывод строки
void Sprinter (char * str, FILE * file)
{
    while (* str != '\0')
    {
        putc (*str, file);
        str++;
    }
    putc ('\n', file);
}
// вывод отсортированного текста
void Fprinter (struct string * indexmass, int nlines, FILE * file, int mode)
{
    unsigned int maxlength = Maxline (indexmass, nlines);
    if (mode == BEGIN)
    {
        for (unsigned int i = 0; i < nlines; i++)
        {
            Sprinter ((indexmass + i) -> place, file);
        }
    }
    if (mode == END)
    {
        for (unsigned int i = 0; i< nlines; i++)
        {
            int temp = 0;
            while (temp < maxlength - ((indexmass + i) -> length))
            {
                putc (' ', file);
                temp++;
            }
            Sprinter ((indexmass + i) -> place, file);
        }
    }
}
