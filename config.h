/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 1;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Arial:size=10", "Icons:size=13" };
static const char dmenufont[]       = "DejaVu Sans Mono:size=11";
static const char col_black[]       = "#000000";
static const char col_gray1[]       = "#333333";
static const char col_gray2[]       = "#707070";
static const char col_gray3[]       = "#cccccc";
static const char col_white[]       = "#eeeeee";
static const char col_unsel[]       = "#b16286";
static const char coltest1[]       = "#d65d0e";
static const char coltest2[]       = "#fb4934";

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_black, col_unsel },
	[SchemeTitle] = { col_gray3, col_black, coltest1 },
	[SchemeDimmed] = { col_gray2, col_black, coltest2 },
	[SchemeSel]  = { col_white, col_gray1, col_gray1  },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", ""};
static const char tagclients[] = "";
static const char tagempty[] = "";

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "OvoPlayer", NULL,       "MiniPlayer",       0,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      deck,    0 },
	{ "",      tile,    0 },
	{ "",      NULL,    0 },    /* no layout function means floating behavior */
	{ "",      monocle, 1 },
};

/* key definitions */
#define MODKEY Mod4Mask
#define AltMask Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} },

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *pstatustimecmd[]  = { "pstatus", "--type", "time", "--update", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_a,      gesture,        {0} },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_ampersand,              0 )
	TAGKEYS(                        XK_bracketleft,            1 )
	TAGKEYS(                        XK_braceleft,              2 )
	TAGKEYS(                        XK_braceright,             3 )
	TAGKEYS(                        XK_parenleft,              4 )
	TAGKEYS(                        XK_equal,                  5 )
	TAGKEYS(                        XK_slash,                  6 )
	TAGKEYS(                        XK_at,                     7 )
	{ MODKEY|ShiftMask,             XK_F12,      quit,         {0} },

	// some degree of compatibility with standard keybindings
	{ AltMask,                      XK_Tab,    focusstack,     {.i = +1 } },
	{ AltMask,                      XK_F4,     killclient,     {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[3]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        spawn,          {.v = pstatustimecmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

/* gestures
 * u means up
 * d means down
 * l means left
 * r means right
 * ud means up and down
 */
static const char *ovoplaypause[]  = { "ovoplayerctrl", "--playpause", NULL };
static const char *ovonext[]  = { "ovoplayerctrl", "--next", NULL };
static const char *ovoprev[]  = { "ovoplayerctrl", "--previous", NULL };
static Gesture gestures[] = {
	{ "u",  spawn, {.v = ovoplaypause} },
	{ "dl",  spawn, {.v = ovoprev} },
	{ "dr",  spawn, {.v = ovonext} },
};

