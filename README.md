# MP3-tag-reader-editor
Mp3tag is a powerful and easy-to-use tool to read and edit metadata of audio files.

The MP3tag is a software which will read and display MP3 (ID3) tag information from MP3 files. The software will be desktop based and not web based. The project will be useful to individuals who wish to view and collect MP3 tag data. This project implements a tag editor, wherein users can modify mp3 tag information.


```
$ ./mp3tag -h
 Mp3_Tag_Editor(1)                HELP MENU

 Help menu for Mp3 Tag Reader and Editor:

 For viewing tags: ./mp3_tag_reader -v <.mp3 file>

 For editing tags: ./mp3_tag_reader -e <.mp3 file> <modifier> <tag>

 MODIFIER            FUNCTION
    -t           Modifies Title tag
    -T           Modifies Track tag
    -a           Modifies Artist tag
    -A           Modifies Album tag
    -y           Modifies Year tag
    -c           Modifies Comment tag
    -g           Modifies Genre tag
                                                                         Mp3_Tag_Editor(1)
$ ./mp3tag -v EltonJohn-Something_About_The_Way_You_Look_Tonight.mp3 

PRINTING TAG INFO...

	VER  : ID3v2
	TIT2 : Something About The Way You Look Tonight (Edit Version)
	TPE1 : Elton John/Anne Dudley
	TALB : The Greatest Hits 1970-2002
	TYER : 2008
	TRCK : 12
	TPE2 : Elton John

DONE PRINTING. GOOD BYE!

$ ./mp3tag -e EltonJohn-Something_About_The_Way_You_Look_Tonight.mp3 

	VER  : ID3v2
	TIT2 : Something About The Way You Look Tonight (Edit Version)
	TPE1 : Elton John/Anne Dudley
	TALB : The Greatest Hits 1970-2002
	TYER : 2008
	TRCK : 12
	TPE2 : Elton John
Enter the TAG: TRCK

	TRCK : Found at 56 Can write upto 133
What to write? : 11

DONE WRITING. GOOD BYE!
```
