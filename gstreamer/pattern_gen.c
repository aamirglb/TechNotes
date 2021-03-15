/*
    Program to generate all test pattern using videotestsrc.
    For compiling:
    $ gcc pattern_gen.c -o pattern_gen `pkg-config --cflags --libs gstreamer-1.0`

    For generating all pattern using the following shell command
    $ for i in {0..24}; do ./pattern_gen $i; done
*/

#include <gst/gst.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    GstElement *pipeline, *source, *sink, *converter, *overlay;
    GstBus     *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;

    gint pattern = 0;
    char filename[50];
    char *pattern_names[] = {
        "smpte",
        "snow",
        "black",
        "white",
        "red",
        "green",
        "blue",
        "checkers-1",
        "checkers-2",
        "checkers-4",
        "checkers-8",
        "circular",
        "blink",
        "smpte75",
        "zone-plate",
        "gamut",
        "chroma-zone-plate",
        "solid-color",
        "ball",
        "smpte100",
        "bar",
        "pinwheel",
        "spokes",
        "gradient",
        "colors",
    };

    if(argc == 2 ) {
        pattern = atoi(argv[1]);
    }

    sprintf(filename, "%s.png", pattern_names[pattern]);

    gst_init(&argc, &argv);

    source = gst_element_factory_make("videotestsrc", "source");
    sink   = gst_element_factory_make("filesink", "sink");
    converter = gst_element_factory_make("pngenc", "converter");
    // sink = gst_element_factory_make("ximagesink", "sink");
    // converter = gst_element_factory_make("autovideoconvert", "converter");
    
    overlay = gst_element_factory_make("textoverlay", "overlay");

    /* create emepty pipeline */
    pipeline = gst_pipeline_new("test-pipeline");

    if(!pipeline || !source || !sink) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    /* Build the pipeline */
    gst_bin_add_many(GST_BIN(pipeline), source, overlay, converter, sink, NULL);

    if(gst_element_link_many(source, overlay, converter, sink, NULL) != TRUE) {
        g_printerr("Element could not be linked.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    /* Modify source's properties */
    // g_object_set(source, "pattern", 0, NULL);
    g_object_set(source, "pattern", pattern, NULL);
    g_object_set(sink, "location", filename, NULL);

    g_object_set(G_OBJECT(overlay), 
        "text", pattern_names[pattern],
        "font-desc", "Sans, 24",
        "shaded-background", TRUE,
        "valignment", 1,
        "halignment", 1,
        NULL);

    ret = gst_element_set_state(pipeline, GST_STATE_PLAYING);
    if(ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set pipeline to playing state.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    bus = gst_element_get_bus(pipeline);
    msg = gst_bus_timed_pop_filtered(bus, 100 * GST_MSECOND,
        GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

    if(msg != NULL) {
        GError *err;
        gchar *debug_info;

        switch(GST_MESSAGE_TYPE(msg)) {
            case GST_MESSAGE_ERROR:
                gst_message_parse_error(msg, &err, &debug_info);
                g_printerr("Error received from element %s: %s\n",
                    GST_OBJECT_NAME(msg->src), err->message);
                g_printerr("Debugging information: %s\n",
                    debug_info ? debug_info : "none");
                g_clear_error(&err);
                g_free(debug_info);
                break;

            case GST_MESSAGE_EOS:
                g_print("End-Of-Stream reached.\n");
                break;
            
            default:
                g_printerr("Unexpected message received.\n");
                break;
        }
        gst_message_unref(msg);
    } 

    /* Free resources */
    gst_object_unref(bus);
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(pipeline);
    g_print("Done Generating Pattern '%s'.\n", pattern_names[pattern]);
    return 0;
}