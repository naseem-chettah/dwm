/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;        /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;        /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const int showbar            = 0;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int splitstatus        = 1;        /* 1 for split status items */
static const char *splitdelim        = ";";       /* Character used for separating status */
static const char *fonts[]          = { "CaskaydiaCoveNerdFont:size=9:Bold" };
static const char col_gray1[]       = "#282828";
static const char col_gray2[]       = "#282828";
static const char col_gray3[]       = "#ebdbb2";
static const char col_gray4[]       = "#282828";
static const char col_gold[]        = "#a89984";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gold,  col_gold  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "sp-cmus", "-g", "98x26", "-e", "bash", "/home/seth/.config/suckless/cmus.sh", NULL };
const char *spcmd2[] = {"st", "-n", "sp-pulsemixer",   "-g", "98x20", "-e", "pulsemixer", NULL };
const char *spcmd3[] = {"st", "-n", "sp-term", "-g", "98x20", NULL };
const char *spcmd4[] = {"st", "-n", "sp-lf", "-g", "98x26", "-e", "lfpv", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"sp-cmus",       spcmd1},
	{"sp-pulsemixer", spcmd2},
	{"sp-term",       spcmd3},
	{"sp-lf",         spcmd4},
};

/* tagging */
static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八"};
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                      instance          title               tags mask    isfloating  isterminal  noswallow  monitor */
	{ "org.wezfurlong.wezterm",   NULL,             NULL,               0,           0,          1,           0,        -1 },
	{ "Brave-browser",            NULL,             NULL,               1 << 0,      0,          0,           0,        -1 },
	{ "tmux",                     NULL,             NULL,               1 << 1,      0,          0,           0,        -1 },
	{ "discord",                  NULL,             NULL,               1 << 5,      0,          0,           0,        -1 },
	{ "Thunar",                   NULL,             NULL,               1 << 6,      0,          0,           0,        -1 },
	{ "Syncthing GTK",            NULL,             NULL,               1 << 4,      0,          0,           0,        -1 },
	{ "tutanota-desktop",         NULL,             NULL,               1 << 4,      0,          0,           0,        -1 },
	{ "mpv",                      NULL,             NULL,               0,           1,          0,           0,        -1 },
	{ "Nsxiv",                    NULL,             NULL,               0,           1,          0,           0,        -1 },
	{ "Nitrogen",                 NULL,             NULL,               0,           1,          0,           0,        -1 },
	{ "Matplotlib",               NULL,             NULL,               0,           1,          0,           0,        -1 },
	{ "Lxappearance",             NULL,             NULL,               0,           1,          0,           0,        -1 },
	{ NULL,                       NULL,             "Event Tester",     0,           0,          0,           1,        -1 },
	{ NULL,		                    "sp-cmus",	      NULL,		            SPTAG(0),	   1,          0,           0,        -1 },
	{ NULL,		                    "sp-pulsemixer",  NULL,		            SPTAG(1),	   1,          0,           0,        -1 },
	{ NULL,		                    "sp-term",        NULL,		            SPTAG(2),	   1,          1,           0,        -1 },
	{ NULL,		                    "sp-lf",          NULL,		            SPTAG(3),	   1,          1,           0,        -1 },
};

/* layout(s) */
static const float mfact        = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster        = 1;    /* number of clients in master area */
static const int resizehints    = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1;    /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define ALTMOD Mod1Mask
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} }, \
  { ALTMOD,                       KEY,      focusnthmon,    {.i  = TAG } }, \
  { ALTMOD|ShiftMask,             KEY,      tagnthmon,      {.i  = TAG } },


/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_o,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_p,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      pushdown,       {0} },
	{ MODKEY|ShiftMask,             XK_k,      pushup,         {0} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY|Mod4Mask,              XK_i,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_g,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_g,      defaultgaps,    {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_s,      togglefullscr,  {0} },
	{ MODKEY,            			      XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			      XK_u,	     togglescratch,  {.ui = 1 } },
	{ MODKEY,            			      XK_t,	     togglescratch,  {.ui = 2 } },
	{ MODKEY,            			      XK_r,	     togglescratch,  {.ui = 3 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_7,                      4)
	TAGKEYS(                        XK_8,                      5)
	TAGKEYS(                        XK_9,                      6)
	TAGKEYS(                        XK_0,                      7)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
