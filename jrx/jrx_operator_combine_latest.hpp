//
//  jrx_operator_combine_latest.cpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-18.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

template<class Result> jrx::operators::CombineLatest<Result>
::CombineLatest(std::vector<PartialValueObserverPtrFactory<Result>> _vInput)
    : jrx::core::ReplaySubject<Result>(), m_vCounter(_vInput.size(), 0)
{
    for (auto &valueObserverHolder : _vInput) {
        valueObserverHolder.ptr->m_pSharedObject = &m_Object;
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
    
    /*
    for (auto &valueObserverHolder : m_vValueObserverHolders) {
        valueObserverHolder->onNextValue([this]() {
            this->onNext(m_Object);
        });
        valueObserverHolder->PartialValueHolder<Result>::m_pSharedObject = &m_Object;
    }
    
    for (auto &valueObserverHolder : valueObserverHolders) {
        valueObserverHolder->observeOnStart([]() {
            
        });
        
        valueObserverHolder->observeOnSubscribe([this]() {
            std::cout << "Hmm";
            this->onNext(m_Object);
        });
        
        valueObserverHolder->observeOnCompleted([]() {
                    
        });
        
        valueObserverHolder->observeOnError([]() {
                        
        });
        
        valueObserverHolder->observeOnNextValue([this]() {
            std::cout << "Hmm";
            this->onNext(m_Object);
        });
        
        valueObserverHolder->onSubscribe();
    }*/
    
    // Whenever someone subscribes to this observable we want to post the current value using this->onNext
}

/*
template<class Result>
auto jrx::operators::CombineLatest<Result>::subscribe(std::function<void(Result &)> _fpObserver) -> void {
    
    for (auto &valueObserverHolder : m_vValueObserverHolders) {
        valueObserverHolder->PartialValueHolder<Result>::m_pSharedObject = &m_Object;
        valueObserverHolder->observeOnNextValue([this]() {
            this->onNext(m_Object);
        });
        valueObserverHolder->onSubscribe();
    }
    
    _fpObserver(m_Object);
}

template<class Result> auto jrx::operators::CombineLatest<Result>
::onNext(Result _tyValue) -> void {
    
}
 

template<class Result>
auto jrx::operators::CombineLatest<Result>::replay(std::function<void(Result &)> _pFunc) -> void {
    _pFunc(m_Object);
}
 */


