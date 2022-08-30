/*
 * 	Filename   : main.c	
 * 	Description: Mp3tag
 *	Created    : Sunday 28 Feb 2019 23:25:18 IST
 *	Version    : 1.0
 *	Author     : Harish Kumar, harishec031@gmail.com
 *	
 *	Copyright (c) 2019 Harish Kumar
 */

#include "include.h"

#define EXTENSION ".mp3"

int main(int argc, char *argv[])
{
    FILE* helpfptr;

    if (argc < 2) {
        printf("Error: ./mp3_tag_reader: Invalid Arguments\n");
        printf("Usage: ./mp3_tag_reader -h for help\n");
        exit(EXIT_FAILURE);
    }

    int ch;
    switch(*(*(argv + 1) + 1))
    {
        case 'h':
            helpfptr = fopen("help_text.txt", "r");
            if (helpfptr == NULL) {
                printf("Help menu is missing dude.\n");
                return 0;
            }
            while ((ch = fgetc(helpfptr)) != EOF)
                putc(ch, stdout);
            getchar();
            break;

        case 'v': /* Check if the file is an mp3 file */     
            if (strstr(argv[2], EXTENSION) != NULL) { 
                printf("\n" BOLDRED "PRINTING TAG INFO..." RESET "\n"); 
                PrintTagInfo(argv[2], NULL);
                printf("\n" BOLDRED "DONE PRINTING." BOLDMAGENTA " GOOD BYE" RESET ".\n\n"); 
            }
            else
                printf("Please include one .mp3 file.\n");
            break;

        case 'e': /* Check if the file is an mp3 file */
            if (strstr(argv[2], EXTENSION) != NULL)  
                ModifyTag(argv[2]);
            else
                printf("Please include one .mp3 file.\n");
            break;
    }
    return 0;
}

