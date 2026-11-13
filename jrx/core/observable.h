//
//  jorx_observable.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_observable_hpp
#define jorx_observable_hpp

template <class _ValueTy>
class jrx::core
    ::Observable
	: public jrx::core::TypedSubscriber<_ValueTy> {
public:
    
    virtual ~Observable() { }

	template<class _Ty> using func_t = std::function<_Ty>;
    template<class _Ty> using container_t = std::vector<_Ty>;
	// template<class _Ty> using ptr_t = std::shared_ptr<_Ty>;
    typedef func_t<void(void)> value_factory_t;
    typedef func_t<_ValueTy(_ValueTy &)> value_retriever_t;
    
    // creating observables
    static auto just(_ValueTy value) -> observable_ptr_t<_ValueTy>;
    static auto forEach(std::initializer_list<_ValueTy> _lstValues) -> observable_ptr_t<_ValueTy>;
    
    // merging
    static auto combineLatest(std::vector<jrx::factories::fragments::PartialValueObserverPtrFactory<_ValueTy>> input) -> ObservablePtr<_ValueTy>;
    static auto merge(std::vector<jrx::core::ObservablePtr<_ValueTy>> input) -> ObservablePtr<_ValueTy>;
    static auto merge(std::initializer_list<jrx::core::ObservablePtr<_ValueTy>> input) -> ObservablePtr<_ValueTy>;

    // operators
    auto filter(std::function<bool(_ValueTy &)> _pPreducate) -> observable_ptr_t<_ValueTy>;
    template <class _NewChildType> auto map(func_t<_NewChildType(_ValueTy)> _pFilter) -> observable_ptr_t<_NewChildType>;
    
protected:
        
    Observable();
        
private:
    
    template <class _NewType> auto addChild(Observable<_NewType> *_pChild) -> observable_ptr_t<_NewType>;
};







#endif /* jorx_observable_hpp */
