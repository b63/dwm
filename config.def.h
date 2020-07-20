/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx     = 5;        /* border pixel of windows */
static const unsigned int snap         = 16;       /* snap pixel */
static const unsigned int gappih       = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv       = 5;       /* vert inner gap between windows */
static const unsigned int gappoh       = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov       = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps             = 1;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating       = 0;        /* 1 means swallow floating windows by default */
static const int showbar               = 1;        /* 0 means no bar */
static const int topbar                = 1;        /* 0 means bottom bar */
static const int horizpadbar           = 5;        /* horizontal padding for statusbar */
static const int vertpadbar            = 8;        /* vertical padding for statusbar */
static const int statusblockpad        = 0;        /* padding between blocks in statusbar (note: total padding)*/
static const char *fonts[]             = {"mononoki Nerd Font:size=10", "OpenMojiBlack Nerd Font:size=13"};
static const char dmenufont[]          = "mononoki Nerd Font:size=10";
static const char bgcol[]              = "#2e3440";
static const char bordercol[]          = "#4c566a";
static const char fgcol[]              = "#e5e9f0";
static const char selfgcol[]           = "#eceff4";
static const char selbordercol[]       = "#bf616a";
static const char selbgcol[]           = "#4c566a";
static const char *colors[][3]         = {
	/*                 fg         bg         border   */
	[SchemeNorm]   = { fgcol,     bgcol,      bordercol    },
	[SchemeSel]    = { selfgcol,  selbgcol,   selbordercol },
};

static const unsigned int baralpha        = 0xffU;
static const unsigned int borderalpha     = OPAQUE;
/* each color scheme in colors is associated with a set of alphas*/
/* if lenghts mismatch, color scheme will be associated with last set of alphas */
/* see dwm.c:setup(void) */
static const unsigned int alphas[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = { OPAQUE,    baralpha,  OPAQUE },
	[SchemeSel]  = { OPAQUE,    baralpha,  OPAQUE },
};


typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-T", "spterm", "-c", "spterm", "-g", "100x30", "-e", "tmux", "-f", ".config/tmux/tmux.conf", NULL };
const char *spcmd2[] = {"st", "-c", "spfm",  "-e", "lf", NULL };
const char *spcmd3[] = {"keeweb.sh", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"keeweb",   spcmd3},
};


/* tagging */
static const char *tags[]           = { "q", "w", "e", "r", "t", "y", "u", "", "" };
/* default layout for each tag, value is index into layouts array */
static const size_t defaulttaglts[] = {  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  0 ,  2  };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance         title          tags mask     isterminal isfloating    noswallow      monitor */
	{ "Gimp",	NULL,		NULL,		0,		0,	1,		 0,	 -1 },
	{ "firefox",	"Navigator",	NULL,		1 << 8,		0,	0,		-1,	 -1 },
	{ "Alacritty",	NULL,		NULL,		0,		1,	0,		-1,	 -1 },
	{ "st",		NULL,		NULL,		0,		1,	0,		-1,	 -1 },
	{ "spterm",	"st-256color",	NULL,		SPTAG(0),	0,	1,		-1,	 -1 },
	{ "spfm",	"st-256color",	NULL,		SPTAG(1),	0,	1,		-1,	 -1 },
	{ NULL,		"keeweb",	NULL,		SPTAG(2),	0,	1,		-1,	 -1 },
	{ NULL,		NULL,		"Event Tester",	0,		0,	1,		 1,	 -1 },/* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ Mod1Mask,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ Mod1Mask|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ Mod1Mask|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bgcol, "-nf", fgcol, "-sb", selbgcol, "-sf", selfgcol, NULL };
static const char *termcmd[]  = { "st", "-e", "tmux", "-f", ".config/tmux/tmux.conf", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_f,      spawn,          SHCMD("'lf'")   },
	{ MODKEY,                       XK_e,      spawn,          SHCMD("")},


	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_semicolon,focusmaster,  { .i=0 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },

	{ MODKEY|Mod1Mask,              XK_h,      incrgaps,       {.i = +5 } },
	{ MODKEY|Mod1Mask,              XK_l,      incrgaps,       {.i = -5 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +5 } },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -5 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_h,      incrigaps,      {.i = +5 } },
	{ MODKEY|Mod1Mask|ControlMask,  XK_l,      incrigaps,      {.i = -5 } },
	{ MODKEY|Mod1Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod1Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },

	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },

	{ MODKEY,                       XK_c,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_v,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[5]} },

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_y,      togglescratch,  {.ui = 0 } },
	{ MODKEY,                       XK_u,      togglescratch,  {.ui = 1 } },
	{ MODKEY,                       XK_x,      togglescratch,  {.ui = 2 } },

	TAGKEYS(                        XK_q,                      0)
	TAGKEYS(                        XK_w,                      1)
	TAGKEYS(                        XK_e,                      2)
	TAGKEYS(                        XK_r,                      3)
	TAGKEYS(                        XK_t,                      4)
	TAGKEYS(                        XK_y,                      5)
	TAGKEYS(                        XK_u,                      6)
	TAGKEYS(                        XK_i,                      7)
	TAGKEYS(                        XK_o,                      8)

	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {1} },

	{ Mod1Mask,                     XK_Escape, focusstack,     {.i = +1 } },
	{ Mod1Mask|ShiftMask,           XK_Escape, focusstack,     {.i = -1 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask           button          function        argument */
	{ ClkLtSymbol,          0,                   Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,                   Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,                   Button2,        zoom,           {0} },
	{ ClkStatusText,        0,                   Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,              Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,              Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,    Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,                   Button1,        view,           {0} },
	{ ClkTagBar,            0,                   Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,              Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,              Button3,        toggletag,      {0} },
};

