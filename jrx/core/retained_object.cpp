//
//  retained_object.cpp
//  jrx
//
//  Created by Jonas Johansson on 12/23/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

size_t jrx::core::RetainedObject::s_iObjectCount = 0;

jrx::core::RetainedObject
::RetainedObject() {
    s_iObjectCount++;
}

jrx::core::RetainedObject
::~RetainedObject() {
    s_iObjectCount--;
    
    if (tracked) {
        std::cout << "objects: " << s_iObjectCount << "\n";
    }
}

auto jrx::core::RetainedObject
::getAliveObjectCount() -> size_t {
    return s_iObjectCount;
}

auto jrx::core::RetainedObject
::retain() -> void {
    m_iCounter++;
    
    if (tracked) {
        std::cout << "retain count: " << m_iCounter << "\n";
    }
}

auto jrx::core::RetainedObject
::release() -> bool {
    m_iCounter--;
    
    if (tracked) {
        std::cout << "retain count: " << m_iCounter << "\n";
    }
    
    assert(m_iCounter >= 0);
    
    if (m_iCounter == 0) {
        if (jrx::config::automaticMemoryManagement) {
            if (named.size() > 0) {
                std::cout << "deleting: " << named << "\n";
            }
            delete this;
        }
        return true;
    }
    return false;
}
