// Auto-generated: includes all birds
#include <unordered_map>
#include <memory>

#include "IBird.h"
#include "Birds/Bodine.h"
#include "Birds/Default.h"
#include "Birds/Robin.h"

class BirdRegistry
{
    static std::shared_ptr<Bodine> get_BODINE()
    {
        ensureInitialized();

        auto it = m_list.find("bodine");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Bodine>(it->second);
        return nullptr;
    }

    static std::shared_ptr<Default> get_DEFAULT()
    {
        ensureInitialized();

        auto it = m_list.find("default");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Default>(it->second);
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
        m_list["bodine"] = std::make_shared<Bodine>();
        m_list["default"] = std::make_shared<Default>();
        m_list["robin"] = std::make_shared<Robin>();

        m_isInitialized = true;
    };

    static inline bool m_isInitialized = false;
    static std::unordered_map<std::string, std::shared_ptr<IBird>> m_list;
};