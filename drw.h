/* See LICENSE file for copyright and license details. */

typedef struct {
	Cursor cursor;
} Cur;

typedef struct Fnt {
	Display *dpy;
	unsigned int h;
	XftFont *xfont;
	FcPattern *pattern;
	struct Fnt *next;
} Fnt;

enum { ColFg, ColBg, ColBorder }; /* Clr scheme index */
typedef XftColor Clr;

typedef struct {
	unsigned int w, h;
	Display *dpy;
	int screen;
	Visual *visual;
	unsigned int depth;
	Colormap cmap;
	Window root;
	Drawable drawable;
	GC gc;
	Clr *scheme;
	Fnt *fonts;
	Fnt *extra_fonts;
} Drw;

typedef struct {
    /* 8*3 = 24 */
    char names[24];
    Clr clrs[3];
} StatusColor;

/* Drawable abstraction */
Drw *drw_create(Display *, int, Window, unsigned int, unsigned int, Visual*, unsigned int, Colormap);
void drw_resize(Drw *drw, unsigned int w, unsigned int h);
void drw_free(Drw *drw);

/* Fnt abstraction */
Fnt *drw_fontset_create(Drw* drw, const char *fonts[], size_t fontcount);
void drw_fontset_free(Fnt* set);
unsigned int drw_fontset_getwidth(Drw *drw, const char *text);
void drw_font_getexts(Fnt *font, const char *text, unsigned int len, unsigned int *w, unsigned int *h);

/* Colorscheme abstraction */
void drw_clr_create(Drw *drw, Clr *dest, const char *clrname, unsigned int alpha);
Clr *drw_scm_create(Drw *drw, const char *clrnames[], const unsigned int alphas[], size_t clrcount);

/* Cursor abstraction */
Cur *drw_cur_create(Drw *drw, int shape);
void drw_cur_free(Drw *drw, Cur *cursor);

/* Drawing context manipulation */
void drw_setfontset(Drw *drw, Fnt *set);
void drw_setscheme(Drw *drw, Clr *scm);

/* Drawing functions */
void drw_rect(Drw *drw, int x, int y, unsigned int w, unsigned int h, int filled, int invert);
int drw_text(Drw *drw, int x, int y, unsigned int w, unsigned int h, unsigned int lpad, const char *text, int invert);

/* Map functions */
void drw_map(Drw *drw, Window win, int x, int y, unsigned int w, unsigned int h);

/* status color functions */
int is_color_char(char c);
size_t drw_set_colorcode(Drw *drw, StatusColor *sc, const char **def_colors, const char *text, const unsigned int *alphas);
size_t drw_filter_colorcodes(Drw *drw, StatusColor *sc_arr, char *dst, const char *text, const char **def_colors, const unsigned int *alphas, size_t *offsets, size_t max_colors);
void drw_colored_text(Drw *drw, char *text, StatusColor *sc_arr, const size_t *offsets, size_t numcolors, int x, int y, unsigned int w, unsigned int h, unsigned int pad);
