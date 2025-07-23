// Auto-generated: includes all birds
#include <unordered_map>
#include <memory>

#include "IBird.h"
#include "Birds/Goose.h"
#include "Birds/RobinBlue.h"
#include "Birds/Robin.h"
#include "Birds/Capsule.h"

class BirdRegistry
{
    static std::shared_ptr<Goose> getGoose()
    {
        ensureInitialized();

        auto it = m_list.find("Goose");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Goose>(it->second);
        return nullptr;
    }

    static std::shared_ptr<RobinBlue> getRobinBlue()
    {
        ensureInitialized();

        auto it = m_list.find("RobinBlue");
        if (it != m_list.end()) return std::dynamic_pointer_cast<RobinBlue>(it->second);
        return nullptr;
    }

    static std::shared_ptr<Robin> getRobin()
    {
        ensureInitialized();

        auto it = m_list.find("Robin");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Robin>(it->second);
        return nullptr;
    }

    static std::shared_ptr<Capsule> getCapsule()
    {
        ensureInitialized();

        auto it = m_list.find("Capsule");
        if (it != m_list.end()) return std::dynamic_pointer_cast<Capsule>(it->second);
        return nullptr;
    }

    static std::shared_ptr<IBird> getInstance(const std::string& name)
    {
        ensureInitialized();

        auto it = m_list.find(name);
        if (it != m_list.end()) return it->second;
        return nullptr;
    }

    static std::vector<std::string> getAllEntries()
    {
        return m_entries;    }
private:
    static void ensureInitialized()
    {
        if(m_isInitialized) return;
        m_list["Goose"] = std::make_shared<Goose>();
        m_entries.push_back("Goose");
        m_list["RobinBlue"] = std::make_shared<RobinBlue>();
        m_entries.push_back("RobinBlue");
        m_list["Robin"] = std::make_shared<Robin>();
        m_entries.push_back("Robin");
        m_list["Capsule"] = std::make_shared<Capsule>();
        m_entries.push_back("Capsule");

        m_isInitialized = true;
    };

    static inline bool m_isInitialized = false;
    static std::unordered_map<std::string, std::shared_ptr<IBird>> m_list;
    static std::vector<std::string> m_entries;
};