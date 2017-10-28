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
	
    CombineLatest(std::vector<std::shared_ptr<PartialValueHolder<Result>>> valueObserverHolders);
    
private:
    Result m_Object;
    std::vector<std::shared_ptr<PartialValueHolder<Result>>> m_vValueObserverHolders;
};

#endif /* jrx_operator_combine_latest_hpp */
