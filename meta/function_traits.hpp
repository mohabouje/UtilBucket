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

 * File: function_traits.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_FUNCTION_TRAITS_HPP
#define UTILBUCKET_FUNCTION_TRAITS_HPP

#include <iterator>
#include <type_traits>
#include <tuple>
#include <functional>

namespace util { namespace meta {
    namespace {
        template <typename C, typename R, typename... A>
        struct memfn_type {
            typedef typename std::conditional<
                std::is_const<C>::value,
                typename std::conditional<std::is_volatile<C>::value, R (C::*)(A...) const volatile,
                                          R (C::*)(A...) const>::type,
                typename std::conditional<std::is_volatile<C>::value, R (C::*)(A...) volatile,
                                          R (C::*)(A...)>::type>::type type;
        };
    } // namespace

    template <typename T>
    struct function_traits : public function_traits<decltype(&T::operator())> {};

    template <typename ReturnType, typename... Args>
    struct function_traits<ReturnType(Args...)> {
        typedef ReturnType result_type;

        typedef ReturnType function_type(Args...);

        template <typename OwnerType>
        using member_function_type =
            typename memfn_type<typename std::remove_pointer<typename std::remove_reference<OwnerType>::type>::type,
                                ReturnType, Args...>::type;

        enum { arity = sizeof...(Args) };

        template <size_t i>
        struct arg {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
    };

    template <typename ReturnType, typename... Args>
    struct function_traits<ReturnType (*)(Args...)> : public function_traits<ReturnType(Args...)> {};

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...)> : public function_traits<ReturnType(Args...)> {
        typedef ClassType& owner_type;
    };

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...) const> : public function_traits<ReturnType(Args...)> {
        typedef const ClassType& owner_type;
    };

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...) volatile> : public function_traits<ReturnType(Args...)> {
        typedef volatile ClassType& owner_type;
    };

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...) const volatile>
        : public function_traits<ReturnType(Args...)> {
        typedef const volatile ClassType& owner_type;
    };

    template <typename FunctionType>
    struct function_traits<std::function<FunctionType>> : public function_traits<FunctionType> {};

}} // namespace util::meta

#endif //UTILBUCKET_FUNCTION_TRAITS_HPP
