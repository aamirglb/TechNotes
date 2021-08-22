/*
gcc appsrc2.c -o appsrc2 `pkg-config --cflags --libs gstreamer-1.0`
*/
#include <gst/gst.h>

static GMainLoop *loop;

static void set_color(GstBuffer *buf, int offset, int color) {
    int r = (color & 0xFF0000) >> 16;
    int g = (color & 0x00FF00) >> 8;
    int b = (color & 0x0000FF);
    gst_buffer_memset(buf, offset, r, 1);
    gst_buffer_memset(buf, offset+1, g, 1);
    gst_buffer_memset(buf, offset+2, b, 1); 
}

static void
cb_need_data (GstElement *appsrc,
          guint       unused_size,
          gpointer    user_data)
{
  static gboolean white = FALSE;
  static gint color = 100;
  static GstClockTime timestamp = 0;
  GstBuffer *buffer;
  guint size;
  GstFlowReturn ret;

  int width = 640;
  int height = 480;
  size = width * height * 3;
  
  buffer = gst_buffer_new_allocate (NULL, size, NULL);

  /* this makes the image black/white */
  // gst_buffer_memset (buffer, 0, white ? 0xff : 0x0, size);
  // gst_buffer_memset (buffer, 0, color, size);
  // ++color;
  // g_print("color: %d ", color);
  // if(color > 255) color = 0;
  // white = !white;

  static int color_arr[] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0xFFFF00,
    0xFF00FF,
  };
  static int col_idx = 0;

  int gwidth = width/5;

  gst_buffer_memset (buffer, 0, 0xff, size);
  for(int blk=0; blk < width/gwidth; ++blk) {
    for(int i=0; i<height; ++i) {
      for(int j=(blk*gwidth); j<(blk*gwidth)+gwidth; ++j) {
        if(blk==0) {
          set_color(buffer, (i*width*3)+(j*3), color_arr[ col_idx % 5]);
        } else if(blk == 1) {
          set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+1) % 5]);
        } else if(blk == 2) {
          set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+2) % 5]);
        } else if(blk == 3) {
          set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+3) % 5]);
        } else if(blk == 4) {
          set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+4) % 5]);
        }
      }
    }
  }

  col_idx += 1;
  if(col_idx >= 5) col_idx = 0;
  int bsize = height/5;

  // for(int blk=0; blk < height/bsize; ++blk) {
  //   for(int i=(blk*bsize); i<(blk*bsize)+bsize; ++i) {
  //     for(int j=0; j<width; ++j) {
  //       if(blk==0) {
  //         set_color(buffer, (i*width*3)+(j*3), color_arr[ col_idx % 5]);
  //       } else if(blk == 1) {
  //         set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+1) % 5]);
  //       } else if(blk == 2) {
  //         set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+2) % 5]);
  //       } else if(blk == 3) {
  //         set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+3) % 5]);
  //       } else if(blk == 4) {
  //         set_color(buffer, (i*width*3)+(j*3), color_arr[ (col_idx+4) % 5]);
  //       }
  //     }
  //   }
  // }

  GST_BUFFER_PTS (buffer) = timestamp;
  GST_BUFFER_DURATION (buffer) = gst_util_uint64_scale_int (1, GST_SECOND, 2);

  timestamp += GST_BUFFER_DURATION (buffer);

  g_signal_emit_by_name (appsrc, "push-buffer", buffer, &ret);
  gst_buffer_unref (buffer);

  if (ret != GST_FLOW_OK) {
    /* something wrong, stop pushing */
    g_main_loop_quit (loop);
  }
}

gint
main (gint   argc,
      gchar *argv[])
{
  GstElement *pipeline, *appsrc, *conv, *videosink;

  /* init GStreamer */
  gst_init (&argc, &argv);
  loop = g_main_loop_new (NULL, FALSE);

  /* setup pipeline */
  pipeline = gst_pipeline_new ("pipeline");
  appsrc = gst_element_factory_make ("appsrc", "source");
  conv = gst_element_factory_make ("videoconvert", "conv");
  videosink = gst_element_factory_make ("xvimagesink", "videosink");

  /* setup */
  g_object_set (G_OBJECT (appsrc), "caps",
        gst_caps_new_simple ("video/x-raw",
                     "format", G_TYPE_STRING, "RGB",
                     "width", G_TYPE_INT, 640,
                     "height", G_TYPE_INT, 480,
                     "framerate", GST_TYPE_FRACTION, 0, 1,
                     NULL), NULL);
  gst_bin_add_many (GST_BIN (pipeline), appsrc, conv, videosink, NULL);
  gst_element_link_many (appsrc, conv, videosink, NULL);

  /* setup appsrc */
  g_object_set (G_OBJECT (appsrc),
        "stream-type", 0,
        "format", GST_FORMAT_TIME, NULL);
  g_signal_connect (appsrc, "need-data", G_CALLBACK (cb_need_data), NULL);

  /* play */
  gst_element_set_state (pipeline, GST_STATE_PLAYING);
  g_main_loop_run (loop);

  /* clean up */
  gst_element_set_state (pipeline, GST_STATE_NULL);
  gst_object_unref (GST_OBJECT (pipeline));
  g_main_loop_unref (loop);

  return 0;
  }