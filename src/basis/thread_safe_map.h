/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 18:54:14
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-22 15:48:16
 */

#ifndef __THREAD_SAFE_MAP_H__
#define __THREAD_SAFE_MAP_H__
#include <map>
#include <mutex>
#include <vector>
namespace basis
{

    template <typename Key, typename Value>
    class ThreadSafeMap
    {
    public:
        using MapType = std::map<Key, Value>;
        using IteratorType = typename MapType::iterator;
        ThreadSafeMap() = default;

        virtual ~ThreadSafeMap() = default;

        ThreadSafeMap(const ThreadSafeMap &other)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_map = other.m_map;
        }

        Value &operator[](const Key &key)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_map[key];
        }

        Value &at(const Key &key)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_map.at(key);
        }

        bool HasElements() const
        {
            bool hasElements;
            std::lock_guard<std::mutex> lock(m_mutex);
            hasElements = (m_map.size() > 0);
            return hasElements;
        }

        bool Exists(const Key &key) const
        {
            bool exists;
            std::lock_guard<std::mutex> lock(m_mutex);

            exists = (m_map.find(key) != m_map.end());

            return exists;
        }

        void Insert(const Key &key, const Value &value)
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_map[key] = value;
        }

        bool Remove(const Key &key, Value &value)
        {
            bool exists;
            std::lock_guard<std::mutex> lock(m_mutex);
            auto iter = m_map.find(key);
            if (iter != m_map.end())
            {
                value = iter->second;
                m_map.erase(iter);
                exists = true;
            }
            else
            {
                exists = false;
            }
            return exists;
        }

        void RemoveAll()
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_map.clear();
        }

        void clear()
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            m_map.clear();
        }

        bool Get(const Key &key, Value &value) const
        {
            bool exists;
            std::lock_guard<std::mutex> lock(m_mutex);

            auto iter = m_map.find(key);
            if (iter != m_map.end())
            {
                value = iter->second;
                exists = true;
            }
            else
            {
                exists = false;
            }

            return exists;
        }

        void GatherKeyAll(std::vector<Key> &keys) const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_map.size() > 0)
            {
                keys.resize(m_map.size());
                auto kiter = keys.begin();
                for (auto const &m : m_map)
                {
                    *kiter++ = m.first;
                }
            }
            else
            {
                keys.clear();
            }
        }

        void GatherValueAll(std::vector<Value> &values) const
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            if (m_map.size() > 0)
            {
                values.resize(m_map.size());
                auto viter = values.begin();
                for (auto const &m : m_map)
                {
                    *viter++ = m.second;
                }
            }
            else
            {
                values.clear();
            }
        }

        IteratorType begin()
        {
            return m_map.begin();
        }

        IteratorType end()
        {
            return m_map.end();
        }

        bool empty() const
        {
            bool ret = m_map.empty();
            return ret;
        }

    protected:
        std::map<Key, Value> m_map;
        mutable std::mutex m_mutex;
    };
} // namespace basis

#endif /* __THREAD_SAFE_MAP_H__ */
