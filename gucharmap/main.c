/*
 * Copyright © 2004 Noah Levitt
 * Copyright © 2007, 2008 Christian Persch
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

#include <config.h>

#include <stdlib.h>

#include <glib/gi18n.h>
#include <gtk/gtk.h>

#include <gucharmap/gucharmap.h>
#include "gucharmap-settings.h"
#include "gucharmap-window.h"

/* BEGIN HACK
 *
 * Gucharmap is a *character map*, not an emoji picker.
 * Consequently, we want to show character glyphs in black
 * and white, not colour emojis.
 *
 * However, there currently is no way in the pango API to
 * suppress use of colour fonts.
 * Internally, cairo *always* (!) calls FT_Load_Glyph with
 * the FT_LOAD_COLOR flag. Interpose the function and strip
 * that flag.
 *
 * This still doesn't get the desired display since the
 * emoji colour fonts (Noto Color Emoji) that's hardcoded
 * (see bug 787365) has greyscale fallback; I see no way
 * to skip the font altogether.
 */

#include <dlfcn.h>
#include <ft2build.h>
#include FT_FREETYPE_H

_GUCHARMAP_PUBLIC
FT_Error
FT_Load_Glyph(FT_Face face,
	      FT_UInt glyph_index,
	      FT_Int32 load_flags);

_GUCHARMAP_PUBLIC
FT_Error
FT_Load_Char(FT_Face face,
	     FT_ULong char_code,
	     FT_Int32 load_flags);

_GUCHARMAP_PUBLIC
FT_Error
FT_Load_Glyph(FT_Face face,
	      FT_UInt glyph_index,
	      FT_Int32 load_flags)
{
  static FT_Error (*original)(FT_Face face,
			      FT_UInt glyph_index,
			      FT_Int32 load_flags) = NULL;
  if (!original)
    original = dlsym(RTLD_NEXT, "FT_Load_Glyph");

  return original(face, glyph_index, load_flags & ~FT_LOAD_COLOR);
}

_GUCHARMAP_PUBLIC
FT_Error
FT_Load_Char( FT_Face face,
	      FT_ULong char_code,
	      FT_Int32 load_flags)
{
  static FT_Error (*original)(FT_Face face,
			      FT_ULong char_code,
			      FT_Int32 load_flags) = NULL;
  if (!original)
    original = dlsym(RTLD_NEXT, "FT_Load_Char");

  return original(face, char_code, load_flags & ~FT_LOAD_COLOR);
}

/* END HACK */

static gboolean
option_version_cb (const gchar *option_name,
                   const gchar *value,
                   gpointer     data,
                   GError     **error)
{
  g_print ("%s %s\n", _("GNOME Character Map"), VERSION);

  exit (EXIT_SUCCESS);
  return FALSE;
}

static gboolean
option_print_cb (const gchar *option_name,
                 const gchar *value,
                 gpointer     data,
                 GError     **error)
{
  const char *p;

  for (p = value; *p; p = g_utf8_next_char (p)) {
    gunichar c;
    char utf[7];

    c = g_utf8_get_char (p);
    if (c == (gunichar)-1)
      continue;

    utf[g_unichar_to_utf8 (c, utf)] = '\0';

    g_print("%s\tU+%04X\t%s\n",
            utf, c,
            gucharmap_get_unicode_name (c));
  }

  exit (EXIT_SUCCESS);
  return FALSE;
}

int
main (int argc, char **argv)
{
  GtkWidget *window;
  GdkScreen *screen;
  int monitor;
  GdkRectangle rect;
  GError *error = NULL;
  char *font = NULL;
  char **remaining = NULL;
  GOptionEntry goptions[] =
  {
    { "font", 0, 0, G_OPTION_ARG_STRING, &font,
      N_("Font to start with; ex: 'Serif 27'"), N_("FONT") },
    { "version", 0, G_OPTION_FLAG_HIDDEN | G_OPTION_FLAG_NO_ARG, 
      G_OPTION_ARG_CALLBACK, option_version_cb, NULL, NULL },
    { "print", 'p', 0, G_OPTION_ARG_CALLBACK, option_print_cb,
      "Print characters in string", "STRING" },
    { G_OPTION_REMAINING, 0, 0, G_OPTION_ARG_STRING_ARRAY, &remaining,
      NULL, N_("[STRING…]") },
    { NULL }
  };

  bindtextdomain (GETTEXT_PACKAGE, LOCALEDIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);

#ifdef HAVE_GCONF
  /* GConf uses ORBit2 which need GThread. See bug #565516 */
  g_thread_init (NULL);
#endif

  /* Not interested in silly debug spew polluting the journal, bug #749195 */
  if (g_getenv ("G_ENABLE_DIAGNOSTIC") == NULL)
    g_setenv ("G_ENABLE_DIAGNOSTIC", "0", TRUE);

  /* Set programme name explicitly (see bug #653115) */
  g_set_prgname("gucharmap");

  if (!gtk_init_with_args (&argc, &argv, NULL, goptions, GETTEXT_PACKAGE, &error))
    {
      g_printerr ("%s\n", error->message);
      g_error_free (error);

      exit (1);
    }

  gucharmap_settings_initialize ();

  g_set_application_name (_("Character Map"));
  gtk_window_set_default_icon_name (GUCHARMAP_ICON_NAME);

  window = gucharmap_window_new ();
  g_signal_connect (window, "destroy",
                    G_CALLBACK (gtk_main_quit), NULL);

  screen = gtk_window_get_screen (GTK_WINDOW (window));
  monitor = gdk_screen_get_monitor_at_point (screen, 0, 0);
  gdk_screen_get_monitor_geometry (screen, monitor, &rect);
  gtk_window_set_default_size (GTK_WINDOW (window), rect.width * 9/16, rect.height * 9/16);

  /* No --font argument, use the stored font (if any) */
  if (!font)
    font = gucharmap_settings_get_font ();

  if (font)
    {
      gucharmap_window_set_font (GUCHARMAP_WINDOW (window), font);
      g_free (font);
    }

  gucharmap_settings_add_window (GTK_WINDOW (window));

  gtk_window_present (GTK_WINDOW (window));

  if (remaining) {
    char *str = g_strjoinv (" ", remaining);
    gucharmap_window_search (GUCHARMAP_WINDOW (window), str);
    g_free (str);
    g_strfreev (remaining);
  }

  gtk_main ();

  gucharmap_settings_shutdown ();

  return 0;
}
