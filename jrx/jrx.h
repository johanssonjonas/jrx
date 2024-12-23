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
#include <cassert>

namespace jrx {
    namespace core {
        class UntypedSubscriber;
        class RetainedObject;

        template <class T> class RetainedPtr;
        template <class _Ty> class TypedSubscriber;
        template <class _SenderType> class Observable;
        
        template<class _Func> using func_t = std::function<_Func>;
        template<class _Ty1> using observable_ptr_t = RetainedPtr<Observable<_Ty1>>;
        
        template<class _Ty1> using ObservablePtr = RetainedPtr<Observable<_Ty1>>;
        using ObservableDisposer = RetainedPtr<UntypedSubscriber>;
    }

    namespace config {
        static bool automaticMemoryManagement = true;
    }

    namespace subjects {
        template <class _SenderType> class BehaviorSubject;
        template <class _SenderType> class ReplaySubject;
        template <class _SenderType> class PublishSubject;
    }

    namespace factories {
        namespace fragments {
            template <class Result> class PartialValueObserverPtrFactory;
            template <class _Ty> class PartialValueHolder;
            template <class _Ty, class _Ty2> class PartialValueObserver;
        }
        template<class Result> class CombineLatest;
    }
    
    namespace operators {
        template <class _SenderType> class Map;
        template <class _SenderType> class Do;
    }
}

using namespace jrx;
using namespace jrx::core;
using namespace jrx::operators;
using namespace jrx::subjects;
using namespace jrx::factories;

#include "core/retained_ptr.h"
#include "core/retained_object.h"
#include "core/observable.h"
#include "core/observable.hpp"
#include "core/untyped_subscriber.h"
#include "core/typed_subscriber.h"
#include "core/typed_subscriber.hpp"
#include "subjects/behavior_subject.h"
#include "subjects/behavior_subject.hpp"
#include "subjects/publish_subject.h"
#include "subjects/publish_subject.hpp"
#include "subjects/replay_subject.h"
#include "subjects/replay_subject.hpp"
#include "operators/filter.h"
#include "operators/filter.hpp"
#include "operators/map.h"
#include "operators/map.hpp"
#include "factories/fragments/partial_value_holder.h"
#include "factories/fragments/partial_value_holder.hpp"
#include "factories/fragments/partial_value_observer.h"
#include "factories/fragments/partial_value_observer.hpp"
#include "factories/fragments/partial_value_observer_ptr_factory.h"
#include "factories/fragments/partial_value_observer_ptr_factory.hpp"
#include "factories/combine_latest.h"
#include "factories/combine_latest.hpp"

#endif /* jorx_hpp */
