//
//  jorx_observable.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_observable_hpp
#define jorx_observable_hpp







template <class _SenderType, class _ChildrenType = _SenderType>
class jrx::core::Observable
	: public jrx::core::TypedSubscriber<_SenderType> {
public:
        
    virtual ~Observable() { }

	// template<class _Ty> using func_t = std::function<_Ty>;
    template<class _Ty> using container_t = std::vector<_Ty>;
	template<class _Ty> using ptr_t = std::shared_ptr<_Ty>;
    typedef func_t<void(void)> value_factory_t;
    typedef func_t<_ChildrenType(_SenderType &)> value_retriever_t;

    // creating observables
    static auto just(_ChildrenType &&value)
        -> observable_ptr_t<_SenderType>;
    static auto forEach(std::vector<_ChildrenType> &&value)
        -> observable_ptr_t<_SenderType>;

    // merging
	static auto combineLatest(std::vector<PartialValueObserverPtrFactory<_SenderType>> input) -> std::shared_ptr<jrx::operators::CombineLatest<_SenderType>>;

    // operators
    auto filter(std::function<bool(_ChildrenType &)> _pPreducate)
        -> observable_ptr_t<_SenderType>;
    template <class _NewChildType> auto map(func_t<_NewChildType(_SenderType)> _pFilter) -> observable_ptr_t<_NewChildType>;
    // auto on(std::function<void(_SenderType &)> _pFilter)
    //         -> observable_ptr_t<_SenderType, _ChildrenType>;

    // subscription
    // virtual auto subscribe(func_t<void(_ChildrenType &)>) -> void;
    
protected:
    
    Observable(value_retriever_t converter);
    Observable();
    // Observable(value_factory_t _pOnSubscribe);
    // std::vector<std::function<void(_ChildrenType &)>> m_vOnNextObserversValue;

    virtual auto replay(func_t<void(_ChildrenType &)>) -> void;

private:
    std::function<_ChildrenType(_SenderType &)> m_pConverted;
};







#endif /* jorx_observable_hpp */
