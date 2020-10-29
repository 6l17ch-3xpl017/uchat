//#include "client.h"
//

//
//static long long read_socket()
//{
//    char buf[20000];
//    read(user_data.server_attributes.socket, buf, 20000);
//
//    json_error_t error;
//    json_t *response = json_loads(buf, 0, &error);
//
//    json_t *status_j = json_object_get(response, "status");
//
//    long long status = json_integer_value(status_j);
//
//    if (status == 107)
//    {
//        return status;
//    }
//    else
//    {
//        //ToDo: Rise error in window
//        cmc_log_error("error: %i", status);
//        return status;
//    }
//}
//
//static long long send_json(json_t *json, int socket)
//{
//    char *result = json_dumps(json, 0);
//    write(socket, result, strlen(result));
//    cmc_log_info("%s", result);
//    json_decref(json);
//    return read_socket();
//}
//
//static int create_user_data()
//{
//    json_t *json = json_object();
//
//    json_t *user = json_object();
//    json_object_set_new(user, "nickname", json_string(user_data.user_attributes.username));
//    json_object_set_new(user, "password", json_string(user_data.user_attributes.password));
//
//    if (strcmp(user_data.type, REGISTER) == 0)
//    {
//        json_object_set_new(user, "email", json_string(user_data.user_attributes.email));
//        json_object_set_new(user, "age", json_string(user_data.user_attributes.age));
//        json_object_set_new(user, "fullname", json_string(user_data.user_attributes.fullname));
//        json_object_set_new(user, "ph_number", json_string(user_data.user_attributes.ph_number));
//        json_object_set_new(user, "user_photo", json_string(user_data.user_attributes.user_photo));
//        json_object_set_new(user, "options", json_string(user_data.user_attributes.options));
//    }
//
//    json_object_set_new(json, "type", json_string(user_data.type));
//    json_object_set_new(json, "user", user);
//
//    return send_json(json, user_data.server_attributes.socket);
//}
//
//static void init_connection(void)
//{
//    cmc_log_info("[Trying connect to server]");
//    int sockfd;
//    struct sockaddr_in servaddr;
//
//    cmc_log_info("[Trying to create a socket]");
//
//    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
//        cmc_log_error("[%s]", strerror(errno));
//    else
//        cmc_log_info("[Socket successfully created]");
//
//    memset(&servaddr, 0, sizeof(servaddr));
//
//    //ToDo: add auto ip and port assign and log output
//    servaddr.sin_family = AF_INET;
//    servaddr.sin_port = htons(5000);
//
//    cmc_log_info("[Trying connect server socket to client socket]");
//
//    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)
//        cmc_log_fatal("[%s]", strerror(errno));
//
//    else
//        cmc_log_info("[Connected to server]");
//
//    //ToDo: Print connection information
//
//    user_data.server_attributes.socket = sockfd;
//}
//
///** login_window **/
//void on_reg_button_activate_link(GtkWidget *window, GtkWidget *windoww)
//{
//    cmc_log_info("SIGN_UP BUTTON CLICKED");
////
////    t_page *page = select_page(REG_PAGE);
////
////    //ToDo: rename variable
////    gpointer *gp = get_widget(page->widgets, "reg_window");
//    gtk_widget_show_now(windoww);
//}
//
//// ToDo: Rework this function
//void on_login_button_clicked(GtkWidget *button, GtkWindow *reg_window)
//{
//    cmc_log_info("LOGIN BUTTON CLICKED");
//
//    user_data.type = LOGIN;
//
////    GList *main_list = gtk_container_get_children(main_box);
////
////    GtkContainer *username_box = g_list_get_widget(main_list, "login_username_box");
////    GtkContainer *password_box = g_list_get_widget(main_list, "password_box");
////
////    GList *username_list = gtk_container_get_children(username_box);
////    GList *password_list = gtk_container_get_children(password_box);
////
////    GtkEntry *username_entry = g_list_get_widget(username_list, "username_entry");
////    GtkEntry *password_entry = g_list_get_widget(password_list, "password_entry");
////
////    strcpy(user_data.user_attributes.username, gtk_entry_get_text(username_entry));
////    strcpy(user_data.user_attributes.password , gtk_entry_get_text(password_entry));
//
//    cmc_log_info("username_entry = %s | password_entry = %s",
//                 user_data.user_attributes.username,
//                 user_data.user_attributes.password);
//
//    if ((errno = create_user_data()) == 104)
//    {
//        gtk_widget_show_now(GTK_WIDGET(reg_window));
//        GtkWidget *toplevel = gtk_widget_get_toplevel(button);
//        cmc_log_info("TEST");
//    }
//    else
//    {
//        //ToDo: Raise error in window
//        cmc_log_error("error: %d", errno);
//    }
//
//}
//
//void on_remember_check_box_toggled()
//{
//    cmc_log_info("REMEMBER CHECKBOX TOGGLED");
//}
//
//void on_password_entry_changed(GtkEntry *entry)
//{
//    cmc_log_info("PASSWORD ENTRY CHANGED");
//    strcpy(user_data.user_attributes.password, gtk_entry_get_text(entry));
//}
//
//void on_username_entry_changed(GtkEntry *entry)
//{
//    cmc_log_info("USERNAME ENTRY CHANGED");
//    strcpy(user_data.user_attributes.username, gtk_entry_get_text(entry));
//}
///***********************************************/
//
///** register_page **/
//
//void on_submit_button_clicked(GtkWidget *button, GtkWidget *chat_app)
//{
//    cmc_log_info("CLICK TO SUBMIT BUTTON");
//    user_data.type = REGISTER;
//    if ((errno = create_user_data()) == 107)
//    {
//        gtk_widget_show_now(GTK_WIDGET(chat_app));
//        GtkWidget *toplevel = gtk_widget_get_toplevel(button);
//        cmc_log_info("TEST");
//    }
//    else
//    {
//        //ToDo: Raise error in window
//        cmc_log_error("error: %d", errno);
//    }
//}
//
//void on_email_entry_changed(GtkEntry *entry)
//{
//    cmc_log_info("EMAIL ENTRY CHANGED");
//    //ToDo: add string validation
//    strcpy(user_data.user_attributes.email, gtk_entry_get_text(entry));
//
//    cmc_log_info("[Current email = %s]", user_data.user_attributes.email);
//}
//
//void on_phonenumber_entry_changed(GtkEntry *entry)
//{
//    cmc_log_info("PHONE_NUMBER ENTRY CHANGED");
//    strcpy(user_data.user_attributes.ph_number, gtk_entry_get_text(entry));
//}
//
//void on_age_entry_changed(GtkEntry *entry)
//{
//    cmc_log_info("AGE ENTRY CHANGED");
//    strcpy(user_data.user_attributes.age, gtk_entry_get_text(entry));
//    cmc_log_info("[Current age = %s]", user_data.user_attributes.age);
//}
//
//void on_rep_password_entry_changed(GtkEntry *rep_password, GtkEntry *password)
//{
////    if (strcmp(gtk_entry_get_text(rep_password), gtk_entry_get_text(password)) == 0)
////        cmc_log_info("REP_PASSWORD ENTRY CHANGED");
////    else
////        cmc_log_info("PASSWORD ENTRY INCORRECT");
//}
//
//void on_fullname_entry_changed(GtkEntry *entry)
//{
//    cmc_log_info("FULLNAME ENTRY CHANGED");
//    strcpy(user_data.user_attributes.fullname, gtk_entry_get_text(entry));
//    cmc_log_info("[Current fullname = %s]", user_data.user_attributes.fullname);
//}
//
//void on_user_logo_press(GtkEntry *entry)
//{
//    cmc_log_info("CLICK TO USER LOGO");
//}
//
///***********************************************/
//
//
//
//
//
//
///* Test Chat Window */
//
//
//void create_msg_json(gchar *msg_text)
//{
//    json_t *json = json_object();
//    json_object_set_new(json, "msg_text", json_string(msg_text));
//    send_json(json, user_data.server_attributes.socket);
//}
//
//void send_msg(GtkButton *chat_send_btn, GtkTextView *chat_msg_entry)
//{
//    GtkTextIter start, end;
//    GtkTextBuffer *buffer = gtk_text_view_get_buffer (chat_msg_entry);
//    gchar *text;
//
//    gtk_text_buffer_get_bounds (buffer, &start, &end);
//    text = gtk_text_buffer_get_text (buffer, &start, &end, FALSE);
//
////    cmc_log_info("[Buffer text: %s]", text);
//
//    gpointer *gp = get_widget(user_data.page->widgets, "chat_msg_lst_box");
//    GtkWidget *msg = msg_widget_factory(P_MSG, text, user_data.user_attributes.username);
//
//    gtk_list_box_insert(GTK_LIST_BOX(gp), GTK_WIDGET(msg), -1);
//    gtk_widget_show_all(GTK_WIDGET(gp));
//    gtk_text_buffer_set_text(buffer, "", -1);
//    g_free(text);
//}
//
//void create_chats_buttons(gpointer *chat_list)
//{
//
//}
//
///***********************************************/
//
//
//
//
//
/////*
//// * Copyright (c) 2015 Andrew Kelley
//// *
//// * This file is part of libsoundio, which is MIT licensed.
//// * See http://opensource.org/licenses/MIT
//// */
////
////#include <soundio/soundio.h>
////#include <stdio.h>
////#include <stdarg.h>
////#include <stdlib.h>
////#include <string.h>
////#include <math.h>
////
////struct SoundIoRingBuffer *ring_buffer = NULL;
////static enum SoundIoFormat prioritized_formats[] = {
////        SoundIoFormatFloat32NE,
////        SoundIoFormatFloat32FE,
////        SoundIoFormatS32NE,
////        SoundIoFormatS32FE,
////        SoundIoFormatS24NE,
////        SoundIoFormatS24FE,
////        SoundIoFormatS16NE,
////        SoundIoFormatS16FE,
////        SoundIoFormatFloat64NE,
////        SoundIoFormatFloat64FE,
////        SoundIoFormatU32NE,
////        SoundIoFormatU32FE,
////        SoundIoFormatU24NE,
////        SoundIoFormatU24FE,
////        SoundIoFormatU16NE,
////        SoundIoFormatU16FE,
////        SoundIoFormatS8,
////        SoundIoFormatU8,
////        SoundIoFormatInvalid,
////};
////static int prioritized_sample_rates[] = {
////        48000,
////        44100,
////        96000,
////        24000,
////        0,
////};
////__attribute__ ((cold))
////__attribute__ ((noreturn))
////__attribute__ ((format (printf, 1, 2)))
////static void panic(const char *format, ...) {
////    va_list ap;
////    va_start(ap, format);
////    vfprintf(stderr, format, ap);
////    fprintf(stderr, "\n");
////    va_end(ap);
////    abort();
////}
////static int min_int(int a, int b) {
////    return (a < b) ? a : b;
////}
////static void read_callback(struct SoundIoInStream *instream, int frame_count_min, int frame_count_max) {
////    struct SoundIoChannelArea *areas;
////    int err;
////    char *write_ptr = soundio_ring_buffer_write_ptr(ring_buffer);
////    int free_bytes = soundio_ring_buffer_free_count(ring_buffer);
////    int free_count = free_bytes / instream->bytes_per_frame;
////    if (frame_count_min > free_count)
////        panic("ring buffer overflow");
////    int write_frames = min_int(free_count, frame_count_max);
////    int frames_left = write_frames;
////    for (;;) {
////        int frame_count = frames_left;
////        if ((err = soundio_instream_begin_read(instream, &areas, &frame_count)))
////            panic("begin read error: %s", soundio_strerror(err));
////        if (!frame_count)
////            break;
////        if (!areas) {
////            // Due to an overflow there is a hole. Fill the ring buffer with
////            // silence for the size of the hole.
////            memset(write_ptr, 0, frame_count * instream->bytes_per_frame);
////            fprintf(stderr, "Dropped %d frames due to internal overflow\n", frame_count);
////        } else {
////            for (int frame = 0; frame < frame_count; frame += 1) {
////                for (int ch = 0; ch < instream->layout.channel_count; ch += 1) {
////                    memcpy(write_ptr, areas[ch].ptr, instream->bytes_per_sample);
////                    areas[ch].ptr += areas[ch].step;
////                    write_ptr += instream->bytes_per_sample;
////                }
////            }
////        }
////        if ((err = soundio_instream_end_read(instream)))
////            panic("end read error: %s", soundio_strerror(err));
////        frames_left -= frame_count;
////        if (frames_left <= 0)
////            break;
////    }
////    int advance_bytes = write_frames * instream->bytes_per_frame;
////    soundio_ring_buffer_advance_write_ptr(ring_buffer, advance_bytes);
////}
////static void write_callback(struct SoundIoOutStream *outstream, int frame_count_min, int frame_count_max) {
////    struct SoundIoChannelArea *areas;
////    int frames_left;
////    int frame_count;
////    int err;
////    char *read_ptr = soundio_ring_buffer_read_ptr(ring_buffer);
////    int fill_bytes = soundio_ring_buffer_fill_count(ring_buffer);
////    int fill_count = fill_bytes / outstream->bytes_per_frame;
////    if (frame_count_min > fill_count) {
////        // Ring buffer does not have enough data, fill with zeroes.
////        frames_left = frame_count_min;
////        for (;;) {
////            frame_count = frames_left;
////            if (frame_count <= 0)
////                return;
////            if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count)))
////                panic("begin write error: %s", soundio_strerror(err));
////            if (frame_count <= 0)
////                return;
////            for (int frame = 0; frame < frame_count; frame += 1) {
////                for (int ch = 0; ch < outstream->layout.channel_count; ch += 1) {
////                    memset(areas[ch].ptr, 0, outstream->bytes_per_sample);
////                    areas[ch].ptr += areas[ch].step;
////                }
////            }
////            if ((err = soundio_outstream_end_write(outstream)))
////                panic("end write error: %s", soundio_strerror(err));
////            frames_left -= frame_count;
////        }
////    }
////    int read_count = min_int(frame_count_max, fill_count);
////    frames_left = read_count;
////    while (frames_left > 0) {
////        int frame_count = frames_left;
////        if ((err = soundio_outstream_begin_write(outstream, &areas, &frame_count)))
////            panic("begin write error: %s", soundio_strerror(err));
////        if (frame_count <= 0)
////            break;
////        for (int frame = 0; frame < frame_count; frame += 1) {
////            for (int ch = 0; ch < outstream->layout.channel_count; ch += 1) {
////                memcpy(areas[ch].ptr, read_ptr, outstream->bytes_per_sample);
////                areas[ch].ptr += areas[ch].step;
////                read_ptr += outstream->bytes_per_sample;
////            }
////        }
////        if ((err = soundio_outstream_end_write(outstream)))
////            panic("end write error: %s", soundio_strerror(err));
////        frames_left -= frame_count;
////    }
////    soundio_ring_buffer_advance_read_ptr(ring_buffer, read_count * outstream->bytes_per_frame);
////}
////static void underflow_callback(struct SoundIoOutStream *outstream) {
////    static int count = 0;
////    fprintf(stderr, "underflow %d\n", ++count);
////}
////static int usage(char *exe) {
////    fprintf(stderr, "Usage: %s [options]\n"
////                    "Options:\n"
////                    "  [--backend dummy|alsa|pulseaudio|jack|coreaudio|wasapi]\n"
////                    "  [--in-device id]\n"
////                    "  [--in-raw]\n"
////                    "  [--out-device id]\n"
////                    "  [--out-raw]\n"
////                    "  [--latency seconds]\n"
////            , exe);
////    return 1;
////}
////int main(int argc, char **argv) {
////    char *exe = argv[0];
////    enum SoundIoBackend backend = SoundIoBackendNone;
////    char *in_device_id = NULL;
////    char *out_device_id = NULL;
////    bool in_raw = false;
////    bool out_raw = false;
////    double microphone_latency = 0.2; // seconds
////    for (int i = 1; i < argc; i += 1) {
////        char *arg = argv[i];
////        if (arg[0] == '-' && arg[1] == '-') {
////            if (strcmp(arg, "--in-raw") == 0) {
////                in_raw = true;
////            } else if (strcmp(arg, "--out-raw") == 0) {
////                out_raw = true;
////            } else if (++i >= argc) {
////                return usage(exe);
////            } else if (strcmp(arg, "--backend") == 0) {
////                if (strcmp("dummy", argv[i]) == 0) {
////                    backend = SoundIoBackendDummy;
////                } else if (strcmp("alsa", argv[i]) == 0) {
////                    backend = SoundIoBackendAlsa;
////                } else if (strcmp("pulseaudio", argv[i]) == 0) {
////                    backend = SoundIoBackendPulseAudio;
////                } else if (strcmp("jack", argv[i]) == 0) {
////                    backend = SoundIoBackendJack;
////                } else if (strcmp("coreaudio", argv[i]) == 0) {
////                    backend = SoundIoBackendCoreAudio;
////                } else if (strcmp("wasapi", argv[i]) == 0) {
////                    backend = SoundIoBackendWasapi;
////                } else {
////                    fprintf(stderr, "Invalid backend: %s\n", argv[i]);
////                    return 1;
////                }
////            } else if (strcmp(arg, "--in-device") == 0) {
////                in_device_id = argv[i];
////            } else if (strcmp(arg, "--out-device") == 0) {
////                out_device_id = argv[i];
////            } else if (strcmp(arg, "--latency") == 0) {
////                microphone_latency = atof(argv[i]);
////            } else {
////                return usage(exe);
////            }
////        } else {
////            return usage(exe);
////        }
////    }
////    struct SoundIo *soundio = soundio_create();
////    if (!soundio)
////        panic("out of memory");
////    int err = (backend == SoundIoBackendNone) ?
////              soundio_connect(soundio) : soundio_connect_backend(soundio, backend);
////    if (err)
////        panic("error connecting: %s", soundio_strerror(err));
////    soundio_flush_events(soundio);
////    int default_out_device_index = soundio_default_output_device_index(soundio);
////    if (default_out_device_index < 0)
////        panic("no output device found");
////    int default_in_device_index = soundio_default_input_device_index(soundio);
////    if (default_in_device_index < 0)
////        panic("no input device found");
////    int in_device_index = default_in_device_index;
////    if (in_device_id) {
////        bool found = false;
////        for (int i = 0; i < soundio_input_device_count(soundio); i += 1) {
////            struct SoundIoDevice *device = soundio_get_input_device(soundio, i);
////            if (device->is_raw == in_raw && strcmp(device->id, in_device_id) == 0) {
////                in_device_index = i;
////                found = true;
////                soundio_device_unref(device);
////                break;
////            }
////            soundio_device_unref(device);
////        }
////        if (!found)
////            panic("invalid input device id: %s", in_device_id);
////    }
////    int out_device_index = default_out_device_index;
////    if (out_device_id) {
////        bool found = false;
////        for (int i = 0; i < soundio_output_device_count(soundio); i += 1) {
////            struct SoundIoDevice *device = soundio_get_output_device(soundio, i);
////            if (device->is_raw == out_raw && strcmp(device->id, out_device_id) == 0) {
////                out_device_index = i;
////                found = true;
////                soundio_device_unref(device);
////                break;
////            }
////            soundio_device_unref(device);
////        }
////        if (!found)
////            panic("invalid output device id: %s", out_device_id);
////    }
////    struct SoundIoDevice *out_device = soundio_get_output_device(soundio, out_device_index);
////    if (!out_device)
////        panic("could not get output device: out of memory");
////    struct SoundIoDevice *in_device = soundio_get_input_device(soundio, in_device_index);
////    if (!in_device)
////        panic("could not get input device: out of memory");
////    fprintf(stderr, "Input device: %s\n", in_device->name);
////    fprintf(stderr, "Output device: %s\n", out_device->name);
////    soundio_device_sort_channel_layouts(out_device);
////    const struct SoundIoChannelLayout *layout = soundio_best_matching_channel_layout(
////            out_device->layouts, out_device->layout_count,
////            in_device->layouts, in_device->layout_count);
////    if (!layout)
////        panic("channel layouts not compatible");
////    int *sample_rate;
////    for (sample_rate = prioritized_sample_rates; *sample_rate; sample_rate += 1) {
////        if (soundio_device_supports_sample_rate(in_device, *sample_rate) &&
////            soundio_device_supports_sample_rate(out_device, *sample_rate))
////        {
////            break;
////        }
////    }
////    if (!*sample_rate)
////        panic("incompatible sample rates");
////    enum SoundIoFormat *fmt;
////    for (fmt = prioritized_formats; *fmt != SoundIoFormatInvalid; fmt += 1) {
////        if (soundio_device_supports_format(in_device, *fmt) &&
////            soundio_device_supports_format(out_device, *fmt))
////        {
////            break;
////        }
////    }
////    if (*fmt == SoundIoFormatInvalid)
////        panic("incompatible sample formats");
////    struct SoundIoInStream *instream = soundio_instream_create(in_device);
////    if (!instream)
////        panic("out of memory");
////    instream->format = *fmt;
////    instream->sample_rate = *sample_rate;
////    instream->layout = *layout;
////    instream->software_latency = microphone_latency;
////    instream->read_callback = read_callback;
////    if ((err = soundio_instream_open(instream))) {
////        fprintf(stderr, "unable to open input stream: %s", soundio_strerror(err));
////        return 1;
////    }
////    struct SoundIoOutStream *outstream = soundio_outstream_create(out_device);
////    if (!outstream)
////        panic("out of memory");
////    outstream->format = *fmt;
////    outstream->sample_rate = *sample_rate;
////    outstream->layout = *layout;
////    outstream->software_latency = microphone_latency;
////    outstream->write_callback = write_callback;
////    outstream->underflow_callback = underflow_callback;
////    if ((err = soundio_outstream_open(outstream))) {
////        fprintf(stderr, "unable to open output stream: %s", soundio_strerror(err));
////        return 1;
////    }
////    int capacity = microphone_latency * 2 * instream->sample_rate * instream->bytes_per_frame;
////    ring_buffer = soundio_ring_buffer_create(soundio, capacity);
////    if (!ring_buffer)
////        panic("unable to create ring buffer: out of memory");
////    char *buf = soundio_ring_buffer_write_ptr(ring_buffer);
////    int fill_count = microphone_latency * outstream->sample_rate * outstream->bytes_per_frame;
////    memset(buf, 0, fill_count);
////    soundio_ring_buffer_advance_write_ptr(ring_buffer, fill_count);
////    if ((err = soundio_instream_start(instream)))
////        panic("unable to start input device: %s", soundio_strerror(err));
////    if ((err = soundio_outstream_start(outstream)))
////        panic("unable to start output device: %s", soundio_strerror(err));
////    for (;;)
////        soundio_wait_events(soundio);
////    soundio_outstream_destroy(outstream);
////    soundio_instream_destroy(instream);
////    soundio_device_unref(in_device);
////    soundio_device_unref(out_device);
////    soundio_destroy(soundio);
////    return 0;
////}

