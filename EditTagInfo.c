/*
 * 	Filename   : EditTagInfo.c	
 * 	Description: Mp3tag
 *	Created    : Sunday 28 Feb 2019 23:25:18 IST
 *	Version    : 1.0
 *	Author     : Harish Kumar, harishec031@gmail.com
 *	
 *	Copyright (c) 2019 Harish Kumar
 *
 */

#include "include.h"

int find(char *a);
long read_tag_info(char *ary, FILE* mp3file);

void ModifyTag(char *FileName)
{
    char flag;
    FILE* mp3file, *outfile;
    Mp3Info mp3info;
    
    PrintTagInfo(FileName, &mp3info);
    mp3file = fopen(FileName, "r");
    if (mp3file == NULL) {
        printf("Error opening the file %s\n", FileName);
        exit(EXIT_FAILURE);
    }
    outfile = fopen("outfile.mp3", "w");
    if (outfile == NULL) {
        printf("Error opening the file %s\n", "outfile.mp3");
        exit(EXIT_FAILURE);
    }

    char a[4] = {0}, str[100], s[4] = {0};
    int ch;
    int i = 0;
    fseek(mp3file, 3L, SEEK_SET);
    
    printf(BOLDRED "Enter the TAG: " RESET);
    scanf("%[^\n]s", a); getchar();
    
    if (!find(a)) 
    {
        printf("No such TAG\n");
        return; 
    }
    
    while ((ch = getc(mp3file)) != EOF)
    {
        s[0] = ch;
        if(isupper(ch))
            fread(a + 1, 3, 1, mp3file);
        else {
            putc(ch, outfile);
            continue;
        }
        s[4] = '\0';
        fseek(mp3file, -3L, SEEK_CUR);
        
        if (!strncmp(a, s, 4))
        {
            printf("Found at %ld ", ftell(mp3file));
                    long pos = ftell(mp3file);
                    fread(outfile, 4, 1, mp3file);
                    long tell = read_tag_info(mp3info.Title, mp3file);
                    printf("Can write upto %ld\n", tell);
                    //fseek(mp3file, -tell, SEEK_CUR);

                    printf("What to write? : ");
                    scanf("%[^\n]s", str);

                    for (long i  = 0; i < tell - ftell(mp3file); ++i) 
                    {
                        if (i < strlen(str))
                            putc(str[i++], outfile);
                        else
                            putc(0x00, outfile);
                    }
                    break;
        } else
            putc(ch, outfile);
    }
    
    while((ch = getc(mp3file)) != EOF)
        putc(ch, outfile);
    fclose(mp3file);
}

long read_tag_info(char *ary, FILE* mp3file)
{
    int ch, c;
    for (int i = 0, j = 0; j < 33*16 && (ch = getc(mp3file)) != EOF; ++j) 
    {
        if (isupper(ch)) {
            c = getc(mp3file);
            if(isupper(c)) {
                fseek(mp3file, -2L, SEEK_CUR);
                return ftell(mp3file);
            }
        }
    }
}
