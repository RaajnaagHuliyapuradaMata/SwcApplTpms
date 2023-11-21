

#ifndef STD_TYPES_H
#define STD_TYPES_H

#include "Platform_Types.h"
#include "Compiler.h"

#define COMMONASR__COMMON_IMPL_STDTYPES_VERSION 0x0304
#define COMMONASR__COMMON_IMPL_STDTYPES_RELEASE_VERSION 0x01

#  define STD_TYPES_AR_RELEASE_MAJOR_VERSION       (4u)
#  define STD_TYPES_AR_RELEASE_MINOR_VERSION       (0u)
#  define STD_TYPES_AR_RELEASE_PATCH_VERSION       (1u)

#define STD_TYPES_SW_MAJOR_VERSION       (3u)
#define STD_TYPES_SW_MINOR_VERSION       (4u)
#define STD_TYPES_SW_PATCH_VERSION       (1u)

#define STD_HIGH     1u
#define STD_LOW      0u

#define STD_ACTIVE   1u
#define STD_IDLE     0u

#define STD_ON       1u
#define STD_OFF      0u

# ifndef STATUSTYPEDEFINED
#  define STATUSTYPEDEFINED
#  define E_OK      0u
typedef unsigned char StatusType;
# endif

#define E_NOT_OK  1u

typedef uint8 Std_ReturnType;

typedef struct{
   uint16 vendorID;
   uint16 moduleID;
   uint8  sw_major_version;
   uint8  sw_minor_version;
   uint8  sw_patch_version;
}Std_VersionInfoType;

#endif

