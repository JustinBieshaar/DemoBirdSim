#pragma once
#include <tuple>
#include <type_traits>

namespace SimpleDI
{
    template<typename T>
    struct ConstructorTraits
    {
        using Args = std::tuple<>;
    };

    // Default empty template
    template<typename T, typename = void>
    struct has_constructor_traits : std::false_type {};

    template<typename T>
    struct has_constructor_traits<T, std::void_t<typename ConstructorTraits<T>::Args>> : std::true_type {};
}