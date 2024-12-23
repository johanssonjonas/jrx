//
//  jrx_partial_value_observer_ptr_factory.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-27.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class Result>
template <class Combined, class Y> jrx::factories::fragments
::PartialValueObserverPtrFactory<Result>::PartialValueObserverPtrFactory(ObservablePtr<Y> _pObservable, Y Combined::* valueSetter) {
    
    auto obj = new PartialValueObserver<Y, Combined> { _pObservable, valueSetter };
    this->ptr = obj;
    
    _pObservable->retain();
    
    this->untypedSubscriber = _pObservable.c_ptr();
    
    _pObservable->release();
    /*
    this->ptr = std::shared_ptr<PartialValueHolder<Combined>> {
        new PartialValueObserver<Y, Combined> { _pObservable, valueSetter }
    };
    this->untypedSubscriber = _pObservable->template getPtr<UntypedSubscriber>(); // .template getPtr<UntypedSubscriber>();
    */
}

template <class Result> jrx::factories::fragments::PartialValueObserverPtrFactory<Result>
::~PartialValueObserverPtrFactory() {
    // this->ptr->release();
}


