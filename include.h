/*
 * 	Filename   : include.h
 * 	Description: Mp3tag
 *	Created    : Sunday 28 Feb 2019 23:25:18 IST
 *	Version    : 1.0
 *	Author     : Harish Kumar, harishec031@gmail.com
 *	
 *	Copyright (c) 2019 Harish Kumar
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "colors.h"

typedef struct _Mp3Info
{
    char Tag[3], Title[100], Album[100], Year[4],
         Track[3], Artist[100], Comment[100];
    unsigned char Genre;
} Mp3Info;

void ModifyTag(char *Filename);
void PrintTagInfo(const char *FileName, Mp3Info *mp3info);
void Out(const char *Label, const char *Tag, size_t Max);
void WriteLabel(const char *Label, const char *LabelInfo, char *Tag, size_t Max, Mp3Info mp3info, FILE* mp3file);
