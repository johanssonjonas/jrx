//
//  jrx_partial_value_observer.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-23.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_partial_value_observer_hpp
#define jrx_partial_value_observer_hpp



template <class _Ty, class _Ty2>
class PartialValueObserver: public PartialValueHolder<_Ty2> {
public:

    PartialValueObserver(std::shared_ptr<jrx::core::Observable<_Ty, _Ty>> obs, _Ty _Ty2::* valueSetter) {
        m_pValueSetter = valueSetter;
        observable = obs;
        obs->on([this](_Ty &val){
            PartialValueHolder<_Ty2>::m_pSharedObject->*m_pValueSetter = val;
        });
        obs->onNextValue([this](){
            this->onValuePosted();
        });
    }

    virtual auto onStart() -> void override {
        observable->start();
    }

    std::shared_ptr<jrx::core::Observable<_Ty, _Ty>> observable;

protected:

//    virtual auto onValuePosted() -> void override {
//        observable->onValuePosted();
//    }

private:
    _Ty _Ty2:: *m_pValueSetter;
    //    _Ty2 *m_pSharedObject;
};


#endif /* jrx_partial_value_observer_hpp */
