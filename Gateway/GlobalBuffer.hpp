#pragma once
#include <vector>
#include <deque>
#include <mutex>
#include <condition_variable>

// A simple global, thread-safe FIFO of byte payloads.
class GlobalBuffer
{
public:
    void Push(std::vector<uint8_t> payload)
    {
        {
            std::lock_guard<std::mutex> lock(_mx);
            _q.emplace_back(std::move(payload));
        }
        _cv.notify_one();
    }

    // Blocking pop; returns false when stop requested and queue empty
    bool PopBlocking(std::vector<uint8_t>& out)
    {
        std::unique_lock<std::mutex> lock(_mx);
        _cv.wait(lock, [this] { return !_q.empty() || _stop; });
        if (_q.empty() && _stop) return false;
        out = std::move(_q.front());
        _q.pop_front();
        return true;
    }

    void Stop()
    {
        {
            std::lock_guard<std::mutex> lock(_mx);
            _stop = true;
        }
        _cv.notify_all();
    }

private:
    std::deque<std::vector<uint8_t>> _q;
    std::mutex _mx;
    std::condition_variable _cv;
    bool _stop{false};
};

// Single global instance getter
GlobalBuffer& GetGlobalBuffer();
