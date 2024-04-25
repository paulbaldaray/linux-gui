//Modify this file to change what commands output to your statusbar, and recompile using the make command.

#define SCRIPT "~/linux-gui/dwmblocks/scripts/"

static const Block blocks[] = {
	/*Icon | Command                    | Interval | Signal*/
	{"",     SCRIPT"bluetooth",           1,         0},
	{"",     SCRIPT"date",                1,         0},
	{"",     SCRIPT"battery",             1,         0},
	{"",     SCRIPT"volume",              1,         0},
	{"",     SCRIPT"mic",                 1,         0},
	{"",     SCRIPT"bright",              1,         0},
	{"",     SCRIPT"wifi",                1,         0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '|';
