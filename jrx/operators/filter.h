//
//  jorx_operator_where.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_operator_where_hpp
#define jorx_operator_where_hpp

template <class _Ty>
class jrx::operators::Filter
    : public jrx::subjects::ReplaySubject<_Ty> {
public:
    
    Filter(Observable<_Ty> *_pParent, std::function<bool(_Ty &)> _pPreducate);
    
private:
    
    std::function<bool(_Ty &)> m_pPreducate;
};


#endif /* jorx_operator_where_hpp */
