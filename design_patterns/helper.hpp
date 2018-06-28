/* 
 * UtilBucket, just another repository with a bunch of utilities written in modern C++.
 * Copyright (c) 2018  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

 * File: helper.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_DESSING_PATTERS_HELPER_HPP
#define UTILBUCKET_DESSING_PATTERS_HELPER_HPP

#include "../meta/polymorphism_traits.hpp"

namespace util { namespace dp {
    template <typename T, class... Arguments>
    struct default_constructor {
        inline T* operator()(Arguments... arguments) const {
            return new T(arguments...);
        }
    };

    template <class Base, class Derived, class... Arguments>
    struct base_constructor {
        inline Base* operator()(Arguments... arguments) const {
            static_assert(meta::is_derived_v<Base, Derived>, "The derived class does not extend from base class.");
            return default_constructor<Derived, Arguments...>()(arguments...);
        }
    };
}} // namespace util::dp

#endif //UTILBUCKET_DESSING_PATTERS_HELPER_HPP
