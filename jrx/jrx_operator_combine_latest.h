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
class jrx::operators::CombineLatest
    : public jrx::core::ReplaySubject<Result> {
public:
	
    CombineLatest(std::vector<PartialValueObserverPtrFactory<Result>> _vInput);
    
   // override this one from Observable and when it's called, make sure to send the last value (if it has been set) to the new subscriber.
    // auto subscribe(std::function<void(Result &)>) -> void override; // TODO: should use func_t
    
    // auto onNext(Result _tyValue) -> void override;
protected:
        
    // auto replay(std::function<void(Result &)> _pFunc) -> void override;
    
private:
    Result m_Object;
    std::vector<int> m_vCounter;
    int m_iReadyCount;
    std::vector<std::shared_ptr<PartialValueHolder<Result>>> m_vValueObserverHolders;
};

#endif /* jrx_operator_combine_latest_hpp */
