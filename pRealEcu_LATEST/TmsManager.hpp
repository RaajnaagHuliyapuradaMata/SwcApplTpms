

#ifndef TMS_MANAGER_H
#define TMS_MANAGER_H

#include "TmsManagerX.hpp"

#define TMS__INIT_VALUE                         ((uint8) 0x00U)

#define TMS__FUNCTIONING_BIT_MASK               ((uint8) 0x01U)         //!< Bit mask used to check if TMS is functioning.
#define TMS__AUTOLOCATION_BIT_MASK              ((uint8) 0x02U)         //!< Bit mask used to check if autolocation is finished.
#define TMS__CYCLIC_MESSAGE_BIT_MASK            ((uint8) 0x04U)         //!< Bit mask used to check if cyclic messages are enabled.
#define TMS__AUTOLEARN_BIT_MASK                 ((uint8) 0x08U)         //!< Bit mask used to check if autolearn is finished.
#define TMS__DEVELOPER_MODE_BIT_MASK            ((uint8) 0x10U)         //!< Bit mask used to check if developer mode is enabled.

#endif
