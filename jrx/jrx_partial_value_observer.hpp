//
//  jrx_partial_value_observer.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _Ty, class _Ty2>
PartialValueObserver<_Ty, _Ty2>::PartialValueObserver(std::shared_ptr<jrx::core::Observable<_Ty, _Ty>> obs, _Ty _Ty2::* valueSetter) {
    m_pValueSetter = valueSetter;
    observable = obs;
    obs->on([this](_Ty &val){
        PartialValueHolder<_Ty2>::m_pSharedObject->*m_pValueSetter = val;
    });
    obs->onNextValue([this](){
        this->onValuePosted();
    });
}

template <class _Ty, class _Ty2>
auto PartialValueObserver<_Ty, _Ty2>::onStart() -> void {
    observable->start();
}


