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

 * File: singleton.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_SINGLETON_HPP
#define UTILBUCKET_SINGLETON_HPP

#include <stdexcept>

namespace util { namespace dp {

    template <class Type>
    class Singleton {
    public:
        using value_type = Type;

        Singleton()            = delete;
        Singleton(Singleton&&) = delete;
        Singleton(Singleton&)  = delete;
        Singleton& operator=(Singleton&) = delete;

        template <class... Arguments>
        static Type& instance(Arguments... rest);

        static bool isInitialized();
        static bool isDestroyed();

    private:
        ~Singleton();
        static Type* instance_{nullptr};
        static bool destroyed_{false};

        template <class... Arguments>
        static void create(Arguments... rest);
        static void onDeadReference();
    };

    template <class Type>
    template <class... Arguments>
    Type& Singleton<Type>::instance(Arguments... rest) {
        if (isDestroyed())
            onDeadReference();
        if (!isInitialized()) {
            create(rest...);
        }
        return *instance_;
    }

    template <class Type>
    template <class... Arguments>
    void Singleton<Type>::create(Arguments... rest) {
        static Type temporal(rest...);
        instance_ = &temporal;
    }

    template <class Type>
    Singleton<Type>::~Singleton() {
        instance_  = nullptr;
        destroyed_ = true;
    }

    template <class Type>
    void Singleton<Type>::onDeadReference() {
        throw std::runtime_error("Dead reference detected");
    }

    template <class Type>
    bool Singleton<Type>::isInitialized() {
        return (instance_ != nullptr);
    }

    template <class Type>
    bool Singleton<Type>::isDestroyed() {
        return destroyed_;
    }

}} // namespace util::dp

#endif //UTILBUCKET_SINGLETON_HPP
