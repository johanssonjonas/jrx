//
//  jrx_operator_combine_latest.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-18.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template<class Result> jrx::factories::CombineLatest<Result>
::CombineLatest(std::vector<jrx::factories::fragments::PartialValueObserverPtrFactory<Result>> _vInput)
    : jrx::subjects::ReplaySubject<Result>(), m_vCounter(_vInput.size(), 0)
{
    for (auto &valueObserverHolder : _vInput) {
        valueObserverHolder.ptr->setSharedObject(&m_Object);
    }
    
    this->observeOnSubscribe([this, _vInput]() {
        int counter = 0;
        for (auto &valueObserverHolder : _vInput) {
            int index = counter;
            valueObserverHolder.ptr->onSubscribe();
            valueObserverHolder.untypedSubscriber->observeOnPreviousOrNextValue([this, index]() {
                if (m_vCounter[index] == 0) {
                    m_vCounter[index] = 1;
                    m_iReadyCount++;
                }
                
                if (m_iReadyCount == m_vCounter.size()) {
                    this->onNext(m_Object);
                }
            });
            counter++;
        }
    });
}
