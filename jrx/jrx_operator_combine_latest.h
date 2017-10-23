//
//  jrx_operator_combine_latest.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-18.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_operator_combine_latest_hpp
#define jrx_operator_combine_latest_hpp


template <class _Ty>
class TypedPartialValueObserver : public UntypedSubscriber {
public:

    _Ty *m_pSharedObject;

    TypedPartialValueObserver() {
        m_pSharedObject = nullptr;
    }
};

template <class _Ty, class _Ty2>
class PartialValueObserver: public TypedPartialValueObserver<_Ty2> {
public:

    PartialValueObserver(std::shared_ptr<Observable<_Ty>> obs, _Ty _Ty2::* valueSetter) {
        m_pValueSetter = valueSetter;
        obs->subscribe([this](_Ty &val){
            TypedPartialValueObserver<_Ty2>::m_pSharedObject->*m_pValueSetter = val;
        });
    }

private:
    _Ty _Ty2:: *m_pValueSetter;
//    _Ty2 *m_pSharedObject;
};





template<class Result>
class CombineLatest : public jrx::core::Observable<Result, Result> {
public:

    CombineLatest(std::vector<TypedPartialValueObserver<Result>> blargs) : m_vBlarghs(blargs)
    {
        for (auto &blarg : m_vBlarghs) {
            blarg.TypedPartialValueObserver<Result>::m_pSharedObject = &m_Object;
        }
    }

    auto onNext(Result &value) -> void override {
        
    }
    
private:

    Result m_Object;
    std::vector<TypedPartialValueObserver<Result>> m_vBlarghs;
};

#endif /* jrx_operator_combine_latest_hpp */
