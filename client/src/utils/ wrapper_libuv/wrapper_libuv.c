#include "client.h"

void on_close(uv_handle_t* handle)
{
    cmc_log_info("closed.");
}

void on_read(uv_stream_t* tcp, ssize_t nread, const uv_buf_t* buf)
{
    GET_USER_DATA
    cmc_log_info("on_read. %p\n", tcp);

    if(nread >= 0) {
        cmc_log_info("read: %s\n", tcp->data);
        cmc_log_info("read: %s\n", buf->base);

        user_data->struct_attr.response = buf->base; //ToDo: Use just buf;
    }
    else {
        cmc_log_error("we got an EOF");
        uv_close((uv_handle_t*)tcp, on_close);
    }
    free(buf->base);
}

void alloc_cb(uv_handle_t* handle, size_t size, uv_buf_t* buf) {
    *buf = uv_buf_init(malloc(size), size);
}

void on_write(uv_write_t* req, int status)
{
    if (status)
        cmc_log_fatal("uv_write error: %s", uv_err_name(status));

    cmc_log_info("wrote\n");
    free(req);
}