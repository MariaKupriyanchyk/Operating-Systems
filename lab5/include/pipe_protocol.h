#pragma once
#include "employee.h"

enum RequestType {
    REQ_READ,
    REQ_MODIFY_BEGIN,
    REQ_MODIFY_COMMIT,
    REQ_RELEASE,
    REQ_EXIT
};

struct PipeRequest {
    RequestType type;
    int employee_id;
    employee data;
};

struct PipeResponse {
    int success;
    employee data;
};
