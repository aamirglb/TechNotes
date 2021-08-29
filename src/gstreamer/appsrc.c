/*
gcc appsrc2.c -o appsrc2 `pkg-config --cflags --libs gstreamer-1.0`
*/
#include <gst/gst.h>
#include <math.h>

static GMainLoop *loop;

static int color_arr[] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0xFFFF00,
    0xFF00FF,
    0x00FFFF,
    0x7F00FF,
    0x800000,
    0x808080,
  };
static int len = sizeof(color_arr)/sizeof(color_arr[0]);
static guint col_idx = 0;
static guint flow_cnt = 0;
static const int max_cells = 5;
static guint time_count = 0;

static void set_color(GstBuffer *buf, int offset, int color) {
    int r = (color & 0xFF0000) >> 16;
    int g = (color & 0x00FF00) >> 8;
    int b = (color & 0x0000FF);
    gst_buffer_memset(buf, offset, r, 1);
    gst_buffer_memset(buf, offset+1, g, 1);
    gst_buffer_memset(buf, offset+2, b, 1); 
}

static void draw_circle(GstBuffer *buf, gint mid_x, gint mid_y, guint w) {
  // guint mid_x = w * 0.5;
  // guint mid_y = h * 0.5;

  set_color(buf, (mid_y*w*3)+(mid_x*3), 0x0);   

  // Use the below formula to draw circle
  // x = cx + r * cos(a)
  // y = cy + r * sin(a)

  guint r = 20;
  for(int r=20; r > 0; --r) {
  for(int a = 0; a < 360; ++a) {
    guint x = mid_x + r * cos((a * M_PI)/180.);
    guint y = mid_y + r * sin((a * M_PI)/180.);
    set_color(buf, (y*w*3)+(x*3), 0x0);
  }
  }
}

static void random_grid(GstBuffer *buffer, gint w, gint h) {
  int gwidth = w/max_cells;
  int hwidth = h/max_cells;
  gint size = w * h;

  for(int blk=0; blk < w/gwidth; ++blk) {
    for(int k=0; k < h/hwidth; k++) {
      for(int i=(k*hwidth); i< (k*hwidth)+hwidth; ++i) {
        for(int j=(blk*gwidth); j<(blk*gwidth)+gwidth; ++j) {
          set_color(buffer, (i*w*3)+(j*3), color_arr[ (blk+col_idx) % len]);
        }
      }
      col_idx++;
    }
  }
}

static void grid_flow(GstBuffer *buffer, gint w, gint h) {
  guint cell_cnt = 0;
  int gwidth = w/max_cells;
  int hwidth = h/max_cells;
  gint size = w * h;
  gint idx = 	0;

  if(flow_cnt >= (max_cells * max_cells)) {
    gst_buffer_memset (buffer, 0, 0xFF, size);
    flow_cnt = 0;
    return;
  }

  for(int blk=0; blk < w/gwidth; ++blk) {
    for(int k=0; k < h/hwidth; k++) {
      for(int i=(k*hwidth); i < (k*hwidth)+hwidth; ++i) {
        for(int j=(blk*gwidth); j<(blk*gwidth)+gwidth; ++j) {
          set_color(buffer, (i*w*3)+(j*3), color_arr[idx % len]);
        }
      }
      idx++;
      ++cell_cnt;
      if(cell_cnt > flow_cnt) return;
    }
  }
}

static void snow(GstBuffer *buffer, gint w, gint h, gint pix_size) {
  int gwidth = pix_size;
  int hwidth = pix_size;
  gint size = w * h;
  guint color;

  for(int blk=0; blk < w/gwidth; ++blk) {
    for(int k=0; k < h/hwidth; k++) {
      for(int i=(k*hwidth); i< (k*hwidth)+hwidth; ++i) {
        for(int j=(blk*gwidth); j<(blk*gwidth)+gwidth; ++j) {
          set_color(buffer, (i*w*3)+(j*3), color);
        }
      }
      color = 	g_random_int_range(0x0, 0xFFFFFF);
    }
  }  
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
  gst_buffer_memset (buffer, 0, 0xFF, size);

  static guint ox = 10;
  static guint oy = 220;
  draw_circle(buffer, ox, oy, width);
  ox+= 5;

  // ++time_count;
  // static guint pix_size = 1;
  // if((time_count % 10) == 0 && pix_size != 256) {
  //   pix_size *= 2;
  // }
  
  // if(pix_size < 256) 
  //   snow(buffer, width, height, pix_size);
  
  // if(time_count > 80 && time_count < 90) {
  //   random_grid(buffer, width, height);
  // } else if(time_count > 90 && time_count < (90+26)) {
  //   grid_flow(buffer, width, height); ++flow_cnt;
  // }

  // if(time_count > (90+26)) {
  //   time_count = 0;
  //   pix_size = 1;
  // }

  /* this makes the image black/white */
  // gst_buffer_memset (buffer, 0, white ? 0xff : 0x0, size);
  // gst_buffer_memset (buffer, 0, color, size);
  // ++color;
  // g_print("color: %d ", color);
  // if(color > 255) color = 0;
  // white = !white;


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