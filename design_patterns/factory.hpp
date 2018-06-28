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

 * File: factory.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_FACTORY_HPP
#define UTILBUCKET_FACTORY_HPP

#include "../meta/function_traits.hpp"
#include "../meta/polymorphism_traits.hpp"

#include <unordered_map>
#include <type_traits>
#include <typeindex>
#include <functional>
#include <memory>

namespace util { namespace dp {

    template <class AbstractProduct, typename ProductKey = std::type_index,
              typename ProductCreator    = std::function<AbstractProduct*(void)>,
              typename ProductDestructor = std::default_delete<AbstractProduct>>
    class Factory {
        static_assert(meta::is_derived_v<AbstractProduct, typename meta::function_traits<ProductCreator>::result_type>,
                      "Functor must return an abstract product pointer");

    public:
        using value_type = AbstractProduct;
        using key_type   = ProductKey;
        using deleter    = ProductDestructor;
        using unique_ptr = std::unique_ptr<AbstractProduct, ProductDestructor>;

        Factory()  = default;
        ~Factory() = default;

        template <class... Arguments>
        std::unique_ptr<AbstractProduct> createObject(ProductKey const&, Arguments...) const;

        bool registerObject(ProductKey const&, ProductCreator);
        bool unregisterObject(ProductKey const&);

    private:
        std::unordered_map<ProductKey, ProductCreator> associations_{};
    };

    template <class AbstractProduct, typename ProductKey, typename ProductConstructor, typename ProductDestructor>
    bool Factory<AbstractProduct, ProductKey, ProductConstructor, ProductDestructor>::registerObject(
        const ProductKey& key, ProductConstructor constructor) {
        const auto iter      = associations_.find(key);
        const auto not_found = (iter == std::end(associations_.end()));
        if (not_found) {
            associations_.insert(std::make_pair(key, constructor));
        }
        return not_found;
    }

    template <class AbstractProduct, typename ProductKey, typename ProductConstructor, typename ProductDestructor>
    bool Factory<AbstractProduct, ProductKey, ProductConstructor, ProductDestructor>::unregisterObject(
        const ProductKey& key) {
        const auto iter  = associations_.find(key);
        const auto found = (iter != std::end(associations_));
        if (found) {
            associations_.erase(iter);
        }
        return found;
    }

    template <class AbstractProduct, typename ProductKey, typename ProductConstructor, typename ProductDestructor>
    template <class... Arguments>
    std::unique_ptr<AbstractProduct>
        Factory<AbstractProduct, ProductKey, ProductConstructor, ProductDestructor>::createObject(
            const ProductKey& key, Arguments... arguments) const {
        const auto iter  = associations_.find(key);
        const auto found = (iter != associations_.end());
        if (!found) {
            throw std::runtime_error("Key is not registered");
        }
        return iter->second(arguments...);
    }
}} // namespace util::dp

#endif //UTILBUCKET_FACTORY_HPP
