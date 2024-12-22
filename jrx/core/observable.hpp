//
//  jorx_observable.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _SenderType>
auto Observable<_SenderType>::just(_SenderType &&value) -> RetainablePointer<Observable<_SenderType>> {
    /*
    std::shared_ptr<Observable<_SenderType>> observable = std::shared_ptr<Observable<_SenderType>> {
        new Observable<_SenderType>([&] {
            _ChildrenType hurp = value;
            observable->onNext(hurp);
        })
    };
    return observable;
    */

    // TODO: this one should use a take(1) once that operator is implemented
    return std::static_pointer_cast<Observable<_SenderType>>(BehaviorSubject<_SenderType>::seeded(value));
}

template <class _SenderType>
auto Observable<_SenderType>::forEach(std::vector<_SenderType> &&value) -> observable_ptr_t<_SenderType> {
    ObservablePtr<Observable<_SenderType>> observable = std::shared_ptr<Observable<_SenderType>> {
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

template <class _SenderType> Observable<_SenderType>::Observable() {
    
}

/*
template <class _SenderType> Observable<_SenderType>::Observable(value_retriever_t converter) {
    this->m_pConverted = converter;
}*/

/*
template <class _SenderType> Observable<_SenderType>::Observable() {
    this->m_pConverted = [](_SenderType &sender) -> _SenderType & {
        return sender;
    };
}*/

/*
template <class _SenderType, class _ChildrenType> Observable<_SenderType, _ChildrenType>::Observable(std::function<void(void)> _pOnSubscribe) {
    this->m_pOnSubscribeRoot = _pOnSubscribe;
    this->m_pConverted = [](_SenderType &sender) -> _ChildrenType & {
        return sender;
    };
}

template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::subscribe(std::function<void(_ChildrenType &)> _pFunc) -> void {
    this->m_vOnNextObserversValue.push_back(_pFunc);
    this->onSubscribe();
    this->onNextValue();
}*/

template <class _SenderType>
auto Observable<_SenderType>::replay(std::function<void(_SenderType &)> _pFunc) -> void {
    
}

template <class _SenderType> auto Observable<_SenderType>
::combineLatest(std::vector<PartialValueObserverPtrFactory<_SenderType>> input) -> ObservablePtr<_SenderType> {
    
    auto obj = new CombineLatest<_SenderType>(input);
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    
    return ptr;
}

template <class _SenderType>
auto Observable<_SenderType>::filter(std::function<bool(_SenderType &)> _pPreducate) -> observable_ptr_t<_SenderType> {
    
    auto obj = new PublishSubject<_SenderType>();
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    
    ptr->m_pParent = this;
    
    this->m_vChildren.push_back(obj->template getPtr<UntypedSubscriber>());
    this->observeOnNextValue([=](auto value) {
        if (_pPreducate(value)) {
            obj->onNext(value);
        }
    });
    
    return ptr;
}

template <class _SenderType> template <class _NewChildType> auto jrx::core::Observable<_SenderType>
::map(func_t<_NewChildType(_SenderType)> _pFilter) -> observable_ptr_t<_NewChildType> {
    
    auto obj = new PublishSubject<_NewChildType>();
    auto ptr = obj->template getPtr<Observable<_NewChildType>>();
    
    ptr->m_pParent = this;
    
    this->m_vChildren.push_back(obj->template getPtr<UntypedSubscriber>());
    this->observeOnNextValue([=](auto value) {
        obj->onNext(_pFilter(value));
    });
    
    return ptr;
}


/*
template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::on(std::function<void(_SenderType &)> _pFilter) -> ObservablePtr<Observable<_SenderType, _ChildrenType>> {

    std::shared_ptr<Observable<_SenderType, _ChildrenType>> ptr {
        new Do<_SenderType, _ChildrenType>{
            _pFilter
        }
    };

    m_vChildren.push_back(ptr);
    return ptr;
}*/

/*
template <class _SenderType, class _ChildrenType>
auto Observable<_SenderType, _ChildrenType>::onNext(_SenderType &value) -> void {
    auto val = m_pConverted(value);
    for (int i = 0; i < m_vChildren.size(); i++) {
        m_vChildren[i]->onNext(val);
    }
    for (int i = 0; i < m_vOnNextObserversValue.size(); i++) {
        m_vOnNextObserversValue[i](val);
    }

    this->onNextValue();
}*/
