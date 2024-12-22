//
//  jrx_partial_value_observer.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty, class _Ty2>
PartialValueObserver<_Ty, _Ty2>::PartialValueObserver(ObservablePtr<_Ty> obs, _Ty _Ty2::* valueSetter) {
    m_pValueSetter = valueSetter;
    observable = obs;
    /*
    obs->onNext({
        this->onNextValue();
    });*/
    /*
    obs->onNextValue([this](){
        this->onValuePosted();
    });*/
    
    
    
    this->observeOnSubscribe([&](){
        observable->subscribe([this](_Ty val){
            PartialValueHolder<_Ty2>::m_pSharedObject->*m_pValueSetter = val;
        });
        // TODO: FIX
    });
}
/*
template <class _Ty, class _Ty2>
auto PartialValueObserver<_Ty, _Ty2>::onStart() -> void {
    observable->start();
}*/


