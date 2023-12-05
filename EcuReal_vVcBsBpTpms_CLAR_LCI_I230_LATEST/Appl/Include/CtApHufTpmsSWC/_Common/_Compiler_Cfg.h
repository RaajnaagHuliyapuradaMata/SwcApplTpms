

#ifndef COMPILER_CFG_H
#define COMPILER_CFG_H

#include "Rte_Compiler_Cfg.h"

#define AUTOSAR_COMSTACKDATA

#define MSR_REGSPACE  REGSPACE

#define V_SUPPRESS_EXTENDED_VERSION_CHECK
#define V_USE_DUMMY_STATEMENT

#define REGSPACE

#define _STATIC_   STATIC
#define _INLINE_   INLINE

#define LINNM_CONTROL_BIT_VECTOR_ENABLED STD_ON
#define V_SUPPRESS_EXTENDED_VERSION_CHECK
#define V_USE_DUMMY_STATEMENT  STD_ON

#include "Rte_Compiler_Cfg.h"
#define STATIC static

#define COMM_CODE

#define COMM_CONST

#define COMM_VAR_NOINIT_8BIT
#define COMM_VAR_NOINIT_16BIT
#define COMM_VAR_NOINIT_UNSPECIFIED
#define COMM_VAR_ZERO_INIT

#define COMM_APPL_CODE
#define COMM_APPL_VAR
#define COMM_APPL_VAR_NVRAM

#define CANSM_CODE

#define CANSM_CONST
#define CANSM_PBCFG

#define CANSM_VAR_NOINIT
#define CANSM_VAR_ZERO_INIT

#define CANSM_APPL_VAR

#define FRSM_CODE
#define FRSM_APPL_CODE

#define FRSM_CONST
#define FRSM_PBCFG

#define FRSM_VAR_NOINIT
#define FRSM_VAR_ZERO_INIT

#define FRSM_APPL_VAR

#define LINSM_CODE

#define LINSM_CONST
#define LINSM_PBCFG
#define LINSM_VAR_NOINIT
#define LINSM_VAR_ZERO_INIT
#define LINSM_APPL_DATA

#define CDD_CODE
#define CDD_APPL_DATA
#define CDD_LINTP_CODE
#define CDD_LINTP_APPL_DATA

#define XCP_CONST
#define XCP_CODE
#define XCP_APPL_DATA
#define XCP_MTA_DATA
#define XCP_DAQ_DATA
#define XCP_VAR_NOINIT

#define CANXCP_VAR_NOINIT
#define CANXCP_CONST
#define CANXCP_PBCFG
#define CANXCP_CODE
#define CANXCP_APPL_VAR

#define FRXCP_PBCFG
#define FRXCP_CONST
#define FRXCP_CODE
#define FRXCP_APPL_DATA
#define FRXCP_VAR_NOINIT

#define DCM_APPL_CONST
#define DCM_APPL_DATA
#define DCM_CONST
#define DCM_CODE
#define DCM_APPL_CODE
#define DCM_CALLOUT_CODE
#define DCM_VAR_NOINIT

#define DEM_CODE
#define DEM_VAR_INIT
#define DEM_VAR_NOINIT
#define DEM_CONST
#define DEM_PBCFG
#define DEM_DCM_DATA
#define DEM_DLT_DATA
#define DEM_NVM_DATA
#define DEM_APPL_CODE
#define DEM_APPL_DATA
#define DEM_APPL_CONST
#define DEM_SHARED_DATA
#define DEM_C_CONST             DEM_CODE
#define DEM_C_VAR_NOINIT        DEM_VAR_NOINIT
#define DEM_C_NVM_DATA_NOINIT   DEM_NVM_DATA

#define ADC_APPL_DATA
#define ADC_CONST
#define ADC_CODE
#define ADC_APPL_CONST
#define ADC_PBCFG
#define ADC_APPL_VAR
#define ADC_VAR
#define ADC_APPL_CODE

#define CAN_CODE
#define CAN_STATIC_CODE
#define CAN_CONST
#define CAN_CONST_PBCFG
#define CAN_VAR_NOINIT
#define CAN_VAR_INIT
#define CAN_INT_CTRL
#define CAN_REG_CANCELL
#define CAN_RX_TX_DATA        CAN_REG_CANCELL
#define CAN_APPL_CODE
#define CAN_APPL_CONST
#define CAN_APPL_VAR

#define DIO_APPL_DATA
#define DIO_CONST
#define DIO_CODE
#define DIO_APPL_CONST

#define FLS_APPL_CODE
#define FLS_CONST
#define FLS_APPL_DATA
#define FLS_APPL_CONST
#define FLS_CODE

#define FR_CODE
#define FR_CODE_ISR

