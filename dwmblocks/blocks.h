//Modify this file to change what commands output to your statusbar, and recompile using the make command.

#define SCRIPT "/home/paul/suckless/dwmblocks/scripts/"

static const Block blocks[] = {
	/*Icon | Command                    | Interval | Signal*/
	{"",     SCRIPT"date",                1,         0},
	{"",     SCRIPT"battery",             60,        0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '|';
