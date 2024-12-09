//
//  jrx_operator_combine_latest.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-18.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template<class Result>
jrx::operators::CombineLatest<Result>::CombineLatest(std::vector<std::shared_ptr<PartialValueHolder<Result>>> valueObserverHolders)
: Observable<Result, Result>([this] {
    for (auto &valueObserverHolder : m_vValueObserverHolders) {
        valueObserverHolder->PartialValueHolder<Result>::m_pSharedObject = &m_Object;
        valueObserverHolder->start();
    }
}),
m_vValueObserverHolders(valueObserverHolders)
{
    for (auto &valueObserverHolder : m_vValueObserverHolders) {
        valueObserverHolder->onNextValue([this]() {
            this->onNext(m_Object);
        });
    }
}

template<class Result>
auto jrx::operators::CombineLatest<Result>::replay(std::function<void(Result &)> _pFunc) -> void {
    _pFunc(m_Object);
}
