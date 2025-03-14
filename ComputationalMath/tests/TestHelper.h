#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include <list>
#include <typeinfo>
#include <gtest/gtest.h>

namespace TestHelper
{
    template<typename T, typename Comparer>
    struct CollectionTally
    {
        std::list<T> missingItems;
        std::list<T> extraItems;
        Comparer comparer;

        CollectionTally() : missingItems(0), extraItems(0)
        {
            comparer = [](const T& lhs, const T& rhs) { return lhs == rhs; };
        }

        CollectionTally(std::vector<T> expectedItems, Comparer compare)
            : missingItems(0), extraItems(0)
        {
            for(auto& expected : expectedItems)
            {
                missingItems.push_back(expected);
            }
            comparer = compare;
        }

        void TryRemoveElements(const std::vector<T>& actualItems)
        {
            for(const T& actual : actualItems)
            {
                auto it = std::find_if(std::begin(missingItems), std::end(missingItems), [&actual, this](const T& value){ 
                    return this->comparer(value, actual);
                });

                if ( it != missingItems.end())
                {
                    missingItems.erase( it );
                } 
                else 
                {
                    extraItems.push_back(actual);
                }
            }
        }
    };

    template<typename T>
    concept Streamable  = requires(T t, std::ostream stream)
    {
        stream << t;
    };

    template <Streamable T>
    std::string printVariable(const T& t) 
    {
        std::stringstream stream;
        stream << t;
        return stream.str();
    }

    template <typename T>
    std::string printVariable(const T& t)
    {
        std::stringstream stream;
        stream << typeid(t).name();
        return stream.str();
    }

    template<typename T, class Comparer>
    testing::AssertionResult AreEquivalent(const std::vector<T>& actual, const std::vector<T>& expected, Comparer comparer)
    {
        CollectionTally<T, Comparer> tally(expected, comparer);
        tally.TryRemoveElements(actual);

        size_t missingItemCount = tally.missingItems.size();
        size_t extraItemCount = tally.extraItems.size();
        if (missingItemCount == 0 && extraItemCount == 0)
        {
            return testing::AssertionSuccess() << "Collections are equivalent.";
        }
        else 
        {
            testing::AssertionResult result(testing::AssertionFailure());
            if (missingItemCount > 0)
            {
                result << std::endl << "Missing items: " << tally.missingItems.size();
                for(auto& missing : tally.missingItems)
                {
                    result << printVariable(missing);
                    // result << typeid(missing).name() << ", ";
                }
            }
            if (extraItemCount > 0)
            {
                result << std::endl << "Extra items: " << tally.extraItems.size();
                for(auto& extra : tally.extraItems)
                {
                    result << printVariable(extra) << ", ";
                }
            }
            return result << std::endl;
        }
    };
}

namespace std
{
    // PrintTo need to reside in the std namespace, to pretify the GoogleTest output in case a parametric test with vectors fails
    template<typename T>
    void PrintTo(const vector<T>& vec, std::ostream* os) {
        *os << "std::vector<"<< typeid(T).name()<< ">(" << vec.size() << ")";
    }
}