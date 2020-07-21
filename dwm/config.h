/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static unsigned int gappx           = 10;       /* gap pixel between windows */
static unsigned int gapalt          = 0;        /* alternate gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int vertpad            = 0;       /* vertical padding of bar */
static const int sidepad            = 0;       /* horizontal padding of bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#151515";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#888888";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray2, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_gray3 },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Pinta",   NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Firefox", NULL,     NULL,           1 << 8,    0,          0,          -1,        -1 },
	{ "st",      NULL,     NULL,           0,         0,          1,          -1,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         1,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tiled",      tile },    /* first entry is default */
	{ "float",      NULL },    /* no layout function means floating behavior */
	{ "monoc",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_semicolon,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,          spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,      {0} },
	{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
	/* { MODKEY,                       XK_n,          incnmaster,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_n,          incnmaster,     {.i = -1 } }, */
	{ MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,     zoom,           {0} },
	{ MODKEY,                       XK_Tab,        cycleview,      {0} },
	{ MODKEY|ShiftMask,             XK_Tab,        cycleview,      {.i = 1} },
	{ MODKEY|ControlMask,           XK_Tab,        reorganize,     {0} },
	{ MODKEY,                       XK_g,          changegaps,     {.i = -1} },
	{ MODKEY,                       XK_c,          killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_c,          spawn,          SHCMD("xkill -id $(xdotool getactivewindow)") },
	{ MODKEY,                       XK_space,      cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_m,          togglefloating, {0} },
	/* { MODKEY,                       XK_0,          view,           {.ui = ~0 } }, */
	{ MODKEY,                       XK_0,          tag,            {.ui = ~0 } },
	/* { MODKEY,                       XK_comma,      focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period,     focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                          0)
	TAGKEYS(                        XK_2,                          1)
	TAGKEYS(                        XK_3,                          2)
	TAGKEYS(                        XK_4,                          3)
	TAGKEYS(                        XK_5,                          4)
	TAGKEYS(                        XK_6,                          5)
	TAGKEYS(                        XK_7,                          6)
	TAGKEYS(                        XK_8,                          7)
	TAGKEYS(                        XK_9,                          8)
	{ MODKEY|ShiftMask,             XK_q,          quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,          restart,        {0} },
	{ MODKEY,                       XK_z,          togglefullscr,      {0} },

	/* Application shortcuts */
	/* { MODKEY,                       XK_ ,          spawn,          SHCMD("") }, */
	{ MODKEY,                       XK_f,          spawn,          SHCMD("firefox") },
	{ MODKEY|ShiftMask,             XK_f,          spawn,          SHCMD("firefox --private-window") },
	{ MODKEY|ShiftMask,             XK_semicolon,  spawn,          SHCMD("book") },
	{ MODKEY,                       XK_p,          spawn,          SHCMD("toggle picom") },
	{ MODKEY,                       XK_v,          spawn,          SHCMD("pavucontrol") },
	{ MODKEY,                       XK_comma,      spawn,          SHCMD("sudo backlight -100") },
	{ MODKEY,                       XK_period,     spawn,          SHCMD("sudo backlight 100") },
	{ MODKEY|ShiftMask,             XK_comma,      spawn,          SHCMD("sudo backlight -10") },
	{ MODKEY|ShiftMask,             XK_period,     spawn,          SHCMD("sudo backlight 10") },
	{ MODKEY|ControlMask,           XK_comma,      spawn,          SHCMD("sudo backlight -1") },
	{ MODKEY|ControlMask,           XK_period,     spawn,          SHCMD("sudo backlight 1") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
