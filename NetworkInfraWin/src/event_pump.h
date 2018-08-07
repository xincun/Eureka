/*
 @ 0xCCCCCCCC
*/

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef EVENT_PUMP_H_
#define EVENT_PUMP_H_

#include <chrono>
#include <unordered_map>
#include <vector>

#include <Windows.h>

#include "kbase/basic_macros.h"
#include "kbase/scoped_handle.h"

#include "io_context.h"
#include "notifier.h"

namespace network {

class EventPump {
public:
    EventPump();

    ~EventPump();

    DISALLOW_COPY(EventPump);

    DISALLOW_MOVE(EventPump);

    // TODO: Abstract this pair.
    void Pump(std::chrono::milliseconds timeout,
              std::vector<std::pair<Notifier*, IOContext*>>& active_notifiers);

    void Wakeup() const;

    void SubscribeNotifier(Notifier* notifier);

    // void RemoveNotifier();

private:
    static constexpr size_t kInitialEventNum = 8;

    kbase::ScopedWinHandle io_port_;
    std::vector<OVERLAPPED_ENTRY> io_events_;

    using NotifierMap = std::unordered_map<UINT_PTR, Notifier>;
    NotifierMap notifier_table_;
};

}   // namespace network

#endif  // EVENT_PUMP_H_
