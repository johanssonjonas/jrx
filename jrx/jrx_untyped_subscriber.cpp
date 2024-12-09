//
//  jrx_untyped_subscriber.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

auto UntypedSubscriber::start() -> void {
    onStart();
}

auto UntypedSubscriber::onNextValue(std::function<void()> func) -> void {
    m_vPostObservers.push_back(func);
    
    if (_bPostedValue) {
        func(); // TODO: Not sure if this one is needed or not?
    }
}

auto UntypedSubscriber::onValuePosted() -> void {
    for (auto func : m_vPostObservers) {
        func();
    }
    _bPostedValue = true;
}

auto UntypedSubscriber::onStart() -> void {
    
}
