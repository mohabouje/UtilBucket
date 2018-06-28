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

 * File: prototype.hpp
 * Created by Mohammed Boujemaoui Boulaghmoudi on 28/06/18.
 */

#ifndef UTILBUCKET_PROTOTYPE_HPP
#define UTILBUCKET_PROTOTYPE_HPP

#include <unordered_map>
#include <typeindex>
#include <memory>

namespace util { namespace dp {
    template <class AbstractProduct, typename ProductKey = std::type_index>
    class Prototype {
    public:
        using value_type = AbstractProduct;
        using key_type   = ProductKey;
        using deleter    = std::default_delete<AbstractProduct>;
        using unique_ptr = std::unique_ptr<AbstractProduct, deleter>;

        Prototype()  = default;
        ~Prototype() = default;

        std::unique_ptr<AbstractProduct> clone(const key_type& key) const;
        bool registerObject(const key_type& key, const AbstractProduct* product);
        bool unregisterObject(const key_type& key);

    private:
        std::unordered_map<ProductKey, const AbstractProduct*> associations_;
    };

    template <class AbstractProduct, typename ProductKey>
    std::unique_ptr<AbstractProduct> Prototype<AbstractProduct, ProductKey>::clone(const key_type& key) const {
        const auto iter  = associations_.find(key);
        const auto found = (iter != associations_.end());
        if (!found) {
            throw std::runtime_error("Key is not registered");
        }
        const auto* product = iter->second;
        return product->clone();
    }

    template <class AbstractProduct, typename ProductKey>
    bool Prototype<AbstractProduct, ProductKey>::registerObject(const key_type& key, const AbstractProduct* product) {
        const auto iter      = associations_.find(key);
        const auto not_found = (iter == std::end(associations_));
        if (not_found) {
            associations_.insert(std::make_pair(key, product));
        }
        return not_found;
    }

    template <class AbstractProduct, typename ProductKey>
    bool Prototype<AbstractProduct, ProductKey>::unregisterObject(const key_type& key) {
        const auto iter  = associations_.find(key);
        const auto found = (iter != std::end(associations_));
        if (found) {
            associations_.erase(key);
        }
        return found;
    }

}} // namespace util::dp

#endif //UTILBUCKET_PROTOTYPE_HPP
