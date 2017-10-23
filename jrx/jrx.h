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
    }
}

using namespace jrx;
using namespace jrx::core;
using namespace jrx::operators;


#include "jrx_untyped_subscriber.h"
#include "jrx_typed_subscriber.h"
#include "jrx_observable.h"
#include "jrx_operator_filter.h"
#include "jrx_operator_map.h"
#include "jrx_operator_do.h"
#include "jrx_operator_combine_latest.h"

#include "jrx_observable.hpp"
#include "jrx_operator_filter.hpp"
#include "jrx_operator_map.hpp"
#include "jrx_operator_do.hpp"


#endif /* jorx_hpp */
