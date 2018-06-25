//
//  jrx_operator_do.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _SenderType, class _NewChildType>
jrx::operators::Do<_SenderType, _NewChildType>::Do(std::function<void(_SenderType &)> _pPreducate)
: Observable<_SenderType, _NewChildType>([this](_SenderType &value) -> _SenderType {
    m_pPreducate(value);
    return value;
}){
    m_pPreducate = _pPreducate;
}

template <class _SenderType, class _NewChildType>
auto jrx::operators::Do<_SenderType, _NewChildType>::onNext(_SenderType &value) -> void {

    m_pPreducate(value);
    Observable<_SenderType, _NewChildType>::onNext(value);
}



