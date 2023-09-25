#pragma once
#include <memory>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define THROW_ERROR(exception_type, message)                                                                           \
    throw exception_type(std::string(__FILE__ ":" TOSTRING(__LINE__) ": ") + (message));

#define FWD_DECL(classname)                                                                                            \
    class classname;                                                                                                   \
    typedef std::shared_ptr<classname> classname##SPtr;                                                                \
    typedef std::unique_ptr<classname> classname##UPtr;

#define FWD_DECL_VEC(classname)                                                                                        \
    typedef std::vector<classname> classname##Vector;                                                                  \
    typedef std::vector<std::shared_ptr<classname>> classname##SPtrVec;                                                \
    typedef std::shared_ptr<std::vector<std::shared_ptr<classname>>> classname##SPtrVecSPtr;

#define FWD_DECL_LIST(classname)                                                                                       \
    typedef std::list<classname> classname##List;                                                                      \
    typedef std::list<std::shared_ptr<classname>> classname##SPtrList;                                                 \
    typedef std::shared_ptr<std::list<std::shared_ptr<classname>>> classname##SPtrListcSPtr;

#define FWD_DECL_QUEUE(classname)                                                                                      \
    typedef std::deque<classname> classname##Deque;                                                                    \
    typedef std::deque<std::shared_ptr<classname>> classname##SPtrDeque;                                               \
    typedef std::shared_ptr<std::deque<std::shared_ptr<classname>>> classname##SPtrDequeSPtr;

#define DECL_READONLY_PROPERTY(type, name)                                                                             \
private:                                                                                                               \
    type m_prop##name;                                                                                                 \
                                                                                                                       \
public:                                                                                                                \
    const type & get##name() const                                                                                     \
    {                                                                                                                  \
        return m_prop##name;                                                                                           \
    }                                                                                                                  \
    constexpr static const char * STR_##name = #name;

using BYTE = uint8_t;

class NonCopyable
{
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

public:
    NonCopyable(const NonCopyable &) = delete;
    const NonCopyable & operator=(const NonCopyable &) = delete;
    NonCopyable(NonCopyable &&) = delete;
    const NonCopyable & operator=(NonCopyable &&) = delete;
};

#define DEFINE_STR(keyName, valString) constexpr auto keyName = #valString; // NOLINT (bugprone-macro-parentheses)

DEFINE_STR(IMAGE_ID, imgKey)
DEFINE_STR(PRINT_DEFINITION, canvas)
DEFINE_STR(PHOTO_STANDARD, standard)
DEFINE_STR(CROWN_POINT, crownPoint)
DEFINE_STR(CHIN_POINT, chinPoint)
DEFINE_STR(EXIF_INFO, EXIFInfo)
DEFINE_STR(AS_BASE64, asBase64)

DEFINE_STR(UNITS, units)

// Photo requirement fields
DEFINE_STR(PHOTO_WIDTH, pictureWidth)
DEFINE_STR(PHOTO_HEIGHT, pictureHeight)
DEFINE_STR(PHOTO_FACE_HEIGHT, faceHeight)
DEFINE_STR(PHOTO_CROWN_TOP, crownTop)
DEFINE_STR(PHOTO_EYELINE_BOTTOM, bottomEyeLine)
DEFINE_STR(PHOTO_RESOLUTION, dpi)

// Print definition fields
DEFINE_STR(PRINT_WIDTH, width)
DEFINE_STR(PRINT_HEIGHT, height)
DEFINE_STR(PRINT_GUTTER, gutter)
DEFINE_STR(PRINT_PADDING, padding)
DEFINE_STR(PRINT_RESOLUTION, resolution)

// Compliance check
DEFINE_STR(COMPLIANCE_CHECKS, complianceChecks)
DEFINE_STR(COMPLIANCE_RESULT_SUCCESS, success)
DEFINE_STR(COMPLIANCE_RESULT_MESSAGE, message)
DEFINE_STR(COMPLIANCE_RESULT_CHECK_NAME, checkName)

DEFINE_STR(CROWN_CHIN_ESTIMATOR, crownChinEstimator)
DEFINE_STR(CHIN_CROWN_COEFF, chinCrownCoeff)
DEFINE_STR(CHIN_FROWN_COEFF, chinFrownCoeff)
