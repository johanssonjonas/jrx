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
class jrx::utils::factories::PartialValueObserverPtrFactory
{
public:
    
    template <class Combined, class Y>
    PartialValueObserverPtrFactory(std::shared_ptr<Observable<Y>> _pObservable, Y Combined::* valueSetter)
    {
        this->ptr = std::shared_ptr<PartialValueHolder<Combined>>{
            new PartialValueObserver<Y, Combined> { _pObservable, valueSetter }
        };
    }
    
    std::shared_ptr<PartialValueHolder<Result>> ptr;
};

#endif /* jrx_partial_value_observer_ptr_factory_hpp */