#define FR_CONST
#define FR_APPL_CONST
#define FR_PBCFG
#define FR_APPL_DATA
#define FR_VAR_FRM_DATA
#define FR_APPL_CODE

#define FR_VAR_NOINIT
#define FR_VAR_NOINIT_FAST

#define GPT_APPL_DATA
#define GPT_CONST
#define GPT_CODE
#define GPT_PBCFG
#define GPT_APPL_CONST

#define ICU_CODE
#define ICU_APPL_CONST
#define ICU_APPL_DATA
#define ICU_VAR_FAST

#define LIN_CODE
#define LIN_CODE_ISR
#define LIN_CONST
#define LIN_VAR_NOINIT
#define LIN_VAR_ZERO_INIT
#define LIN_VAR_REGS
#define LIN_PBCFG
#define LIN_PBCFG_ROOT
#define LIN_APPL_VAR

#define MCU_APPL_DATA
#define MCU_CONST
#define MCU_CODE
#define MCU_APPL_CONST

#define PORT_CODE
#define PORT_VAR
#define PORT_CONST
#define PORT_APPL_DATA
#define PORT_APPL_CONST
#define PORT_PBCFG
#define PORT_REGISTER

#define PWM_CODE

#define SPI_CODE
#define SPI_APPL_CODE
#define SPI_APPL_CONST

#define IOHWAB_CODE

#define IOHWAB_VAR

#define IOHWAB_APPL_DATA
#define IOHWAB_APPL_CODE

#define IOHWAB_CONST

#define PDUR_CODE
#define PDUR_VAR_NOINIT
#define PDUR_VAR_ZERO_INIT
#define PDUR_VAR
#define PDUR_CONST
#define PDUR_PBCFG
#define PDUR_APPL_DATA
#define PDUR_APPL_CODE
#define PDUR_PBCFG_ROOT		PDUR_PBCFG

#define LINIF_CODE
#define LINIF_CONST
#define LINIF_VAR_NOINIT
#define LINIF_VAR_ZERO_INIT
#define LINIF_APPL_DATA
#define LINIF_APPL_VAR
#define LINIF_PBCFG_ROOT
#define LINIF_PBCFG
#define LINIF_APPL_PBCFG
#define LINIF_CBK_TRCV_CODE

#define LINTP_CODE
#define LINTP_CONST
#define LINTP_VAR_NOINIT
#define LINTP_VAR_ZERO_INIT
#define LINTP_APPL_DATA
#define LINTP_APPL_VAR
#define LINTP_PBCFG_ROOT
#define LINTP_PBCFG
#define LINTP_APPL_PBCFG

#define CANIF_VAR_NOINIT
#define CANIF_VAR_ZERO_INIT
#define CANIF_VAR_INIT

#define CANIF_CONST
#define CANIF_PBCFG
#define CANIF_PBCFG_ROOT

#define CANIF_CODE

#define CANIF_APPL_CODE
#define CANIF_APPL_VAR
#define CANIF_APPL_PBCFG

#define CANIF_VAR_STACK

#define CANIF_APPL_STATE_VAR   CANIF_APPL_VAR
#define CANIF_APPL_MSG_VAR     CANIF_APPL_VAR

#define CANIF_CBK_VAR          CANIF_APPL_VAR

#define CANIF_CBK_DRV_VAR      CANIF_CBK_VAR

#define CANIF_CBK_TRCV_CODE     CANIF_APPL_CODE
#define CANIF_APPL_STATE_CODE   CANIF_APPL_CODE
#define CANIF_APPL_MSG_CODE     CANIF_APPL_CODE

#define CANIF_UL_STANDARD_VAR    CANIF_APPL_VAR
#define CANIF_UL_ADVANCED_VAR    CANIF_APPL_VAR
#define CANIF_UL_OSEKNM_VAR      CANIF_APPL_VAR

#define FEE_API_CODE
#define FEE_CODE
#define FEE_APPL_CODE
#define FEE_APPL_CONFIG
#define FEE_APPL_DATA
#define FEE_CONST
#define FEE_PRIVATE_CODE
#define FEE_PRIVATE_CONST
#define FEE_PRIVATE_DATA
#define FEE_VAR
#define FEE_VAR_NOINIT

#define FRIF_CODE
#define FRIF_CODE_FAST
#define FRIF_CODE_ISR

#define FRIF_CONST
#define FRIF_CONST_FAST
#define FRIF_PBCFG
#define FRIF_PBCFG_ROOT

#define FRIF_VAR_INIT
#define FRIF_VAR_NOINIT
#define FRIF_VAR_ZERO_INIT
#define FRIF_VAR_INIT_FAST
#define FRIF_VAR_NOINIT_FAST
#define FRIF_VAR_ZERO_INIT_FAST

#define FRIF_APPL_DATA
#define FRIF_APPL_CODE

