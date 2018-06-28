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
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * File: iterator_traits.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_ITERATOR_TRAITS_HPP
#define UTILBUCKET_ITERATOR_TRAITS_HPP

#include <iterator>
#include <type_traits>

namespace util { namespace meta {

    template <typename T>
    struct is_iterator {
        static char test(...);

        template <typename U, typename = typename std::iterator_traits<U>::difference_type,
                  typename = typename std::iterator_traits<U>::pointer,
                  typename = typename std::iterator_traits<U>::reference,
                  typename = typename std::iterator_traits<U>::value_type,
                  typename = typename std::iterator_traits<U>::iterator_category>
        static long test(U&&);

        constexpr static bool value = std::is_same<decltype(test(std::declval<T>())), long>::value;
    };

    template <typename T>
    constexpr bool is_iterator_v = is_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_input_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::input_iterator_tag>;
    template <typename T>

    constexpr bool is_input_iterator_v = is_input_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_output_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::output_iterator_tag>;
    template <typename T>

    constexpr bool is_output_iterator_v = is_output_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_forward_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::forward_iterator_tag>;
    template <typename T>

    constexpr bool is_forward_iterator_v = is_forward_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_bidirectional_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::bidirectional_iterator_tag>;
    template <typename T>

    constexpr bool is_bidirectional_iterator_v = is_bidirectional_iterator<T>::value;

    template <typename T, typename = typename std::enable_if<is_iterator<T>::value>::type>
    using is_random_access_iterator =
        std::is_same<typename std::iterator_traits<T>::iterator_category, std::random_access_iterator_tag>;
    template <typename T>

    constexpr bool is_random_access_iterator_v = is_random_access_iterator<T>::value;
}} // namespace util::meta

#endif //UTILBUCKET_ITERATOR_TRAITS_HPP
