//
//  jorx_observable.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _SenderType> auto Observable<_SenderType>
::just(_SenderType &&value) -> RetainedPtr<Observable<_SenderType>> {
    // TODO: this one should use a take(1) once that operator is implemented
    return BehaviorSubject<_SenderType>::seeded(value);
}

template <class _SenderType> auto Observable<_SenderType>
::forEach(std::vector<_SenderType> &&value) -> observable_ptr_t<_SenderType> {
    // TODO: test this one
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

template <class _SenderType> Observable<_SenderType>
::Observable() {
    
}

template <class _SenderType> auto Observable<_SenderType>
::combineLatest(std::vector<jrx::factories::fragments::PartialValueObserverPtrFactory<_SenderType>> input) -> ObservablePtr<_SenderType> {
    
    auto obj = new CombineLatest<_SenderType>(input);
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    
    return ptr;
}

template <class _SenderType> auto Observable<_SenderType>
::filter(std::function<bool(_SenderType &)> _pPreducate) -> observable_ptr_t<_SenderType> {
    
    auto obj = new PublishSubject<_SenderType>();
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    
    ptr->setParent(this);
    
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
    
    ptr->setParent(this);
    
    this->m_vChildren.push_back(obj->template getPtr<UntypedSubscriber>());
    this->observeOnNextValue([=](auto value) {
        obj->onNext(_pFilter(value));
    });
    
    return ptr;
}
