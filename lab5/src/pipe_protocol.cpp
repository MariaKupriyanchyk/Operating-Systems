#include "pipe_protocol.h"
#include <stdexcept>

static void write_all(HANDLE pipe, const void* data, unsigned int size) {
    DWORD written = 0;
    if (!WriteFile(pipe, data, size, &written, nullptr) || written != size) {
        throw std::runtime_error("Pipe write failed");
    }
}

static void read_all(HANDLE pipe, void* data, unsigned int size) {
    DWORD read = 0;
    if (!ReadFile(pipe, data, size, &read, nullptr) || read != size) {
        throw std::runtime_error("Pipe read failed");
    }
}

void send_request(HANDLE pipe, const PipeRequest& req) {
    write_all(pipe, &req, sizeof(PipeRequest));
}

void receive_request(HANDLE pipe, PipeRequest& req) {
    read_all(pipe, &req, sizeof(PipeRequest));
}

void send_response(HANDLE pipe, const PipeResponse& resp) {
    write_all(pipe, &resp, sizeof(PipeResponse));
}

void receive_response(HANDLE pipe, PipeResponse& resp) {
    read_all(pipe, &resp, sizeof(PipeResponse));
}