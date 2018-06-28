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

 * File: abstract_factory.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_ABSTRACT_FACTORY_HPP
#define UTILBUCKET_ABSTRACT_FACTORY_HPP

#include "factory.hpp"

namespace util { namespace dp {

    template <class AbstractProduct, typename FactoryKey, class Factory = Factory<AbstractProduct>>
    class AbstractFactory {
        static_assert(meta::is_derived_v<AbstractProduct, typename Factory::value_type>,
                      "Factory does not generated a derived class from AbstractProduct");

    public:
        AbstractFactory()  = default;
        ~AbstractFactory() = default;

        using value_type = AbstractProduct;
        using key_type   = FactoryKey;
        using deleter    = std::default_delete<AbstractProduct>;
        using unique_ptr = std::unique_ptr<AbstractProduct, deleter>;

        template <class... Arguments>
        std::unique_ptr<AbstractProduct> createObject(const key_type& factory_key,
                                                      const typename Factory::key_type& product_key,
                                                      Arguments... arguments);

        bool registerFactory(const key_type& factory_key, const Factory& factory);
        bool unregisterFactory(const key_type& factory_key);

    private:
        std::unordered_map<FactoryKey, Factory> associations_{};
    };

    template <class AbstractProduct, typename FactoryKey, typename Factory>
    template <class... Arguments>
    std::unique_ptr<AbstractProduct> AbstractFactory<AbstractProduct, FactoryKey, Factory>::createObject(
        const key_type& factory_key, const typename Factory::key_type& product_key, Arguments... arguments) {
        const auto iter  = associations_.find(factory_key);
        const auto found = (iter != associations_.end());
        if (!found) {
            throw std::runtime_error("Key is not registered");
        }
        const auto& factory = iter->second;
        return found ? factory.createObject(product_key, arguments...) : nullptr;
    }

    template <class AbstractProduct, typename FactoryKey, typename Factory>
    bool AbstractFactory<AbstractProduct, FactoryKey, Factory>::registerFactory(const key_type& factory_key,
                                                                                const Factory& factory) {
        const auto iter      = associations_.find(factory_key);
        const auto not_found = (iter == std::end(associations_));
        if (not_found) {
            associations_.insert(std::make_pair(factory_key, factory));
        }
        return not_found;
    }

    template <class AbstractProduct, typename FactoryKey, typename Factory>
    bool AbstractFactory<AbstractProduct, FactoryKey, Factory>::unregisterFactory(const key_type& factory_key) {
        const auto iter  = associations_.find(factory_key);
        const auto found = (iter != std::end(associations_));
        if (found) {
            associations_.erase(factory_key);
        }
        return found;
    }
}} // namespace util::dp

#endif //UTILBUCKET_ABSTRACT_FACTORY_HPP
