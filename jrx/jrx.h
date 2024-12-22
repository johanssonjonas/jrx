//
//  jorx.hpp
//  JoRX
//
//  Created by Jonas Johansson on 2017-10-02.
//  Copyright © 2017 Jonas Johansson. All rights reserved.
//

#ifndef jorx_hpp
#define jorx_hpp

#include <iostream>
#include <vector>

namespace jrx {
    namespace core {
    
        template <class T> class RetainablePointer;
        class RetainableObject;
    
        class UntypedSubscriber;
        template <class _Ty> class TypedSubscriber;
        // template <class _Ty> class ObservablePtr;
        template <class _SenderType> class Observable;
        template <class _SenderType> class BehaviorSubject;
        template <class _SenderType> class ReplaySubject;
        template <class _SenderType> class PublishSubject;

        template<class _Func> using func_t = std::function<_Func>;
        // template<class _Ty1, class _Ty2 = _Ty1> using observable_ptr_t = ObservablePtr<Observable<_Ty1, _Ty2>>;
    
        // template<class _Ty1, class _Ty2 = _Ty1> using observable_ptr_t = RetainedPointer<Observable<_Ty1, _Ty2>>
        template<class _Ty1> using ObservablePtr = RetainablePointer<Observable<_Ty1>>;
        template<class _Ty1> using observable_ptr_t = RetainablePointer<Observable<_Ty1>>;
    }
    
    namespace operators {
        template <class _SenderType> class Map;
        template <class _SenderType> class Do;
        template<class Result> class CombineLatest;
    }
    
    namespace utils {
        namespace factories {
            template <class Result> class PartialValueObserverPtrFactory;
        }
    
        namespace memory {
            
        }
    }
}

using namespace jrx;
using namespace jrx::core;
using namespace jrx::operators;
using namespace jrx::utils;
using namespace jrx::utils::factories;
using namespace jrx::utils::memory;


using ObservableDisposer = RetainablePointer<UntypedSubscriber>;



// TODO: move to separate file
/*
class ObservableDisposer {
public:
    std::shared_ptr<UntypedSubscriber> m_pSubscriber;
    
    // Copy constructor
    ObservableDisposer(const ObservableDisposer &other) {
        m_pSubscriber = other.m_pSubscriber;
    }
    
    ObservableDisposer(UntypedSubscriber *subscriber) {
        m_pSubscriber = std::shared_ptr<UntypedSubscriber>(subscriber);
    }
    
    ~ObservableDisposer() {
        std::cout << "Disposing subscriber\n";
    }
};*/

#include "jrx_observable_ptr.h"

#include "jrx_untyped_subscriber.h"
#include "jrx_typed_subscriber.h"
#include "jrx_partial_value_holder.h"
#include "jrx_partial_value_observer.h"

#include "core/observable.h"
#include "jrx_behavior_subject.h"
#include "jrx_publish_subject.h"
#include "jrx_replay_subject.h"
#include "jrx_operator_filter.h"
#include "jrx_operator_map.h"
#include "jrx_operator_do.h"
#include "jrx_partial_value_observer_ptr_factory.h"
#include "jrx_operator_combine_latest.h"

#include "jrx_partial_value_observer.hpp"
#include "jrx_operator_combine_latest.hpp"
#include "jrx_partial_value_holder.hpp"
#include "jrx_typed_subscriber.hpp"
#include "core/observable.hpp"
#include "jrx_behavior_subject.hpp"
#include "jrx_publish_subject.hpp"
#include "jrx_replay_subject.hpp"
#include "jrx_operator_filter.hpp"
#include "jrx_operator_map.hpp"
#include "jrx_operator_do.hpp"
#include "jrx_partial_value_observer_ptr_factory.hpp"


#endif /* jorx_hpp */
