//
//  jrx_untyped_subscriber.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

auto UntypedSubscriber::observeOnStart(std::function<void()> func) -> void {
    m_vStartObservers.push_back(func);
}

auto UntypedSubscriber::observeOnSubscribe(std::function<void()> func) -> void {
    m_vSubscribeObservers.push_back(func);
}

auto UntypedSubscriber::observeOnNextValue(std::function<void ()> func) -> void {
    m_vOnNextObservers.push_back(func);
}

auto UntypedSubscriber::observeOnCompleted(std::function<void()> func) -> void {
    m_vCompletedObservers.push_back(func);
}

auto UntypedSubscriber::observeOnError(std::function<void()> func) -> void {
    m_vErrorObservers.push_back(func);
}

auto UntypedSubscriber::onStart() -> void {
    for (auto func : m_vStartObservers) {
        func();
    }
    
    for (auto child : m_vChildren) {
        child->onStart();
    }
}

auto UntypedSubscriber::onSubscribe() -> void {
    for (auto func : m_vSubscribeObservers) {
        func();
    }
    
    if (m_pParent != nullptr) {
        m_pParent->onSubscribe();
    }
}
auto UntypedSubscriber::onNextValue() -> void {
    for (auto func : m_vOnNextObservers) {
        func();
    }
}
auto UntypedSubscriber::onCompleted() -> void {
    for (auto func : m_vCompletedObservers) {
        func();
    }
}
auto UntypedSubscriber::onError() -> void {
    for (auto func : m_vErrorObservers) {
        func();
    }
}
