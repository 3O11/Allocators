// TODO(3011): These headers need some pruning.
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstdio>

// Platform detection macros
// TODO(3011): This here is very limited, survey possible extensions.
#define TTA_PLATFORM_UNKNOWN 0
#define TTA_PLATFORM_WINDOWS 1
#define TTA_PLATFORM_MACOS   2
#define TTA_PLATFORM_LINUX   3

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#   define TTA_CURRENT_PLATFORM TTA_PLATFORM_WINDOWS
#elif defined(__APPLE__)
#   define TTA_CURRENT_PLATFORM TTA_PLATFORM_MACOS
#elif defined(__linux__)
#   define TTA_CURRENT_PLATFORM TTA_PLATFORM_LINUX
#else
#   define TTA_CURRENT_PLATFORM TTA_PLATFORM_UNKNOWN
#   warning "Could not determine the current platform!"
#endif

#define TTA_IS_PLATFORM_WINDOWS (TTA_CURRENT_PLATFORM == TTA_PLATFORM_WINDOWS)
#define TTA_IS_PLATFORM_MACOS   (TTA_CURRENT_PLATFORM == TTA_PLATFORM_MACOS)
#define TTA_IS_PLATFORM_LINUX   (TTA_CURRENT_PLATFORM == TTA_PLATFORM_LINUX)

#define TTA_IS_PLATFORM_POSIX   (TTA_IS_PLATFORM_LINUX || TTA_IS_PLATFORM_MACOS)

namespace tt
{
    // Useful type aliases
    using size_t = std::size_t;

    template <size_t StrLen>
    class AllocConstString
    {
    public:
        char Value[StrLen];

        constexpr AllocConstString(const char(&StrLiteral)[StrLen])
        {
            for (size_t i = 0; i < StrLen; ++i)
            {
                Value[i] = StrLiteral[i];
            }
        }

        constexpr size_t Size()   const { return StrLen; }
        constexpr size_t Length() const { return StrLen; }

        template <size_t OtherStrLen>
        constexpr bool operator==(AllocConstString& other) const
        {
            if (Length() != other.Length())
            {
                return false;
            }

            for (size_t i = 0; i < Length(); ++i)
            {
                if (Value[i] != other.Value[i])
                {
                    return false;
                }
            }

            return true;
        }
        template <size_t OtherStrLen>
        constexpr bool operator!=(AllocConstString& other) const
        {
            return !(*this == other);
        }
    };

    template <size_t StrLen>
    static constexpr void AllocAssert(bool expr, AllocConstString<StrLen> message)
    {
        if (!expr)
        {
            std::printf("%s", message.Value);
            std::exit(EXIT_FAILURE);
        }
    }
}
