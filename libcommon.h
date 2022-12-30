/* libcommon.h generated by valac 0.18.1, the Vala compiler, do not modify */


#ifndef __LIBCOMMON_H__
#define __LIBCOMMON_H__

#include <glib.h>
#include <stdlib.h>
#include <string.h>
#include <gio/gio.h>

G_BEGIN_DECLS


#define WIXL_TYPE_UNIX_INPUT_STREAM (wixl_unix_input_stream_get_type ())
#define WIXL_UNIX_INPUT_STREAM(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), WIXL_TYPE_UNIX_INPUT_STREAM, WixlUnixInputStream))
#define WIXL_UNIX_INPUT_STREAM_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), WIXL_TYPE_UNIX_INPUT_STREAM, WixlUnixInputStreamClass))
#define WIXL_IS_UNIX_INPUT_STREAM(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), WIXL_TYPE_UNIX_INPUT_STREAM))
#define WIXL_IS_UNIX_INPUT_STREAM_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), WIXL_TYPE_UNIX_INPUT_STREAM))
#define WIXL_UNIX_INPUT_STREAM_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), WIXL_TYPE_UNIX_INPUT_STREAM, WixlUnixInputStreamClass))

typedef struct _WixlUnixInputStream WixlUnixInputStream;
typedef struct _WixlUnixInputStreamClass WixlUnixInputStreamClass;
typedef struct _WixlUnixInputStreamPrivate WixlUnixInputStreamPrivate;

typedef enum  {
	WIXL_ERROR_FAILED,
	WIXL_ERROR_FIXME
} WixlError;
#define WIXL_ERROR wixl_error_quark ()
struct _WixlUnixInputStream {
	GInputStream parent_instance;
	WixlUnixInputStreamPrivate * priv;
};

struct _WixlUnixInputStreamClass {
	GInputStreamClass parent_class;
};


GQuark wixl_error_quark (void);
gchar* wixl_uuid_generate (void);
gpointer wixl_enum_from_string (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, const gchar* str, GError** error);
void wixl_hash_table_add (GType g_type, GBoxedCopyFunc g_dup_func, GDestroyNotify g_destroy_func, GHashTable* h, gconstpointer o);
gchar* wixl_add_braces (const gchar* str);
gchar* wixl_get_uuid (gchar* uuid, GError** error);
glong wixl_now (void);
guint64 wixl_time_to_filetime (glong t);
gchar* wixl_indent (const gchar* space, const gchar* text);
gchar* wixl_uuid_from_name (const gchar* s);
gchar* wixl_generate_id (const gchar* prefix, guint n, ...);
gchar* wixl_random_id (const gchar* prefix);
gchar* wixl_yesno (gboolean yes);
gboolean wixl_parse_yesno (const gchar* str, gboolean _default_);
gchar* wixl_unquote (const gchar* str);
gchar* wixl_remove_prefix (const gchar* prefix, const gchar* str);
gint wixl_find_closing_paren (const gchar* str);
void wixl_compute_md5 (GFile* file, gint* hash1, gint* hash2, gint* hash3, gint* hash4, GError** error);
GType wixl_unix_input_stream_get_type (void) G_GNUC_CONST;
WixlUnixInputStream* wixl_unix_input_stream_new (gint fd_);
WixlUnixInputStream* wixl_unix_input_stream_construct (GType object_type, gint fd_);
gint wixl_unix_input_stream_get_fd (WixlUnixInputStream* self);
void wixl_unix_input_stream_set_fd (WixlUnixInputStream* self, gint value);


G_END_DECLS

#endif