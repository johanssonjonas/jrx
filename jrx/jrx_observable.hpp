//
//  jorx_observable.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::just(_ChildrenType &&value) -> std::shared_ptr<Observable<_SenderType>> {
    
    std::shared_ptr<Observable<_SenderType>> observable = std::shared_ptr<Observable<_SenderType>>{
        new Observable<_SenderType>([&] {
            _ChildrenType hurp = value;
            observable->onNext(hurp);
        })
    };
    
    return observable;
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::forEach(std::vector<_ChildrenType> &&value) -> std::shared_ptr<Observable<_SenderType>> {
    
    std::shared_ptr<Observable<_SenderType>> observable = std::shared_ptr<Observable<_SenderType>>{
        new Observable<_SenderType>([&] {
            for (int i = 0; i < value.size(); i++) {
                observable->onNext(value[i]);
            }
            for (int i = 0; i < value.size(); i++) {
                observable->onCompleted();
            }
        })
    };
    
    return observable;
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::combineLatest(std::vector<PartialValueObserverPtrFactory<_SenderType>> blargs) -> std::shared_ptr<jrx::operators::CombineLatest<_SenderType>> {
    
    std::vector<std::shared_ptr<PartialValueHolder<_SenderType>>> blargsPtrs;
    
    for (auto blarg : blargs)
    {
        blargsPtrs.push_back(blarg.ptr);
    }
    
    std::shared_ptr<CombineLatest<_SenderType>> observable = std::shared_ptr<CombineLatest<_SenderType>>{
        new CombineLatest<_SenderType>(blargsPtrs)
    };

    return observable;
}

template <class _SenderType, class _ChildrenType> Observable<_SenderType, _ChildrenType>::Observable(value_retriever_t converter) {
    this->m_pOnSubscribeRoot = nullptr;
    this->m_pConverted = converter;
}

template <class _SenderType, class _ChildrenType> Observable<_SenderType, _ChildrenType>::Observable() {
    this->m_pOnSubscribeRoot = nullptr;
    this->m_pConverted = [](_SenderType &sender) -> _ChildrenType & {
        return sender;
    };
}

template <class _SenderType, class _ChildrenType> Observable<_SenderType, _ChildrenType>::Observable(std::function<void(void)> _pOnSubscribe) {
    this->m_pOnSubscribeRoot = _pOnSubscribe;
    this->m_pConverted = [](_SenderType &sender) -> _ChildrenType & {
        return sender;
    };
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::subscribe(std::function<void(_ChildrenType &)> _pFunc) -> void {
    this->m_vSubscribersOnNext.push_back(_pFunc);
    this->start();
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::onStart() -> void {
    this->m_pOnSubscribeRoot();
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::filter(std::function<bool(_ChildrenType &)> _pPreducate) -> std::shared_ptr<Observable<_SenderType>> {
    
    auto ptr = std::shared_ptr<Observable<_SenderType>>{
        new Filter<_SenderType, _ChildrenType>{
            _pPreducate
        }
    };
    
    auto convertedPtr = std::static_pointer_cast<::TypedSubscriber<_SenderType>>(ptr);
    m_vChildren.push_back(convertedPtr);

    m_vChildren.back()->m_pOnSubscribeRoot = this->m_pOnSubscribeRoot;
    
    return ptr;
}

template <class _SenderType, class _ChildrenType>
template <class _NewChildType>
auto Observable<_SenderType, _ChildrenType>::map(std::function<_NewChildType(_SenderType &)> _pFilter) -> std::shared_ptr<Observable<_SenderType, _NewChildType>> {
    
    std::shared_ptr<Observable<_ChildrenType, _NewChildType>> ptr {
        new Map<_ChildrenType, _NewChildType>{
            _pFilter
        }
    };
    
    m_vChildren.push_back(ptr);
    ptr->m_pOnSubscribeRoot = this->m_pOnSubscribeRoot;
    return ptr;
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::on(std::function<void(_SenderType &)> _pFilter) -> std::shared_ptr<Observable<_SenderType, _ChildrenType>> {

    std::shared_ptr<Observable<_SenderType, _ChildrenType>> ptr {
        new Do<_SenderType, _ChildrenType>{
            _pFilter
        }
    };

    m_vChildren.push_back(ptr);
    ptr->m_pOnSubscribeRoot = this->m_pOnSubscribeRoot;
    return ptr;
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::onNext(_SenderType &value) -> void {
    auto val = m_pConverted(value);
    for (int i = 0; i < m_vChildren.size(); i++) {
        m_vChildren[i]->onNext(val);
    }
    for (int i = 0; i < m_vSubscribersOnNext.size(); i++) {
        m_vSubscribersOnNext[i](val);
    }

    this->onValuePosted();
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::onCompleted() -> void {
    
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::onError() -> void {
    
}


