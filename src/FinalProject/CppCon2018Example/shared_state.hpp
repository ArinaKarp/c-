//
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//
#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include "websocket_session.hpp"

// Represents the shared server state
class shared_state
{
    // This simple method of tracking
    // sessions only works with an implicit
    // strand (i.e. a single-threaded server)
    std::unordered_set<websocket_session*> sessions_;

public:
    void join  (websocket_session& session);
    void leave (websocket_session& session);
    void send  (std::string message);
};
