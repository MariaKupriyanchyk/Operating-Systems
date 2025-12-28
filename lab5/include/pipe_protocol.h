#pragma once
#include <windows.h>
#include "employee.h"

enum RequestType {
    REQ_READ = 1,
    REQ_WRITE = 2,
    REQ_RELEASE = 3,
    REQ_EXIT = 4
};

struct PipeRequest {
    RequestType type;
    int employee_id;
    employee data;
};

struct PipeResponse {
    bool success;
    employee data;
};

void send_request(HANDLE pipe, const PipeRequest& req);
void receive_request(HANDLE pipe, PipeRequest& req);
void send_response(HANDLE pipe, const PipeResponse& resp);
void receive_response(HANDLE pipe, PipeResponse& resp);