/*
 * 	Filename   : PrintTagInfo.c	
 * 	Description: Mp3tag
 *	Created    : Sunday 28 Feb 2019 23:25:18 IST
 *	Version    : 1.0
 *	Author     : Harish Kumar, harishec031@gmail.com
 *	
 *	Copyright (c) 2019 Harish Kumar
 */

#include "include.h"

int find(char *a);

void PrintTagInfo(const char *FileName, Mp3Info *mp3info)
{
    int ch, i = 0, j = 0;
    
    FILE* mp3file;
    mp3file = fopen(FileName, "r"); /* open mp3file */
    if (mp3file == NULL) {                     
        printf("Error opening the file %s\n", FileName);
        exit(EXIT_FAILURE);
    }

#if 0
    for (int i = 0; i < 128 && (ch = getc(mp3file)); i++)
        putc(ch, stdout);
    rewind(mp3file);
#endif

    char a[4];
    fread(a, 3, 1, mp3file);
    /* find the version of mp3file */
    if (!strncmp(a, "ID3", 3)) 
        printf("\n\t%-5s%s", "VER", ": ID3v2");
    else {
        fseek(mp3file, -128, SEEK_END);
        fread(a, 3, 1, mp3file);
        if (!strncmp(a, "ID3", 3)) 
            printf("\n\t%-5s%s", "VER", ": ID3v1");
    }
    
    i = 0;
#if 0
    while ((ch = getc(mp3file)) != EOF)
#endif
    while ((ch = getc(mp3file)) != EOF && i < 7)
    {
        if (isupper(ch)) 
        {
            a[0] = ch;
            fread(a+1, 3, 1, mp3file);
            a[4] = '\0';
            
            if (find(a)) {
                ++i;
                fseek(mp3file, 4L, SEEK_CUR);
                for (int c = 0; j < 33*16 && (ch = getc(mp3file)) != EOF; ++j) {
                    if (isupper(ch)) {
                        c = getc(mp3file);
                        if(isupper(c)) {
                            fseek(mp3file, -2L, SEEK_CUR);
                            break;
                        }
                    }
                    if (isprint(ch)) {
                        if (c == 0)
                            putc(ch, stdout);
                        else {
                            printf("%c%c", ch, c);
                            c = 0;
                        }
                    }
                }
            }
        }
    }
    putc('\n', stdout);
    fclose(mp3file);
}

/* find: find the right tag */
int find(char *tag)
{
 
#if 1
    #define NTAGS 7
    char *Tags[] = {"TIT2", "TPE1", "TPE2", "TRCK", "TALB", "TYER", "COMM"};
#else 
    #define NTAGS 55
    char *Tags[] = {"TALB", "TPE2", "TSO2", "TSOA", "TPE1", "WOAR", "TSOP", "TPE2", "TBPM", 
                    "COMM", "WCOM", "TCOM", "TSOC", "TPE3", "TCOP", "WCOP", "TDRC", "TYER",
                    "TPOS", "TENC", "TSSE", "WOAF", "TCON", "TIT1", "TKEY", "WORS", "TSRC",
                    "TCMP", "TLAN", "TEXT", "TMED", "TOAL", "TOPE", "TDOR", "TORY", "TOWN",
                    "WPAY", "TPUB", "WPUB", "TRSN", "TRSO", "POPM", "TRDA", "TXXX", "TDRL",
                    "TPE4", "TSST", "WOAS", "TIT3", "TIT2", "TSOT", "TPOS", "TRCK", "USLT",
                    "TEXT"};
#endif

        for (int i = 0; i < NTAGS; i++) 
        {
            if (!strncmp(tag, Tags[i], 4)) {    /* find the right tag and print */
                printf("\n\t%s : ", Tags[i]);
                return 1;
            }
        }
        return 0;
}

