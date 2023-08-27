#pragma once

#include "rumble.h"

struct RumbleImpl;
struct Rumble
{
    static Rumble& get();
    Rumble(const Rumble&) = delete;
    Rumble(Rumble&) = delete;
    void init();
    void deinit();
    void write(uint32_t address, uint8_t data);
private:
    explicit Rumble() {}
    void thread_func();

    RumbleImpl* impl = nullptr;
};
