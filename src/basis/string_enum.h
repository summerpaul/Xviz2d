/**
 * @Author: Xia Yunkai
 * @Date:   2023-12-30 10:31:21
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-06-03 10:41:40
 */
#pragma once

#include <string>

namespace basis
{
    namespace details
    {

        template <class T, T N>
        const char *get_enum_name_static()
        {
#if defined(_MSC_VER)
            return __FUNCSIG__;
#else
            return __PRETTY_FUNCTION__;
#endif
        }

        //  "SFINAE" (Substitution Failure Is Not An Error)
        template <bool Cond>
        struct my_enable_if
        {
        };
        template <>
        struct my_enable_if<true>
        {
            typedef void type;
        };

        template <int Beg, int End, class F>
        typename my_enable_if<Beg == End>::type static_for(F const &func) {}

        // 递归调用
        template <int Beg, int End, class F>
        typename my_enable_if<Beg != End>::type static_for(F const &func)
        {
            // 传递模板参数
            func.template call<Beg>();
            static_for<Beg + 1, End>(func);
        }

        template <class T>
        struct get_enum_name_functor
        {
            int n;
            std::string &s;

            get_enum_name_functor(int n, std::string &s) : n(n), s(s) {}

            template <int I>
            void call() const
            {
                // 在寻找每个枚举值时都要完整遍历0-256
                if (n == I)
                    s = details::get_enum_name_static<T, (T)I>();
            }
        };

    } // namespace details

    template <class T, T Beg, T End>
    std::string get_enum_name(T n)
    {
        std::string s;
        // 如果是enum class ，需要显式的将枚举值转换为int
        details::static_for<int(Beg), int(End) + 1>(
            details::get_enum_name_functor<T>(int(n), s));
        if (s.empty())
            return "";
#if defined(_MSC_VER)
        size_t pos = s.find(',');
        pos += 1;
        size_t pos2 = s.find('>', pos);
#else
        size_t pos = s.find("N = ");
        pos += 4;
        size_t pos2 = s.find_first_of(";]", pos);
#endif
        s = s.substr(pos, pos2 - pos);
        // 需要去掉所有的命名空间和类型名称
        size_t pos3 = s.find_last_of(':');
        if (pos3 != s.npos)
        {
            s = s.substr(pos3 + 1);
        }
        return s;
    }

    // interface: from enum type to string
    template <class T>
    std::string get_enum_name(T n)
    {
        return get_enum_name<T, (T)0, (T)256>(n);
    }

    template <class T, T Beg, T End>
    int enum_from_name(std::string const &s)
    {
        for (int i = (int)Beg; i < (int)End; i++)
        {
            if (s == get_enum_name((T)i))
            {
                return i;
            }
        }
        throw std::runtime_error("invalid enum name");
    }

    // interface: from string to enum type
    template <class T>
    int enum_from_name(std::string const &s)
    {
        return enum_from_name<T, (T)0, (T)256>(s);
    }

} // namespace science