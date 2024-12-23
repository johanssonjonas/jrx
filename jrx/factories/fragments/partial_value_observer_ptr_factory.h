//
//  jrx_partial_value_observer_ptr_factory.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-27.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_partial_value_observer_ptr_factory_hpp
#define jrx_partial_value_observer_ptr_factory_hpp

template <class Result>
class jrx::factories::fragments::PartialValueObserverPtrFactory {
public:
    template <class Combined, class Y>
    PartialValueObserverPtrFactory(ObservablePtr<Y> _pObservable, Y Combined::* valueSetter);
    PartialValueObserverPtrFactory(const PartialValueObserverPtrFactory &_Other);
    
    ~PartialValueObserverPtrFactory();
    
    
    // std::shared_ptr<PartialValueHolder<Result>> ptr;
    PartialValueHolder<Result> *ptr;
    UntypedSubscriber *untypedSubscriber;
    UntypedSubscriber *observable;
    
private:
    // copy constructor:
};

#endif /* jrx_partial_value_observer_ptr_factory_hpp */
