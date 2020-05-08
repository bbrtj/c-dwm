/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 13;        /* gaps between windows */
static const unsigned int row_clients = 2;
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Icons:size=13" };
static const char dmenufont[]       = "Droid Sans Mono:size=11";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#333333";
static const char col_gray2[]       = "#cccccc";
static const char col_white[]       = "#eeeeee";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray2, col_black, col_gray1 },
	[SchemeTitle] = { col_gray2, col_black, col_gray1 },
	[SchemeSel]  = { col_white, col_gray1, col_gray1  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Vivaldi",  NULL,       NULL,       1,       0,           -1 },
	{ "Telegram", NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Slack", NULL,       NULL,       1 << 1,       0,           -1 },
	{ "Thunderbird", NULL,       NULL,       1 << 2,       0,           -1 },
	{ "DBeaver", NULL,       NULL,       1 << 4,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.65; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      deck },
	{ "",      tile },
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ ControlMask,                  KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_black, "-nf", col_gray2, "-sb", col_gray1, "-sf", col_white, NULL };
static const char *termcmd[]  = { "st", "-e", "tmux" };
static const char *rangercmd[]  = { "st", "-e", "ranger" };
static const char *pstatustimecmd[]  = { "pstatus", "--type", "time", "--update" };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Menu,   spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Return, rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_dollar, view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_dollar, tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_ampersand,                      0)
	TAGKEYS(                        XK_bracketleft,                      1)
	TAGKEYS(                        XK_braceleft,                      2)
	TAGKEYS(                        XK_braceright,                      3)
	TAGKEYS(                        XK_parenleft,                      4)
	TAGKEYS(                        XK_equal,                      5)
	TAGKEYS(                        XK_asterisk,                      6)
	{ MODKEY|ShiftMask,             XK_F12,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkRootWin,           MODKEY,         Button1,        spawn,          {.v = rangercmd} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = pstatustimecmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

