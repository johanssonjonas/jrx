//
//  merge.hpp
//  jrx
//
//  Created by Jonas Johansson on 12/26/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template<class _SenderType> jrx::factories::Merge<_SenderType>
::Merge(std::initializer_list<jrx::core::ObservablePtr<_SenderType>> _lstObservables)
    : Merge(std::vector<jrx::core::ObservablePtr<_SenderType>>(_lstObservables))
{
    
}

template<class _SenderType> jrx::factories::Merge<_SenderType>
::Merge(std::vector<jrx::core::ObservablePtr<_SenderType>> _lstObservables)
    : jrx::subjects::ReplaySubject<_SenderType>(), m_lstObservables(_lstObservables)
{
    for (auto &valueObserverHolder : _lstObservables) {
        valueObserverHolder->setParent(this);
    }
    
    this->observeOnSubscribe([&]() {
        for (auto &valueObserverHolder : this->m_lstObservables) {
            valueObserverHolder->subscribe([this](_SenderType _tyValue) {
                this->onNext(_tyValue);
            });
        }
    });
}
