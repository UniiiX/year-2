#ifndef COLOR_H
#define COLOR_H

enum class Color{red, black};

inline bool operator<(const Color & left, const Color & right)
{
    return static_cast<int>(left) < static_cast<int>(right);
}

inline bool operator>(const Color & left, const Color & right)
{
    return static_cast<int>(left) > static_cast<int>(right);
}

#endif // COLOR_H
