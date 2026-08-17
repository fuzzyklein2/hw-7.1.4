/**
 * @file str.cpp
 *
 * Functions for the `str` class.
 */

#include "str.hpp"

using namespace std;
using namespace hw7;

str str::lower()
{
    gchar* p = g_utf8_strup(c_str, length);
    str result(p);
    g_free(p);
    return result;
}

str str::upper()
{
    gchar* p = g_utf8_strdown(c_str, length);
    str result(p);
    g_free(p);
    return result;
}

StrList str::split()
{
    return split("\\s");
}

StrList str::split(const str& sep)
{
    GError* err = nullptr;
    GRegex* regex = g_regex_new(
        sep.c_str(),
        G_REGEX_DEFAULT,
        G_REGEX_MATCH_DEFAULT,
        &error
    );

    if (!regex)
    {
        // Handle error however your str class/project does errors.
        if (error)
            g_error_free(error);
        return {};
    }

    gchar** substrings = g_regex_split(regex, c_str, 0);

    StrList result;

    for (gchar** p = substrings; p && *p; ++p)
        result.emplace_back(*p);

    g_strfreev(substrings);
    g_regex_unref(regex);

    return result;
}

str str::join(const StrList& L)
{
    std::vector<gchar*> strings;
    strings.reserve(L.size() + 1);

    for (const std::string& s : L)
        strings.push_back(g_strdup(s.c_str()));

    strings.push_back(nullptr);

    gchar* p = g_strjoinv(c_str, strings.data());

    for (gchar* s : strings)
        g_free(s);

    str result(p);
    g_free(p);

    return result;
}

str str::replace(const str& pattern, const str& replacement)
{
    if (target.empty()) return *this;
    return regex_replace(*this, regex(pattern), replacement);
}