#include "client.h"
#include <uv.h>
#include <stdlib.h>
#include <utl/log.h>

static uv_loop_t *loop;
static void on_close(uv_handle_t* handle);
static void on_connect(uv_connect_t* connection, int status);
static void on_write(uv_write_t* req, int status);


void on_close(uv_handle_t* handle)
{
    cmc_log_info("closed.");
}

void on_write(uv_write_t* req, int status)
{
    if (status) {
        perror( "uv_write error ");
        return;
    }
    cmc_log_info("wrote.\n");
    free(req);
}

void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
    cmc_log_info("on_read. %p\n", tcp);

    if(nread >= 0) {
        cmc_log_info("read: %s\n", tcp->data);
        cmc_log_info("read: %s\n", buf->base);
    }
    else {
        cmc_log_error("we got an EOF");
        uv_close((uv_handle_t*)tcp, on_close);
    }

    free(buf->base);
}

void write2(uv_stream_t* stream, char *data, int len2) {
    uv_buf_t buffer[] = {
            {.base = data, .len = len2}
    };
    uv_write_t *req = malloc(sizeof(uv_write_t));
    uv_write(req, stream, buffer, 1, on_write);
}

static void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
    *buf = uv_buf_init(malloc(size), size);
}

void on_connect(uv_connect_t* connection, int status)
{
    // ToDo: Add more info
    if (status < 0)
        cmc_log_fatal("failed to connect: %s\n", uv_strerror(status));

    cmc_log_info("connected. %p %d\n", connection, status);

    uv_stream_t* stream = connection->handle;
    free(connection);
    write2(stream, "echo  world!", 12);
    uv_read_start(stream, alloc_cb, on_read);
}

void init_connection(char *host, int port)
{
    uv_tcp_t *socket = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, socket);
    uv_tcp_keepalive(socket, 1, 60);

    struct sockaddr_in dest; // Where send data
    uv_ip4_addr(host, port, &dest);

    uv_connect_t *connection = malloc(sizeof(uv_connect_t));
    cmc_log_info("allocated %p\n", connection);
    uv_tcp_connect(connection, socket, (const struct sockaddr*)&dest, on_connect);
}



//ToDo: Split all on logical containers and get with gtk_container_foreach()
int main(int argc, char **argv)
{
    // ToDo: Free that memory
    t_user_data *user_data = malloc(sizeof(t_user_data));

    loop = uv_default_loop();
    init_connection(argc != 2 ? "127.0.0.1" : argv[1], 5000);

    gtk_init(&argc, &argv);
    user_data->page = select_page(TEST_PAGE);

    //ToDo: rename variable
    gpointer *gp = get_widget(user_data->page->widgets, "login_window");

    gtk_widget_show_now(GTK_WIDGET(gp));
    uv_loop_set_data(loop, user_data);

    // ToDo: Free gtk
    gtk_main();
    system("leaks -q uchat_gui");
    return 0;
}