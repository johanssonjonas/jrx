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
        class UntypedSubscriber;
        template <class _Ty> class TypedSubscriber;
        template <class _SenderType, class _ChildrenType> class Observable;
    }
    
    namespace operators {
        template <class _SenderType, class _NewChildType> class Map;
        template <class _SenderType, class _NewChildType> class Do;
        template<class Result> class CombineLatest;
    }
    
    namespace utils {
        namespace factories {
            template <class Result> class PartialValueObserverPtrFactory;
        }
    }
}

using namespace jrx;
using namespace jrx::core;
using namespace jrx::operators;
using namespace jrx::utils;
using namespace jrx::utils::factories;


#include "jrx_untyped_subscriber.h"
#include "jrx_typed_subscriber.h"
#include "jrx_partial_value_holder.h"
#include "jrx_partial_value_observer.h"

#include "jrx_observable.h"
#include "jrx_operator_filter.h"
#include "jrx_operator_map.h"
#include "jrx_operator_do.h"
#include "jrx_partial_value_observer_ptr_factory.h"
#include "jrx_operator_combine_latest.h"

#include "jrx_partial_value_observer.hpp"
#include "jrx_operator_combine_latest.hpp"
#include "jrx_partial_value_holder.hpp"
#include "jrx_observable.hpp"
#include "jrx_operator_filter.hpp"
#include "jrx_operator_map.hpp"
#include "jrx_operator_do.hpp"
#include "jrx_partial_value_observer_ptr_factory.hpp"


#endif /* jorx_hpp */
