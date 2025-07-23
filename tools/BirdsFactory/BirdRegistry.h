// Auto-generated: includes all birds
#include <unordered_map>
#include <memory>

#include "IBird.h"
#include "Birds/RobinBlue.h"
#include "Birds/Robin.h"
#include "Birds/Capsule.h"
#include "Birds/Goose.h"

class BirdRegistry
{
public:
    BirdRegistry() = delete;
    BirdRegistry(const BirdRegistry&) = delete;
    BirdRegistry& operator=(const BirdRegistry&) = delete;
    inline static const IBird* getInstance(const std::string& name)
    {
        ensureInitialized();

        auto it = m_list.find(name);
        if (it != m_list.end()) return it->second.get();
        return nullptr;
    }

    inline static std::vector<std::string> getAllEntries()
    {
        ensureInitialized();

        return m_entries;
    }

private:
    inline static void ensureInitialized()
    {
        if(m_isInitialized) return;
        m_list["RobinBlue"] = std::make_shared<Birds::RobinBlue>();
        m_entries.push_back("RobinBlue");
        m_list["Robin"] = std::make_shared<Birds::Robin>();
        m_entries.push_back("Robin");
        m_list["Capsule"] = std::make_shared<Birds::Capsule>();
        m_entries.push_back("Capsule");
        m_list["Goose"] = std::make_shared<Birds::Goose>();
        m_entries.push_back("Goose");

        m_isInitialized = true;
    };

    inline static inline bool m_isInitialized = false;
    inline static std::unordered_map<std::string, std::shared_ptr<IBird>> m_list;
    inline static std::vector<std::string> m_entries;
};