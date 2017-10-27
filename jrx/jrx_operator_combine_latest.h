//
//  jrx_operator_combine_latest.hpp
//  jrx
//
//  Created by Jonas Johansson on 2017-10-18.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jrx_operator_combine_latest_hpp
#define jrx_operator_combine_latest_hpp







template<class Result>
class jrx::operators::CombineLatest : public jrx::core::Observable<Result, Result> {
public:

    CombineLatest(std::vector<std::shared_ptr<PartialValueHolder<Result>>> blargs) :
    	Observable<Result, Result>([this]{
            for (auto &blargh : m_vBlarghs) {
                blargh->start();
            }
    	}),
    	m_vBlarghs(blargs)
    {
        for (auto &blarg : m_vBlarghs) {
            blarg->PartialValueHolder<Result>::m_pSharedObject = &m_Object;
            blarg->onNextValue([this](){
                this->onNext(m_Object);
            });
        }
    }

//    auto onNext(Result &value) -> void override {
//
//    }

protected:

private:

    Result m_Object;
    std::vector<std::shared_ptr<PartialValueHolder<Result>>> m_vBlarghs;
};

#endif /* jrx_operator_combine_latest_hpp */
