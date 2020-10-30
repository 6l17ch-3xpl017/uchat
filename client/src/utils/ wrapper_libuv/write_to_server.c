#include "client.h"

void write_to_server(uv_stream_t* stream, char *data, int len)
{
    uv_buf_t buffer[] ={{.base = data, .len = len}};
    uv_write_t *req = malloc(sizeof(uv_write_t));
    uv_write(req, stream, buffer, 1, on_write);
}