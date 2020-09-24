/*
 * gtkinfobar.h
 * This file is part of GTK+
 *
 * Copyright (C) 2005 - Paolo Maggi
 *
 * This lib is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This lib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this lib. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Modified by the gedit Team, 2005. See the gedit AUTHORS file for a
 * list of people on the gedit Team.
 * See the gedit ChangeLog files for a list of changes.
 *
 * Modified by the GTK+ Team, 2008-2009.
 */

#ifndef __GTK_INFO_BAR_H__
#define __GTK_INFO_BAR_H__

#if !defined (__GTK_H_INSIDE__) && !defined (GTK_COMPILATION)
#error "Only <gtk/gtk.h> can be included directly."
#endif

#include <gtk/gtkbox.h>
#include <gtk/gtkenums.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GTK_TYPE_INFO_BAR              (gtk_info_bar_get_type())
#define GTK_INFO_BAR(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_TYPE_INFO_BAR, GtkInfoBar))
#define GTK_INFO_BAR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), GTK_TYPE_INFO_BAR, GtkInfoBarClass))
#define GTK_IS_INFO_BAR(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_TYPE_INFO_BAR))
#define GTK_IS_INFO_BAR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), GTK_TYPE_INFO_BAR))
#define GTK_INFO_BAR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), GTK_TYPE_INFO_BAR, GtkInfoBarClass))


typedef struct _GtkInfoBarPrivate GtkInfoBarPrivate;
typedef struct _GtkInfoBarClass GtkInfoBarClass;
typedef struct _GtkInfoBar GtkInfoBar;


struct _GtkInfoBar
{
  GtkBox parent;

  /*< private > */
  GtkInfoBarPrivate *priv;
};


struct _GtkInfoBarClass
{
  GtkBoxClass parent_class;

  /* Signals */
  void (* response) (GtkInfoBar *info_bar, gint response_id);

  /* Keybinding signals */
  void (* close)    (GtkInfoBar *info_bar);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};

GDK_AVAILABLE_IN_ALL
GType          gtk_info_bar_get_type               (void) G_GNUC_CONST;
GDK_AVAILABLE_IN_ALL
GtkWidget     *gtk_info_bar_new                    (void);

GDK_AVAILABLE_IN_ALL
GtkWidget     *gtk_info_bar_new_with_buttons       (const gchar    *first_button_text,
                                                    ...);

GDK_AVAILABLE_IN_ALL
GtkWidget     *gtk_info_bar_get_action_area        (GtkInfoBar     *info_bar);
GDK_AVAILABLE_IN_ALL
GtkWidget     *gtk_info_bar_get_content_area       (GtkInfoBar     *info_bar);
GDK_AVAILABLE_IN_ALL
void           gtk_info_bar_add_action_widget      (GtkInfoBar     *info_bar,
                                                    GtkWidget      *child,
                                                    gint            response_id);
GDK_AVAILABLE_IN_ALL
GtkWidget     *gtk_info_bar_add_button             (GtkInfoBar     *info_bar,
                                                    const gchar    *button_text,
                                                    gint            response_id);
GDK_AVAILABLE_IN_ALL
void           gtk_info_bar_add_buttons            (GtkInfoBar     *info_bar,
                                                    const gchar    *first_button_text,
                                                    ...);
GDK_AVAILABLE_IN_ALL
void           gtk_info_bar_set_response_sensitive (GtkInfoBar     *info_bar,
                                                    gint            response_id,
                                                    gboolean        setting);
GDK_AVAILABLE_IN_ALL
void           gtk_info_bar_set_default_response   (GtkInfoBar     *info_bar,
                                                    gint            response_id);

/* Emit response signal */
GDK_AVAILABLE_IN_ALL
void           gtk_info_bar_response               (GtkInfoBar     *info_bar,
                                                    gint            response_id);

GDK_AVAILABLE_IN_ALL
void           gtk_info_bar_set_message_type       (GtkInfoBar     *info_bar,
                                                    GtkMessageType  message_type);
GDK_AVAILABLE_IN_ALL
GtkMessageType gtk_info_bar_get_message_type       (GtkInfoBar     *info_bar);

GDK_AVAILABLE_IN_3_10
void           gtk_info_bar_set_show_close_button  (GtkInfoBar     *info_bar,
                                                    gboolean        setting);
GDK_AVAILABLE_IN_3_10
gboolean       gtk_info_bar_get_show_close_button  (GtkInfoBar     *info_bar);

GDK_AVAILABLE_IN_3_22
void           gtk_info_bar_set_revealed           (GtkInfoBar     *info_bar,
                                                    gboolean        revealed);
GDK_AVAILABLE_IN_3_22
gboolean       gtk_info_bar_get_revealed           (GtkInfoBar     *info_bar);

G_END_DECLS

#endif  /* __GTK_INFO_BAR_H__  */