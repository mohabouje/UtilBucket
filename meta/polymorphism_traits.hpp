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

 * File: polymorphism_traits.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_POLYMORPHISM_TRAITS_HPP
#define UTILBUCKET_POLYMORPHISM_TRAITS_HPP

#include <iterator>
#include <type_traits>

namespace util { namespace meta {
    template <typename Base, typename Derive>
    using is_derived = std::is_base_of<Base, Derive>;

    template <typename Base, typename Derived>
    constexpr bool is_derived_v = is_derived<Base, Derived>::value;

}} // namespace util::meta

#endif //UTILBUCKET_POLYMORPHISM_TRAITS_HPP
