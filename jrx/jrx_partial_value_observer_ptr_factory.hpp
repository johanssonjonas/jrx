//
//  jrx_partial_value_observer_ptr_factory.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-27.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template <class Result>
template <class Combined, class Y>
PartialValueObserverPtrFactory<Result>::PartialValueObserverPtrFactory(std::shared_ptr<Observable<Y>> _pObservable, Y Combined::* valueSetter)
{
    this->ptr = std::shared_ptr<PartialValueHolder<Combined>>{
        new PartialValueObserver<Y, Combined> { _pObservable, valueSetter }
    };
}



