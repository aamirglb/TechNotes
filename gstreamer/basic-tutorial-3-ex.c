#include <gst/gst.h>

/*
    For compilation use the command
    gcc filename.c -o outputfile `pkg-config --cflags --libs gstreamer-1.0`
*/
typedef struct _CustomData {
    GstElement *pipeline;
    GstElement *source;
    GstElement *convert;
    GstElement *videoconvert;
    GstElement *resample;
    GstElement *sink;
    GstElement *videosink;
} CustomData;

static void pad_added_handler(GstElement *src, GstPad *pad, CustomData *data);

int main(int argc, char *argv[]) {
    CustomData data;
    GstBus     *bus;
    GstMessage *msg;
    GstStateChangeReturn ret;
    gboolean terminate = FALSE;

    /* Initialize GStreamer */
    gst_init(&argc, &argv);

    // Create elements
    data.source = gst_element_factory_make("uridecodebin", "source");
    data.convert = gst_element_factory_make("audioconvert", "convert");
    data.resample = gst_element_factory_make("audioresample", "resample");
    data.sink = gst_element_factory_make("autoaudiosink", "sink");
    data.videoconvert = gst_element_factory_make("videoconvert", "videoconvert");
    data.videosink  = gst_element_factory_make("autovideosink", "videosink");

    // Create pipeline
    data.pipeline = gst_pipeline_new("test-pipeline");

    if(!data.pipeline || !data.source || !data.convert || !data.videoconvert ||
        !data.resample || !data.sink || !data.videosink ) {
        g_printerr("Not all elements could be created.\n");
        return -1;
    }

    gst_bin_add_many(GST_BIN(data.pipeline), 
                            data.source, 
                            data.convert,
                            data.videoconvert, 
                            data.resample, 
                            data.sink,
                            data.videosink, 
                            NULL);
    
    if(!gst_element_link_many(data.videoconvert, data.videosink, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    if(!gst_element_link_many(data.convert, data.resample, data.sink, NULL)) {
        g_printerr("Elements could not be linked.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    // Set URI
    // g_object_set(data.source, "uri", "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_trailer-480p.webm", NULL);

    if(argc == 1) {
        g_object_set(data.source, "uri", "http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/BigBuckBunny.mp4", NULL);        
    } else {
        g_print("URI set to: %s\n", argv[1]);
        g_object_set(data.source, "uri", argv[1], NULL);
    }
    
    g_signal_connect(data.source, "pad-added", G_CALLBACK(pad_added_handler), &data);

    // Start playing
    ret = gst_element_set_state(data.pipeline, GST_STATE_PLAYING);
    if(ret == GST_STATE_CHANGE_FAILURE) {
        g_printerr("Unable to set the pipeline to playing state.\n");
        gst_object_unref(data.pipeline);
        return -1;
    }

    bus = gst_element_get_bus(data.pipeline);
    do {
        msg = gst_bus_timed_pop_filtered(bus, GST_CLOCK_TIME_NONE,
        GST_MESSAGE_STATE_CHANGED | GST_MESSAGE_ERROR | GST_MESSAGE_EOS);

        // parse messages
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
                    terminate = TRUE;
                    break;

                case GST_MESSAGE_EOS:
                    g_print("End-Of-Stream reached.\n");
                    terminate = TRUE;
                    break;
                
                case GST_MESSAGE_STATE_CHANGED:
                    // check if message is from pipeline
                    if(GST_MESSAGE_SRC(msg) == GST_OBJECT(data.pipeline)) {
                        GstState old_state, new_state, pending_state;
                        gst_message_parse_state_changed(msg, 
                            &old_state, &new_state, &pending_state);
                        g_print("Pipeline state changed from %s to %s:\n", 
                            gst_element_state_get_name(old_state),
                            gst_element_state_get_name(new_state));
                    }
                    break;
                default:
                    g_printerr("Unexpected message received.\n");
                    break;
            }
            gst_message_unref(msg);
        }
    } while(!terminate);
    
    /* Free resources */
    gst_object_unref(bus);
    gst_element_set_state(data.pipeline, GST_STATE_NULL);
    gst_object_unref(data.pipeline);
    return 0;
}

static void pad_added_handler(GstElement *src, GstPad *new_pad, CustomData *data) {    
    GstPad *sink_pad;
    GstPadLinkReturn ret;
    GstCaps *new_pad_caps = NULL;
    GstStructure *new_pad_struct = NULL;
    const gchar *new_pad_type = NULL;

    g_print("Received new pad '%s' from '%s':\n", 
        GST_PAD_NAME(new_pad), GST_ELEMENT_NAME(src));

    new_pad_caps = gst_pad_get_current_caps(new_pad);
    new_pad_struct = gst_caps_get_structure(new_pad_caps, 0);
    new_pad_type = gst_structure_get_name(new_pad_struct);

    if(g_str_has_prefix(new_pad_type, "audio/x-raw")) {
        // get audio sink
        sink_pad = gst_element_get_static_pad(data->convert, "sink");
        if(gst_pad_is_linked(sink_pad)) {
            g_print("We are already linked. Ignoring.\n");
            goto exit;
        }

        ret = gst_pad_link(new_pad, sink_pad);
        if(GST_PAD_LINK_FAILED(ret)) {
            g_print ("Type is '%s' but link failed.\n", new_pad_type);
        } else {
            g_print ("Link succeeded (type '%s').\n", new_pad_type);
        }
    } else if(g_str_has_prefix(new_pad_type, "video/x-raw")) {
        // get video sink
        sink_pad = gst_element_get_static_pad(data->videoconvert, "sink");
        if(gst_pad_is_linked(sink_pad)) {
            g_print("We are already linked. Ignoring.\n");
            goto exit;
        }

        ret = gst_pad_link(new_pad, sink_pad);
        if(GST_PAD_LINK_FAILED(ret)) {
            g_print ("Type is '%s' but link failed.\n", new_pad_type);
        } else {
            g_print ("Link succeeded (type '%s').\n", new_pad_type);
        }
    }

    exit:
        /* Unreference the new pad's caps, if we got them */
        if (new_pad_caps != NULL)
            gst_caps_unref (new_pad_caps);

        /* Unreference the sink pad */
        gst_object_unref (sink_pad);
}