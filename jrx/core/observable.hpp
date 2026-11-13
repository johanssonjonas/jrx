//
//  jorx_observable.cpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class _SenderType> auto Observable<_SenderType>
::just(_SenderType value) -> RetainedPtr<Observable<_SenderType>> {
    // TODO: this one should use a take(1) once that operator is implemented
    return BehaviorSubject<_SenderType>::seeded(value);
}

template <class _SenderType> auto Observable<_SenderType>
::forEach(std::initializer_list<_SenderType> _lstValues) -> observable_ptr_t<_SenderType> {
    
    std::vector<ObservablePtr<_SenderType>> values;
    
    for (auto value : _lstValues) {
        values.push_back(jrx::core::Observable<_SenderType>::just(value));
    }
    
    return Observable<_SenderType>::merge(values);
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
::merge(std::vector<jrx::core::ObservablePtr<_SenderType>> input) -> ObservablePtr<_SenderType> {
    
    auto obj = new Merge<_SenderType>(input);
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    
    return ptr;
}

template <class _SenderType> auto Observable<_SenderType>
::merge(std::initializer_list<jrx::core::ObservablePtr<_SenderType>> input) -> ObservablePtr<_SenderType> {
    
    auto obj = new Merge<_SenderType>(input);
    auto ptr = obj->template getPtr<Observable<_SenderType>>();
    
    return ptr;
}

template <class _SenderType> template <class _NewType> auto Observable<_SenderType>
::addChild(Observable<_NewType> *_pChild) -> observable_ptr_t<_NewType> {
    auto ptr = _pChild->template getPtr<Observable<_NewType>>();
    
    ptr->setParent(this);
    
    this->m_vChildren.push_back(_pChild->template getPtr<UntypedSubscriber>());
    
    return ptr;
}

template <class _SenderType> auto Observable<_SenderType>
::filter(std::function<bool(_SenderType &)> _pPreducate) -> observable_ptr_t<_SenderType> {
    return addChild(new jrx::operators::Filter<_SenderType> (
        this, _pPreducate
    ));
}

template <class _SenderType> template <class _NewChildType> auto jrx::core::Observable<_SenderType>
::map(func_t<_NewChildType(_SenderType)> _pFilter) -> observable_ptr_t<_NewChildType> {
    return addChild<_NewChildType>(new jrx::operators::Map<_NewChildType, _SenderType> (
        this, _pFilter
    ));
}
