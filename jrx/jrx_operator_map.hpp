//
//  jorx_operator_map.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//




template <class _SenderType, class _NewChildType>
jrx::operators::Map<_SenderType, _NewChildType>::Map(std::function<_NewChildType(_SenderType &)> _pPreducate)
: Observable<_SenderType, _NewChildType>([this](_SenderType &value) -> _NewChildType {
    auto tmp = m_pPreducate(value);
    return tmp;
}){
    m_pPreducate = _pPreducate;
}

template <class _SenderType, class _NewChildType>
auto jrx::operators::Map<_SenderType, _NewChildType>::onNext(_SenderType &value) -> void {
    
    auto converted = m_pPreducate(value);
    
    for (int i = 0; i < this->m_vChildren.size(); i++) {
        this->m_vChildren[i]->onNext(converted);
    }
    for (int i = 0; i < this->m_vSubscribersOnNext.size(); i++) {
        this->m_vSubscribersOnNext[i](converted);
    }
}
