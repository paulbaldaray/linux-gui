#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 4;        /* border pixel of windows */
static unsigned int gappx           = 25;       /* gap pixel between windows */
static const unsigned int gapmax    = 50;       /* max gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
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
/* static const char col_cyan[]        = "#005577"; */
static const char col_cyan[]        = "#422A38";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray4, col_gray2, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_gray3 },
	[SchemeHid]  = { col_gray3,  col_gray1, col_gray3 },
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
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "tiled",      tile },    /* first entry is default */
	/* { "float",      NULL },    /1* no layout function means floating behavior *1/ */
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
static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };
static const char *miccmd[] = { "amixer", "set", "Capture", "toggle", NULL };
static const char *brupcmd[] = { "brightnessctl", "s", "5%+", NULL };
static const char *brdowncmd[] = { "brightnessctl", "s", "5%-", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_semicolon,  spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,          spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	/* { MODKEY,                       XK_n,          incnmaster,     {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_n,          incnmaster,     {.i = -1 } }, */
	{ MODKEY,                       XK_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,     zoom,           {0} },
	{ MODKEY,                       XK_Tab,        cycleview,      {0} },
	{ MODKEY|ShiftMask,             XK_Tab,        cycleview,      {.i = 1} },
	{ MODKEY,                       XK_r,          reorganizetags,     {0} },
	{ MODKEY|ControlMask,           XK_g,          changegaps,     {.i = 0} },
	{ MODKEY,                       XK_g,          changegaps,     {.i = -5} },
	{ MODKEY|ShiftMask,             XK_g,          changegaps,     {.i = +5} },
	{ MODKEY,                       XK_c,          killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_c,          spawn,          SHCMD("xkill -id $(xdotool getactivewindow)") },
	{ MODKEY,                       XK_space,      cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_x,          togglefloating, {0} },
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

	{ MODKEY|ShiftMask,             XK_n,      show,           {0} },
	{ MODKEY,                       XK_n,      hide,           {0} },

	/* Application shortcuts */
	/* { MODKEY,                       XK_ ,          spawn,          SHCMD("") }, */
	{ MODKEY|ShiftMask,             XK_l,          spawn,          SHCMD("slock") },
	{ MODKEY,                       XK_s,          spawn,          SHCMD("screenshot") },
	{ MODKEY,                       XK_p,          spawn,          SHCMD("toggle picom") },
	{ MODKEY,                       XK_f,          spawn,          SHCMD("google-chrome") },
	{ MODKEY|ShiftMask,             XK_f,          spawn,          SHCMD("firefox") },
	{ 0,                       XF86XK_AudioMute,          spawn,          {.v = mutecmd} },
	{ 0,                       XF86XK_AudioLowerVolume,          spawn,          {.v = voldowncmd} },
	{ 0,                       XF86XK_AudioRaiseVolume,          spawn,          {.v = volupcmd} },
	{ 0,                       XF86XK_AudioMicMute,          spawn,          {.v = miccmd} },
	{ 0,                       XF86XK_MonBrightnessUp,          spawn,          {.v = brupcmd} },
	{ 0,                       XF86XK_MonBrightnessDown,          spawn,          {.v = brdowncmd} },
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
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
};
