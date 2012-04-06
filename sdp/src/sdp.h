/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * sdp.h
 * Copyright (C) Kevin Welsh 2012 <kcwelsh@mtu.edu>
 * 
 * sdp is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * sdp is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SDP_
#define _SDP_

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define SDP_TYPE_APPLICATION             (sdp_get_type ())
#define SDP_APPLICATION(obj)             (G_TYPE_CHECK_INSTANCE_CAST ((obj), SDP_TYPE_APPLICATION, Sdp))
#define SDP_APPLICATION_CLASS(klass)     (G_TYPE_CHECK_CLASS_CAST ((klass), SDP_TYPE_APPLICATION, SdpClass))
#define SDP_IS_APPLICATION(obj)          (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SDP_TYPE_APPLICATION))
#define SDP_IS_APPLICATION_CLASS(klass)  (G_TYPE_CHECK_CLASS_TYPE ((klass), SDP_TYPE_APPLICATION))
#define SDP_APPLICATION_GET_CLASS(obj)   (G_TYPE_INSTANCE_GET_CLASS ((obj), SDP_TYPE_APPLICATION, SdpClass))

typedef struct _SdpClass SdpClass;
typedef struct _Sdp Sdp;

struct _SdpClass
{
	GtkApplicationClass parent_class;
};

struct _Sdp
{
	GtkApplication parent_instance;
};

GType sdp_get_type (void) G_GNUC_CONST;
Sdp *sdp_new (void);

/* Callbacks */

G_END_DECLS

#endif /* _APPLICATION_H_ */
