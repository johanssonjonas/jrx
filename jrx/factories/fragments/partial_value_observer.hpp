//
//  jrx_partial_value_observer.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty, class _Ty2> jrx::factories::fragments::PartialValueObserver<_Ty, _Ty2>
::PartialValueObserver(ObservablePtr<_Ty> obs, _Ty _Ty2::* valueSetter) {
    m_pValueSetter = valueSetter;
    observable = obs; // Retain the object so we hold a reference for the subscribe event
    
    this->observeOnSubscribe([&](){
        observable->subscribe([this](_Ty val){
            jrx::factories::fragments::PartialValueHolder<_Ty2>::getSharedObject()->*m_pValueSetter = val;
        });
    });
}

template <class _Ty, class _Ty2> jrx::factories::fragments::PartialValueObserver<_Ty, _Ty2>
::~PartialValueObserver() {
    
}

