//
//  jrx_untyped_subscriber.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#include "jrx.h"

jrx::core::UntypedSubscriber
::UntypedSubscriber() :
m_pParent(nullptr) {
    
}

jrx::core::UntypedSubscriber
::~UntypedSubscriber() {
    
}

auto jrx::core::UntypedSubscriber
::getRoot() -> UntypedSubscriber * {
    return m_pParent != nullptr ? m_pParent->getRoot() : this;
}

auto jrx::core::UntypedSubscriber
::observeOnStart(std::function<void()> func) -> void {
    m_vStartObservers.push_back(func);
}

auto jrx::core::UntypedSubscriber
::observeOnSubscribe(std::function<void()> func) -> void {
    m_vSubscribeObservers.push_back(func);
}

auto jrx::core::UntypedSubscriber
::observeOnNext(std::function<void ()> func) -> void {
    m_vOnNextObservers.push_back(func);
}

auto jrx::core::UntypedSubscriber
::observeOnPreviousOrNextValue(std::function<void ()> func) -> void {
    m_vOnAnyObservers.push_back(func);
    
    if (m_bAnyValueSent) {
        func();
    }
}

auto jrx::core::UntypedSubscriber
::observeOnCompleted(std::function<void()> func) -> void {
    m_vCompletedObservers.push_back(func);
}

auto jrx::core::UntypedSubscriber
::observeOnError(std::function<void()> func) -> void {
    m_vErrorObservers.push_back(func);
}

auto jrx::core::UntypedSubscriber
::onStart() -> void {
    for (auto func : m_vStartObservers) {
        func();
    }
    
    for (auto child : m_vChildren) {
        child->onStart();
    }
}

auto jrx::core::UntypedSubscriber
::onSubscribe() -> void {
    if (m_pParent != nullptr) {
        m_pParent->onSubscribe();
    }
    for (auto func : m_vSubscribeObservers) {
        func();
    }
}

auto jrx::core::UntypedSubscriber
::onNextValue() -> void {
    
    m_bAnyValueSent = true;
    
    for (auto func : m_vOnAnyObservers) {
        func();
    }
    
    for (auto func : m_vOnNextObservers) {
        func();
    }
}

auto jrx::core::UntypedSubscriber
::onCompleted() -> void {
    for (auto func : m_vCompletedObservers) {
        func();
    }
}

auto jrx::core::UntypedSubscriber
::onError() -> void {
    for (auto func : m_vErrorObservers) {
        func();
    }
}

auto jrx::core::UntypedSubscriber
::setParent(UntypedSubscriber *_pParent) -> void {
    m_pParent = _pParent;
}
