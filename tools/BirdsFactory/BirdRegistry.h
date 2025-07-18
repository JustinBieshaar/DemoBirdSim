// Auto-generated: includes all birds
#include <unordered_map>
#include <memory>

#include "IBird.h"
#include "Birds/Goose.h"
#include "Birds/Gull.h"
#include "Birds/Robin.h"

class BirdRegistry
{
    static std::shared_ptr<Goose> get_GOOSE()
    {
        ensureInitialized();

        auto it = m_list.find("goose");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Goose>(it->second);
        return nullptr;
    }

    static std::shared_ptr<Gull> get_GULL()
    {
        ensureInitialized();

        auto it = m_list.find("gull");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Gull>(it->second);
        return nullptr;
    }

    static std::shared_ptr<Robin> get_ROBIN()
    {
        ensureInitialized();

        auto it = m_list.find("robin");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Robin>(it->second);
        return nullptr;
    }

    static std::shared_ptr<IBird> getInstance(const std::string& name)
    {
        ensureInitialized();

        auto it = m_list.find(name);
        if (it != m_list.end()) return it->second;
        return nullptr;
    }
private:
    static void ensureInitialized()
    {
        if(m_isInitialized) return;
        m_list["goose"] = std::make_shared<Goose>();
        m_list["gull"] = std::make_shared<Gull>();
        m_list["robin"] = std::make_shared<Robin>();

        m_isInitialized = true;
    };

    static inline bool m_isInitialized = false;
    static std::unordered_map<std::string, std::shared_ptr<IBird>> m_list;
};