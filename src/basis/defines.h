/**
 * @Author: Xia Yunkai
 * @Date:   2024-05-28 19:11:20
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-05-29 19:38:04
 */

#ifndef __DEFINES_H__
#define __DEFINES_H__


#define XVIZ_MAX(a, b) (((a) > (b)) ? (a) : (b))                  // maximum
#define XVIZ_MIN(a, b) (((a) < (b)) ? (a) : (b))                  // minimum
#define XVIZ_CLAMP(v, min, max) (XVIZ_MAX(XVIZ_MIN(v, max), min)) // clamp
#define XVIZ_PI (3.1415926f)                                      // pi
#define XVIZ_2PI (6.2831853f)                                     // 2*pi
#define XVIZ_PI2 (1.5707963f)                                     // pi/2
#define XVIZ_PI4 (0.78539815f)                                    // pi/2
#define XVIZ_RPI (0.31831f)                                       // 1/pi
#define XVIZ_ANG2RAD(x) ((x) * HATA_PI * 0.0055556f)              // 角度转弧度，转完后变成浮点型
#define XVIZ_RAD2ANG(x) ((x) * HATA_RPI * 180)


#define CHECK_RETURN(state) \
    if (state)              \
    {                       \
        return;             \
    }

#define CHECK_CONTINUE(state) \
    if (state)                \
    {                         \
        continue;             \
    }

#define CHECK_BREAK(state) \
    if (state)             \
    {                      \
        break;             \
    }

#define CHECK_RETURN_RET(state, ret) \
    if (state)                       \
    {                                \
        return ret;                  \
    }

#define CHECK_SLEEP_CONTINUE(state, sleep_time)                             \
    if (state)                                                              \
    {                                                                       \
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time)); \
        continue;                                                           \
    }

#define DISALLOW_COPY_AND_ASSIGN(classname) \
private:                                    \
    classname(const classname &);           \
    classname &operator=(const classname &);

#define DISALLOW_IMPLICIT_CONSTRUCTORS(classname) \
private:                                          \
    classname();                                  \
    DISALLOW_COPY_AND_ASSIGN(classname);

#define DECLARE_SINGLETON(classname)          \
public:                                       \
    static classname *instance()              \
    {                                         \
        static classname instance;            \
        return &instance;                     \
    }                                         \
    DISALLOW_IMPLICIT_CONSTRUCTORS(classname) \
private:



#define NUMBER_OF_ARRAY(arr) (sizeof(arr) / sizeof(*arr))



#define CHECK_DELETE_RESET_OBJ(obj) \
    do                              \
    {                               \
        if (obj != nullptr)         \
        {                           \
            delete obj;             \
            obj = nullptr;          \
        }                           \
    } while (0)
#define CHECK_DELETE_OBJ(obj) \
    do                        \
    {                         \
        if (obj != nullptr)   \
        {                     \
            delete obj;       \
        }                     \
    } while (0)
#define CHECK_DELETE_RESET_ARRAY(arr) \
    do                                \
    {                                 \
        if (arr != nullptr)           \
        {                             \
            delete[] arr;             \
            arr = nullptr;            \
        }                             \
    } while (0)
#define CHECK_DELETE_ARRAY(arr) \
    do                          \
    {                           \
        if (arr != nullptr)     \
        {                       \
            delete[] arr;       \
        }                       \
    } while (0)
#define CHECK_FREE_RESET_PTR(ptr) \
    do                            \
    {                             \
        if (ptr != nullptr)       \
        {                         \
            free(ptr);            \
            ptr = nullptr;        \
        }                         \
    } while (0)
#define CHECK_FREE_PTR(ptr) \
    do                      \
    {                       \
        if (ptr != nullptr) \
        {                   \
            free(ptr);      \
        }                   \
    } while (0)
#define CHECK_CLOSE_RESET_FD(fd) \
    do                           \
    {                            \
        if (fd != -1)            \
        {                        \
            close(fd);           \
            fd = -1;             \
        }                        \
    } while (0)
#define CHECK_CLOSE_FD(fd) \
    do                     \
    {                      \
        if (fd != -1)      \
        {                  \
            close(fd);     \
        }                  \
    } while (0)

#endif /* __DEFINES_H__ */
