//
//  jorx_operator_where.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_operator_where_hpp
#define jorx_operator_where_hpp

template <class _Ty, class _Ty2 = _Ty>
class Filter : public jrx::core::Observable<_Ty, _Ty2> {
public:
    
    Filter(std::function<bool(_Ty &)> _pPreducate);
    
    auto onNext(_Ty &value) -> void override;
    
private:
    
    std::function<bool(_Ty &)> m_pPreducate;
};


#endif /* jorx_operator_where_hpp */
