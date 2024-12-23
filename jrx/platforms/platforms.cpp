//
//  platforms.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/23/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

#if defined (__unix__) || (defined (__APPLE__) && defined (__MACH__))

#define canDoMemoryTest 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mach/mach.h>

auto jrx::platforms::getMemoryUsage() -> size_t {
    struct task_basic_info info;
    mach_msg_type_number_t infoCount = TASK_BASIC_INFO_COUNT;

    if (task_info(mach_task_self(), TASK_BASIC_INFO, (task_info_t)&info, &infoCount) != KERN_SUCCESS) {
        return 0; // Failed to retrieve info
    }

    return info.resident_size; // Memory in bytes
}
#else
#warning Could not determine memory usage of the test for this system. This should be all fine though!
#endif

auto jrx::platforms::testLeakage(int runCount, std::function<void()> func) -> void {
    
    size_t leakingMemoryInBytes = 0;
    size_t leakingObjectsCount = 0;
    
#ifdef canDoMemoryTest
    auto bytesUsed = jrx::platforms::getMemoryUsage();
#endif
    
    for (int i = 0; i < runCount; i++) {
        func();
    }
    
#ifdef canDoMemoryTest
    leakingMemoryInBytes = jrx::platforms::getMemoryUsage() - bytesUsed;
#endif
    // Now print
#ifdef canDoMemoryTest
    std::cout << "Memory leak: " << leakingMemoryInBytes << " bytes \n";
#else
    std::cout << "Memory leak: " << "<<!could not detect!>>" << "\n";
#endif
    std::cout << "Living objects: " << jrx::core::RetainedObject::getAliveObjectCount() << "\n";
}
