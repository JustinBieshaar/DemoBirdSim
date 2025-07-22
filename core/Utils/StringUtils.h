#pragma once
#include <string>
#include <string_view>

namespace StringUtils
{

    // Ps. I didn't come up with this myself, this to me, even with generated comments, still
    // looks like black magic. More back info: https://stackoverflow.com/a/20170989/3578538

    /// <summary>
    /// Template function to extract the type name at compile-time
    /// </summary>
    template <typename T>
    constexpr std::string_view type_name()
    {
#if defined(__clang__)
        // __PRETTY_FUNCTION__ looks like:
        // "std::string_view TypeName() [T = YourType]"
        // So we slice out just the type name from the full string.
        std::string_view p = __PRETTY_FUNCTION__;
        return p.substr(31, p.length() - 31 - 1); // 31 = offset to type name, -1 to remove ']'

#elif defined(__GNUC__)
        // GCC __PRETTY_FUNCTION__ looks like:
        // "constexpr std::string_view TypeName() [with T = YourType]"
        // So we start at index 49 and trim trailing ']'
        std::string_view p = __PRETTY_FUNCTION__;
        return p.substr(49, p.length() - 49 - 1);

#elif defined(_MSC_VER)
        // Example: "class std::basic_string_view<...> __cdecl type_name<YourType>(void)"
        std::string_view p = __FUNCSIG__;

        constexpr std::string_view prefix = "std::string_view __cdecl StringUtils::type_name<";
        constexpr std::string_view suffix = ">(void)";

        size_t start = p.find('<') + 1;
        size_t end = p.rfind('>');
        return p.substr(start, end - start);
#else
        // Unknown compiler: return fallback
        return "UnknownType";
#endif
    }

    template <typename T>
    constexpr std::string type_name_str()
    {
        return std::string(type_name<T>());
    }

    inline std::string cleanTypeName(const char* rawName)
    {
        std::string name = rawName;

        // Remove common prefixes
        const std::string classPrefix = "class ";
        const std::string structPrefix = "struct ";
        const std::string enumPrefix = "enum ";

        if (name.starts_with(classPrefix)) name.erase(0, classPrefix.size());
        else if (name.starts_with(structPrefix)) name.erase(0, structPrefix.size());
        else if (name.starts_with(enumPrefix)) name.erase(0, enumPrefix.size());

        return name;
    }

    template <typename T>
    std::string runtime_type_name(T& obj)
    {
        return cleanTypeName(typeid(obj).name());
    }

    template <typename T>
    std::string runtime_type_name(T* ptr)
    {
        if (!ptr) return "<null>";
        return cleanTypeName(typeid(*ptr).name());
    }

    inline std::string toPascalCase(const std::string& name)
    {
        std::string out = name;
        out[0] = std::toupper(out[0]);
        return out;
    }

    inline std::string toCamelCase(const std::string& name)
    {
        std::string out = name;
        out[0] = std::tolower(out[0]);
        return out;
    }

    inline std::string toUpperCase(const std::string& input)
    {
        std::string out = input;
        for (char& c : out)
        {
            c = std::toupper(static_cast<unsigned char>(c));
        }
        return out;
    }

    inline std::string toLowerCase(const std::string& input)
    {
        std::string out = input;
        for (char& c : out)
        {
            c = std::tolower(static_cast<unsigned char>(c));
        }
        return out;
    }

    inline std::string toUpperSnakeCase(const std::string& input)
    {
        std::string result;

        for (size_t i = 0; i < input.size(); ++i)
        {
            char c = input[i];

            // Check for transition boundaries
            if (i > 0 && std::isupper(c))
            {
                char prev = input[i - 1];
                char next = (i + 1 < input.size()) ? input[i + 1] : '\0';

                if (std::islower(prev) || (std::isupper(prev) && std::islower(next)))
                {
                    result += '_';
                }
            }

            result += std::toupper(static_cast<unsigned char>(c));
        }

        return result;
    }

    inline void trimSuffix(std::string& str, const std::string& suffix)
    {
        if (str.length() >= suffix.length() &&
            str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0)
        {
            str.erase(str.length() - suffix.length());
        }
    }
}