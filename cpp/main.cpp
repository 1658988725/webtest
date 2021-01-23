/*
 * Copyright (c) 2014 Cesanta Software Limited
 * All rights reserved
 */

#include <chrono>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include "json/json.h"
#include "mongoose.h"
static const char *s_http_port = "8080";
static struct mg_serve_http_opts s_http_server_opts;

bool str2json(std::string str, Json::Value &v) {
    Json::Reader reader;
    Json::Value temp;

    if (!reader.parse(str, temp)) return false;

    v = temp;
    return true;
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *)ev_data;

    switch (ev) {
    case MG_EV_HTTP_REQUEST:
        if (mg_vcmp(&hm->uri, "/hello") == 0) {


            //接收数据，直接用第三方库解析为json
            std::string rsq(hm->body.p);
            Json::Value jsrsq;
            str2json(rsq, jsrsq);
            std::cout << jsrsq.toStyledString() << std::endl;

        } else {
            mg_serve_http(nc, hm,
                          s_http_server_opts); /* Serve static content */
        }
        break;
    default:
        break;
    }
}

int main(int argc, char *argv[]) {
    struct mg_mgr mgr;
    struct mg_connection *nc;

    mg_mgr_init(&mgr, NULL);
    nc = mg_bind(&mgr, s_http_port, ev_handler);
    mg_set_protocol_http_websocket(nc);
    s_http_server_opts.enable_directory_listing = "yes";

    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);

    return 0;
}
