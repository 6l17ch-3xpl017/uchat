#include <uv.h>
#include "server.h"

#define DEFAULT_PORT 5000
#define DEFAULT_BACKLOG 128 // backlog indicates the number of connections the kernel might queue, same as listen(2)

uv_loop_t *loop;
struct sockaddr_in addr;

typedef struct {
    uv_write_t req;
    uv_buf_t buf;
} write_req_t;

void free_write_req(uv_write_t *req) {
    write_req_t *wr = (write_req_t *)req;
    free(wr->buf.base);
    free(wr);
}

void echo_write(uv_write_t *req, int status) {
    if (status)
        cmc_log_error("Write error %s\n", uv_strerror(status));
    free_write_req(req);
}

void on_close(uv_handle_t* handle) {
    free(handle);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    if (nread > 0) {
        write_req_t *req = malloc(sizeof(write_req_t));
        req->buf = uv_buf_init(buf->base, nread);
        cmc_log_info("TEST0: %s", buf->base);
        uv_write((uv_write_t *)req, client, &req->buf, 1, echo_write);
        cmc_log_info("TEST1: %s", buf->base);
        return;
    }
    if (nread < 0) {
        if (nread != UV_EOF)
            cmc_log_error("Read error %s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) client, on_close);
    }
    free(buf->base);
}

void alloc_buffer(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    // ToDo: Learn more about *handle

    buf->base = (char *)malloc(suggested_size);
    buf->len = suggested_size;
}

void on_new_connection(uv_stream_t *server, int status) {

    if (status < 0)
        cmc_log_fatal("New connection error %s\n", uv_strerror(status));

    // ToDo: Add more info about someone
    cmc_log_info("Some one connected!\n");

    uv_tcp_t *client = malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);

    if (uv_accept(server, (uv_stream_t *)client) == 0)
        uv_read_start((uv_stream_t *)client, alloc_buffer, echo_read);

    else
        uv_close((uv_handle_t *)client, on_close);

}

void print_ip_port(uv_tcp_t client)
{
    char ip[17] = {0};
    struct sockaddr_in _addr = {0};
    int alen = 0;

    uv_tcp_getsockname(&client, (struct sockaddr *)&_addr, &alen);
    uv_ip4_name((const struct sockaddr_in *)&_addr, ip, sizeof(ip));
    cmc_log_info("%s:%d", ip, _addr.sin_port);
}

int main()
{
    loop = uv_default_loop();

    uv_tcp_t server;
    int r;
    uv_tcp_init(loop, &server);

    // ToDo: Change IP
    uv_ip4_addr("0.0.0.0", DEFAULT_PORT, &addr); // Function convert human readable pair ip:port to sockaddr_in struct

    uv_tcp_bind(&server, (const struct sockaddr *)&addr, 0);
    r = uv_listen((uv_stream_t*) &server, DEFAULT_BACKLOG, on_new_connection);

//    print_ip_port(server);
//
    if(r)
        cmc_log_fatal("Listen error %s\n", uv_strerror(r));
//
//    // ToDo: Add more info about server
//    cmc_log_info("Server create successful\n"
//                 "IP: %"
//                 "PORT:");

    return uv_run(loop, UV_RUN_DEFAULT);
}