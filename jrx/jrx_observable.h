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

	template<class _Ty> using func_t = std::function<_Ty>;
    template<class _Ty> using container_t = std::vector<_Ty>;
	template<class _Ty> using ptr_t = std::shared_ptr<_Ty>;
    template<class _Ty1, class _Ty2 = _Ty1> using ptr_observable_t = ptr_t<Observable<_Ty1, _Ty2>>;
    typedef func_t<void(void)> value_factory_t;
    typedef func_t<_ChildrenType(_SenderType &)> value_retriever_t;

    // creating observables
    static auto just(_ChildrenType &&value)
        -> ptr_observable_t<_SenderType>;
    static auto forEach(std::vector<_ChildrenType> &&value)
        -> ptr_observable_t<_SenderType>;

        static auto untyped(std::shared_ptr<Observable<_SenderType>> sender) -> std::shared_ptr<UntypedSubscriber> {
            return std::static_pointer_cast<UntypedSubscriber>(sender);
        }
    
    // operators
    auto filter(std::function<bool(_ChildrenType &)> _pPreducate)
        -> ptr_observable_t<_SenderType>;
    template <class _NewChildType>
        auto map(std::function<_NewChildType(_SenderType &)> _pFilter)
        	-> ptr_observable_t<_SenderType, _NewChildType>;
    
    // combining operators
//    template<class Result, typename... Arguments>
//        static auto combineLatest(ptr_observable_t<Arguments> ... params, Arguments Result:: * ... params2) -> ptr_observable_t<Result>;

//        template<class Result, typename... Arguments>
//        static auto combineLatest(std::pair<std::shared_ptr<Observable<Arguments, Arguments>>, std::function<void(Arguments, Result)>> ...params) -> ptr_observable_t<Result>;

//    template<class Result, typename... Arguments>
//        static auto combineLatest(std::vector<UntypedSubscriber>, std::vector<std::function<void(Arguments ..., Result)>>> idfj)  -> ptr_observable_t<Result>;

    // posting
    virtual auto onNext(_SenderType &value)
        -> void;
    virtual auto onCompleted()
        -> void;
    virtual auto onError()
        -> void;
    
    // subscription
    auto subscribe(func_t<void(_ChildrenType &)>) -> void;
    
protected:
    
    Observable(value_retriever_t converter);
    Observable();
    Observable(value_factory_t _pOnSubscribe);
	container_t<func_t<void(_ChildrenType &)>> m_vSubscribersOnNext;
    container_t<ptr_t<TypedSubscriber<_ChildrenType>>> m_vChildren;

private:
    std::function<_ChildrenType(_SenderType &)> m_pConverted;
};







#endif /* jorx_observable_hpp */
