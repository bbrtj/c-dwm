/* See LICENSE file for copyright and license details. */


/* appearance */
static const unsigned int borderpx = 1;        /* border pixel of windows */
static const unsigned int gappx = 6;        /* gaps between windows */
static const unsigned int snap = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray = 1;        /* 0 means no systray */
static const int showbar = 1;            /* 0 means no bar */
static const int topbar = 1;             /* 0 means bottom bar */
static const int iconsize = 14;          /* icon size */
static const int iconspacing = 8;        /* space between icon and title */
static const char *fonts[] = { "DejaVu Sans:size=10", "Icons:size=14" };

// Gruvbox
static const char col_activebackground[] = "#282828";
static const char col_activeborder[] = "#1d2021";
static const char col_inactivebackground[] = "#1d2021";
static const char col_inactiveborder[] = "#98971a";
static const char col_activetext[] = "#ebdbb2";
static const char col_inactivetext[] = "#7c6f64";
static const char col_selectedtag[] = "#458588";
static const char col_success[] = "#b8bb26";
static const char col_alert[] = "#d79921";
static const char col_urgent[] = "#fb4934";

// fg, bg, border
static const char *colors[][3] = {
	[SchemeNorm] = { col_activetext, col_inactivebackground, col_inactiveborder }, // unselected window, title bar
	[SchemeSel] = { col_activetext, col_activebackground, col_activeborder }, // currently selected window
	[SchemeTitle] = { col_activetext, col_inactivebackground, col_inactiveborder }, // title bar
	[SchemeTitleDim] = { col_inactivetext, col_inactivebackground, col_inactiveborder }, // non-active tags on the tagbar
	[SchemeTitleSel] = { col_selectedtag, col_inactivebackground, col_inactiveborder }, // non-active tags on the tagbar
	[SchemeTitleSuccess] = { col_success, col_inactivebackground, col_inactiveborder }, // custom color for status bar
	[SchemeTitleAlert] = { col_alert, col_inactivebackground, col_inactiveborder }, // custom color for status bar
	[SchemeTitleUrgent] = { col_urgent, col_inactivebackground, col_inactiveborder }, // custom color for status bar
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "" };
static const char tagclients[] = "";
static const char tagempty[] = "";

// xprop(1):
// WM_CLASS(STRING) = instance, class
// WM_NAME(STRING) = title
static const Rule rules[] = {
	/* class                 instance       title              tags mask   floating   monitor */
	{ "OvoPlayer",           "ovoplayer",   NULL,              1 << 7,     0,         -1 },
	{ "OvoPlayer",           NULL,          "MiniPlayer",      0,          1,         -1 },
	{ "feh",                 NULL,          NULL,              0,          1,         -1 },
	{ NULL,                  "Alert",       NULL,              0,          1,         -1 },

	// rules for organizing programs on tags on start / restore (optional)
	{ "firefox",             "Navigator",   NULL,              1 << 0,     0,         -1 },
	{ "thunderbird-default", "Mail",        NULL,              1 << 2,     0,         -1 },
};

/* layout(s) */
static const float mfact = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1; /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol   fn       hides topbar */
	{ "",      deck,    0 },
	{ "",      tile,    0 },
	{ "",      NULL,    0 }, /* no layout function means floating behavior */
	{ "",      monocle, 0 },
	{ "",      picture, 1 },
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
static const char *termcmd[] = { "st", NULL };
static const char *pstatustimecmd[] = { "pcrctl", "query", "Status", "build_time_line", "1", NULL };

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
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_a,      gesture,        {.i = 0} },
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
static const char *ovoplaypause[] = { "ovoplayerctrl", "--playpause", NULL };
static const char *ovonext[] = { "ovoplayerctrl", "--next", NULL };
static const char *ovoprev[] = { "ovoplayerctrl", "--previous", NULL };
static Gesture gestures[] = {
	{ "u",  spawn, {.v = ovoplaypause} },
	{ "dl",  spawn, {.v = ovoprev} },
	{ "dr",  spawn, {.v = ovonext} },
};