#define MEMIF_CODE
#define MEMIF_CONST
#define MEMIF_APPL_DATA

#define WDGIF_CODE
#define WDGIF_CONST
#define WDGIF_WDG_CODE
#define WDGIF_APPL_DATA

#define COM_CONST

#define COM_PBCFG

#define COM_PBCFG_ROOT 		COM_PBCFG

#define COM_CODE

#define COM_VAR_NOINIT

#define COM_VAR_INIT

#define COM_APPL_CODE

#define COM_APPL_VAR

#define COM_APPL_DATA

#define IPDUM_CODE
#define IPDUM_PBCFG
#define IPDUM_VAR_INIT
#define IPDUM_VAR_NOINIT
#define IPDUM_APPL_DATA
#define IPDUM_PBCFG_ROOT                  IPDUM_PBCFG

#define NVM_APPL_DATA
#define NVM_APPL_CODE
#define NVM_APPL_CONST

#define NVM_CRC_APPL_DATA

#define NVM_CONFIG_DATA
#define NVM_CONFIG_CONST

#define NVM_CODE

#define NVM_FAST_DATA

#define NVM_PRIVATE_CODE
#define NVM_PRIVATE_CONST
#define NVM_PRIVATE_DATA

#define NVM_PUBLIC_CODE
#define NVM_PUBLIC_CONST

#define DLT_CODE

#define DLT_CONST

#define DLT_VAR_INIT
#define DLT_VAR_NOINIT
#define DLT_VAR_ZERO_INIT

#define GENMEAS_CONST

#define AMDRTM_CODE
#define AMDRTM_VAR

#define CANNM_CODE

#define CANNM_CONST
#define CANNM_PBCFG
#define CANNM_PBCFG_ROOT

#define CANNM_VAR_NOINIT
#define CANNM_VAR_NOINIT_FAST
#define CANNM_VAR_ZERO_INIT_FAST
#define CANNM_APPL_VAR

#define FRNM_CODE

#define FRNM_CONST
#define FRNM_PBCFG
#define FRNM_PBCFG_ROOT

#define FRNM_VAR_NOINIT
#define FRNM_VAR_NOINIT_FAST
#define FRNM_VAR_ZERO_INIT_FAST
#define FRNM_APPL_VAR

#define NM_CODE

#define NM_CONST

#define NM_VAR_NOINIT_FAST
#define NM_VAR_ZERO_INIT_FAST
#define NM_APPL_VAR

#define LINNM_CODE

#define LINNM_CONST
#define LINNM_PBCFG
#define LINNM_PBCFG_ROOT

#define LINNM_VAR_NOINIT
#define LINNM_VAR_NOINIT_FAST
#define LINNM_VAR_ZERO_INIT_FAST
#define LINNM_APPL_VAR

#define BSWM_CODE
#define BSWM_APPL_CODE
#define BSWM_CONST
#define BSWM_PBCFG
#define BSWM_VAR_INIT
#define BSWM_APPL_DATA
#define BSWM_VAR_NOINIT

#define ECUM_API_CODE
#define ECUM_APPL_DATA
#define ECUM_VAR_BOOT
#define ECUM_CODE
#define ECUM_CODE_BOOT_TARGET
#define ECUM_PBCFG
#define ECUM_VAR
#define ECUM_VAR_NOINIT

#define CRC_APPL_DATA
#define CRC_CODE
#define CRC_CONST

#define DET_CODE
#define DET_VAR
#define DET_APPL_DATA
#define DET_APPL_CODE

#define RAMTST_APPL_DATA
#define RAMTST_CODE
#define RAMTST_VAR
#define RAMTST_CONST
#define RAMTST_PBCFG

#define WDGM_CODE

#define WDGM_VAR
#define WDGM_VAR_NOINIT
#define WDGM_DATA

#define WDGM_APPL_DATA
#define WDGM_APPL_CODE

#define WDGM_CONST
#define WDGM_PBCFG

#define CANTP_CODE
#define CANTP_CONST
#define CANTP_APPL_CONST
#define CANTP_APPL_DATA
#define CANTP_VAR_NOINIT
#define CANTP_VAR_INIT
#define CANTP_PBCFG

#define FRTP_CODE

#define TP_ISO10681_CODE
#define TP_ISO10681_CONST

#define TP_ISO10681_APPL_DATA
#define TP_ISO10681_APPL_CODE

#define TP_ISO10681_VAR_NOINIT

#define TP_ISO10681_PBCFG
#define TP_ISO10681_PBCFG_ROOT

#define VSTDLIB_CODE
#define VSTDLIB_CONST
#define VSTDLIB_VAR_NEAR
#define VSTDLIB_CONST_FAR
#define VSTDLIB_VAR_FAR
#define VSTDLIB_VAR_NOINIT

#endif

