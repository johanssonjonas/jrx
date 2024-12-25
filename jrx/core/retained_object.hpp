//
//  retained_object_hpp.m
//  jrx
//
//  Created by Jonas Johansson on 12/22/24.
//  Copyright © 2024 Jonas Johansson. All rights reserved.
//

template <class _Ty> auto jrx::core::RetainedObject
::getPtr() -> RetainedPtr<_Ty>  {
    return RetainedPtr<_Ty>((_Ty *)this);
}
