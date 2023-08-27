#include "rumble.h"
#include <future>
#include <condition_variable>
#include <thread>
#include <vector>
#include <atomic>
#include <SDL2/SDL.h>

struct RumbleImpl
{
    std::atomic_bool run{true};
    std::atomic_bool written{false};
    std::future<void> future;
    std::condition_variable cv;
    std::mutex mtx;
    uint16_t low_freq;
    uint16_t high_freq;
    uint32_t duration_ms;
    std::vector<SDL_GameController*> controllers;
};

Rumble& Rumble::get()
{
    static Rumble inst;
    return inst;
}

void Rumble::init()
{
    impl = new RumbleImpl{};
    SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
    for (auto i : nall::range(SDL_NumJoysticks()))
        impl->controllers.emplace_back(SDL_GameControllerOpen(i));
    impl->future = std::async(std::launch::async, &Rumble::thread_func, this);

}

void Rumble::deinit()
{
    impl->run.store(false);
    impl->cv.notify_one();
    impl->future.get();
    for (auto* controller : impl->controllers)
        SDL_GameControllerClose(controller);
    delete impl;
    SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
}

void Rumble::write(uint32_t address, uint8_t data)
{
    std::unique_lock<std::mutex> lk{impl->mtx};
    switch (address)
    {
    case 0x2000:
        impl->low_freq = impl->low_freq & 0xFF00 | data;
        break;
    case 0x2001:
        impl->low_freq = impl->low_freq & 0x00FF | data << 8;
        break;
    case 0x2002:
        impl->high_freq = impl->high_freq & 0xFF00 | data;
        break;
    case 0x2003:
        impl->high_freq = impl->high_freq & 0x00FF | data << 8;
        break;
    case 0x2004:
        impl->duration_ms = impl->duration_ms & 0xFFFFFF00 | data;
        break;
    case 0x2005:
        impl->duration_ms = impl->duration_ms & 0xFFFF00FF | data << 8;
        break;
    case 0x2006:
        impl->duration_ms = impl->duration_ms & 0xFF00FFFF | data << 16;
        break;
    case 0x2007:
        impl->duration_ms = impl->duration_ms & 0x00FFFFFF | data << 24;
        impl->written.store(true);
        impl->cv.notify_one();
        break;
    default:
        break;
}
}

void Rumble::thread_func()
{
    while (true)
    {
        std::unique_lock lk{impl->mtx};
        if (!impl->written.load())
            impl->cv.wait(lk);
        impl->written.store(false);
        if (!impl->run.load())
            return;
        for (auto* controller : impl->controllers)
            SDL_GameControllerRumble(controller, impl->low_freq,
                                     impl->high_freq, impl->duration_ms);
        impl->cv.wait_for(lk, std::chrono::milliseconds(impl->duration_ms));
        if (!impl->written.load())
            for (auto* controller : impl->controllers)
                SDL_GameControllerRumble(controller, 0, 0, 0);
    }
}
