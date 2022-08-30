/*
 * mp3tag -- extract MP3 tags
 */
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef enum {Normal, Shell, CShell} Format;


const char *genres[] = {
"Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk",
"Grunge", "Hip-Hop", "Jazz", "Metal", "New Age", "Oldies", "Other",
"Pop", "R&B", "Rap", "Reggae", "Rock", "Techno", "Industrial",
"Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack",
"Euro-Techno", "Ambient", "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion",
"Trance", "Classical", "Instrumental", "Acid", "House", "Game", 
"Sound Clip", "Gospel", "Noise", "AlternRock", "Bass", "Soul", "Punk",
"Space", "Meditative", "Instrumental Pop", "Instrumental Rock",
"Ethnic", "Gothic", "Darkwave", "Techno-Industrial", "Electronic",
"Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy", "Cult",
"Gangsta", "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret", "New Wave", "Psychadelic", "Rave", "Showtunes",
"Trailer", "Lo-Fi", "Tribal", "Acid Punk", "Acid Jazz", "Polka",
"Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk-Rock",
"National Folk", "Swing", "Fast Fusion", "Bebob", "Latin", "Revival",
"Celtic", "Bluegrass", "Avantgarde", "Gothic Rock", "Progressive Rock", 
"Psychedelic Rock", "Symphonic Rock", "Slow Rock", "Big Band",
"Chorus", "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson",
"Opera", "Chamber Music", "Sonata", "Symphony", "Booty Bass",
"Primus", "Porn Groove", "Satire", "Slow Jam", "Club", "Tango",
"Samba", "Folklore", "Ballad", "Power Ballad", "Rhytmic Soul",
"Freestyle", "Duet", "Punk Rock", "Drum Solo", "Acapella",
"Euro-House", "Dance Hall", "Goa", "Drum & Bass", "Club-House",
"Hardcore", "Terror", "Indie", "BritPop", "Negerpunk", "Polsk Punk",
"Beat", "Christian Gangsta Rap", "Heavy Metal", "Black Metal",
"Crossover", "Contemporary Christian", "Christian Rock", "Merengue",
"Salsa", "Trash Metal", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown", "Unknown", "Unknown",
"Unknown", "Unknown", "Unknown", "Unknown"};

/* syserr -- print s + system error message and exit */
static void syserr(const char *s)
{
  perror(s);
  exit(1);
}


/* out -- print a tag on stdout */
static void out(const char *label, const char *tag, size_t max, Format format)
{
  int i;

  switch (format) {
    case Normal:
      printf("\t%s\t", label);
      for (i = 0; i < max && tag[i]; i++) putchar(tag[i]);
      putchar('\n');
      break;
    case Shell:
      printf("export %s;\t%s=", label, label);
      for (i = 0; i < max && tag[i]; i++) {
	if (! isalnum(tag[i])) putchar('\\');
	putchar(tag[i]);
      }
      printf(";\n");
      break;
    case CShell:
      printf("setenv %s ", label);
      for (i = 0; i < max && tag[i]; i++) {
	if (! isalnum(tag[i])) putchar('\\');
	putchar(tag[i]);
      }
      printf(";\n");
      break;
    default:
      assert(!"Cannot happen");
  }
}


/* mp3tag -- get MP3 tags from a file and print them on stdout */
static void mp3tag(const char *filename, Format format)
{
  FILE *f;
  struct {
    char tag[3];				/* = "TAG" */
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    unsigned char genre;
  } info;

  if (! (f = fopen(filename, "r"))) syserr(filename);
  if (fseek(f, -128, SEEK_END) < 0) syserr(filename);
  if (fread(&info, sizeof(info), 1, f) != 1) syserr(filename);
  if (strncmp(info.tag, "TAG", 3) == 0) {
    out("title", info.title, sizeof(info.title), format);
    out("artist", info.artist, sizeof(info.artist), format);
    out("album", info.album, sizeof(info.album), format);
    out("year", info.year, sizeof(info.year), format);
    out("comment", info.comment, sizeof(info.comment), format);
    out("genre", genres[info.genre], strlen(genres[info.genre]), format);
  }
}


/* usage -- print usage message and exit */
static void usage(const char *progname)
{
  fprintf(stderr, "Usage: %s [-s|-c] mp3file\n", progname);
  exit(1);
}


int main(int argc, char *argv[])
{
  Format format = Normal;
  int c, i;

  while ((c = getopt(argc, argv, "sc")) != -1) {
    switch (c) {
      case 's':	format = Shell; break;		/* Output for (Bourne) sh */
      case 'c':	format = CShell; break;		/* Output for Csh */
      default: usage(argv[0]); break;
    }
  }
  if (optind == argc) usage(argv[0]);
  for (i = optind; i < argc; i++) mp3tag(argv[i], format);
  return 0;
}
