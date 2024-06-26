/*
 * Copyright © 2004 Noah Levitt
 * Copyright © 2007 Christian Persch
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335 USA
 */

#include <gtk/gtk.h>

#define I_(string) g_intern_static_string (string)

/* The last unicode character we support */
#define UNICHAR_MAX (0x0010FFFFUL)

G_GNUC_INTERNAL void _gucharmap_intl_ensure_initialized (void);

G_GNUC_INTERNAL gboolean _gucharmap_unicode_has_nameslist_entry (gunichar uc);

#define _GUCHARMAP_CHAPTERS_MODEL_COLUMN_LABEL_ATTRS (2)

struct _GucharmapChaptersModelPrivate {
  GucharmapCodepointList *book_list;
  int sort_column;
};

struct _GucharmapChartablePrivate {
  /* scrollable implementation */
  GtkAdjustment *vadjustment;
  gulong vadjustment_changed_handler_id;
#if GTK_CHECK_VERSION (2, 91, 2)
  /* GtkScrollable impl */
  GtkAdjustment *hadjustment; /* unused */
  guint hscroll_policy : 1; /* unused */
  guint vscroll_policy : 1;
#endif

  /* Font */
  PangoFontDescription *font_desc;

  /* Geometry */
  int minimal_column_width;      /* depends on font_desc and size allocation */
  int minimal_row_height;        /* depends on font_desc and size allocation */
  int n_padded_columns;          /* columns 0..n-1 will be 1px wider than minimal_column_width */
  int n_padded_rows;             /* rows 0..n-1 will be 1px taller than minimal_row_height */
  int rows;
  int cols;
  int page_size;       /* rows * cols */

  int page_first_cell; /* the cell index of the top left corner */
  int active_cell;     /* the active cell index */

  /* Drawing */
  PangoLayout *pango_layout;

  /* Zoom popup */
  GtkWidget *zoom_window;
  int zoom_image_width;
  int zoom_image_height;

  /* for dragging (#114534) */
  gdouble click_x, click_y; 

  GtkTargetList *target_list;

  GucharmapCodepointList *codepoint_list;
  int last_cell; /* from gucharmap_codepoint_list_get_last_index */
  gboolean codepoint_list_changed;

  /* Settings */
  guint snap_pow2_enabled : 1;
  guint zoom_mode_enabled : 1;
  guint font_fallback     : 1;
};

gint _gucharmap_chartable_cell_column	(GucharmapChartable *chartable,
					 guint cell);
gint _gucharmap_chartable_column_width	(GucharmapChartable *chartable,
					 gint col);
gint _gucharmap_chartable_x_offset	(GucharmapChartable *chartable,
					 gint col);
gint _gucharmap_chartable_row_height	(GucharmapChartable *chartable,
		 			 gint row);
gint _gucharmap_chartable_y_offset	(GucharmapChartable *chartable,
					 gint row);
void _gucharmap_chartable_redraw	(GucharmapChartable *chartable,
					 gboolean move_zoom);
