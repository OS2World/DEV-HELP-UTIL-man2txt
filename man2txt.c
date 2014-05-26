#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    FILE *in, *out;
    int i;
    int buf[1024];

    i=0;

    if(argc != 3)
    {
      fprintf(stderr, "Usage: man2txt [man page] [output file]\n");
      exit(1);
    }

    if( stricmp(argv[1], argv[2])==0 )
    {
      fprintf(stderr, "[man page] and [output file] can not be the same.\n");
      exit(1);
    }

    if ((in = fopen(argv[1], "r+b")) == NULL)
    {
        fprintf(stderr, "Cannot open input file.\n");
        return 1;
    }

    if ((out = fopen(argv[2], "w+b")) == NULL)
    {
        fprintf(stderr, "Cannot open output file.\n");
        return 1;
    }

    while(!feof(in))
    {
        while((buf[i]=fgetc(in))!=0x0D && !feof(in))
        {
            if(buf[i] == 8 && i > 0)
            {
                buf[--i]=fgetc(in);
                i++;
            }
            else i++;
        }

        if(!feof(in))
        {
            for(i=0;buf[i]!=0x0D;i++)
            {
                fputc(buf[i], out);
            }

            fputc(buf[i], out);
            i=0;
        }
    }

    fclose(in);
    fclose(out);

    return 0;
}
