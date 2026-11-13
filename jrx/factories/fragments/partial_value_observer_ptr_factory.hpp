//
//  jrx_partial_value_observer_ptr_factory.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-27.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class Result>
template <class Combined, class Y> jrx::factories::fragments::PartialValueObserverPtrFactory<Result>
::PartialValueObserverPtrFactory(ObservablePtr<Y> _pObservable, Y Combined::* valueSetter) {
    
    this->ptr = (PartialValueHolder<Result> *) new PartialValueObserver<Y, Combined> { _pObservable, valueSetter };
    this->ptr->retain();
    this->observable = _pObservable.c_ptr();
    this->untypedSubscriber = _pObservable.c_ptr();
    this->untypedSubscriber->retain();
}

template <class Result> jrx::factories::fragments::PartialValueObserverPtrFactory<Result>
::PartialValueObserverPtrFactory(const PartialValueObserverPtrFactory &_Other) {
    
    this->ptr = _Other.ptr;
    this->ptr->retain();
    this->untypedSubscriber = _Other.untypedSubscriber;
    this->untypedSubscriber->retain();
}

template <class Result> jrx::factories::fragments::PartialValueObserverPtrFactory<Result>
::~PartialValueObserverPtrFactory() {
    
    this->untypedSubscriber->release();
    this->ptr->release();
}


