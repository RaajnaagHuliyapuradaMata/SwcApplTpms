

#if(!defined  FR_GENERALTYPES_H)
#define FR_GENERALTYPES_H

#include "Std_Types.h"

#define DRVFR__BASEASR_VERSION          0x0107u
#define DRVFR__BASEASR_RELEASE_VERSION  0x00u

typedef void Fr_ConfigType;

typedef uint8 Fr_SyncStateType;
#define FR_ASYNC ((Fr_SyncStateType)0)
#define FR_SYNC  ((Fr_SyncStateType)1)

typedef uint8 Fr_OffsetCorrectionType;
#define FR_OFFSET_INC       ((Fr_OffsetCorrectionType)0)
#define FR_OFFSET_DEC       ((Fr_OffsetCorrectionType)1)
#define FR_OFFSET_NOCHANGE  ((Fr_OffsetCorrectionType)2)

typedef uint8 Fr_RateCorrectionType;
#define FR_RATE_INC       ((Fr_RateCorrectionType)0)
#define FR_RATE_DEC       ((Fr_RateCorrectionType)1)
#define FR_RATE_NOCHANGE  ((Fr_RateCorrectionType)2)

typedef uint8 Fr_POCStateType;
#define FR_POCSTATE_CONFIG          ((Fr_POCStateType)0)
#define FR_POCSTATE_DEFAULT_CONFIG  ((Fr_POCStateType)1)
#define FR_POCSTATE_HALT            ((Fr_POCStateType)2)
#define FR_POCSTATE_NORMAL_ACTIVE   ((Fr_POCStateType)3)
#define FR_POCSTATE_NORMAL_PASSIVE  ((Fr_POCStateType)4)
#define FR_POCSTATE_READY           ((Fr_POCStateType)5)
#define FR_POCSTATE_STARTUP         ((Fr_POCStateType)6)
#define FR_POCSTATE_WAKEUP          ((Fr_POCStateType)7)

typedef uint8 Fr_TxLPduStatusType;
#define FR_TRANSMITTED      ((Fr_TxLPduStatusType)0)
#define FR_NOT_TRANSMITTED  ((Fr_TxLPduStatusType)1)

typedef uint8 Fr_RxLPduStatusType;
#define FR_RECEIVED     ((Fr_RxLPduStatusType)0)
#define FR_NOT_RECEIVED ((Fr_RxLPduStatusType)1)
#define FR_RECEIVED_MORE_DATA_AVAILABLE ((Fr_RxLPduStatusType)2)

typedef uint8 Fr_WakeupStateType;
#define FR_WAKEUPSTATE_UNDEFINED          ((Fr_WakeupStateType)0)
#define FR_WAKEUPSTATE_RECEIVED_HEADER    ((Fr_WakeupStateType)1)
#define FR_WAKEUPSTATE_RECEIVED_WUP       ((Fr_WakeupStateType)2)
#define FR_WAKEUPSTATE_COLLISION_HEADER   ((Fr_WakeupStateType)3)
#define FR_WAKEUPSTATE_COLLISION_WUP      ((Fr_WakeupStateType)4)
#define FR_WAKEUPSTATE_COLLISION_UNKNOWN  ((Fr_WakeupStateType)5)
#define FR_WAKEUPSTATE_TRANSMITTED        ((Fr_WakeupStateType)6)

typedef uint8 Fr_MTSStatusType;
#define FR_MTS_RCV                ((Fr_MTSStatusType)0)
#define FR_MTS_RCV_SYNERR         ((Fr_MTSStatusType)1)
#define FR_MTS_RCV_BVIO           ((Fr_MTSStatusType)2)
#define FR_MTS_RCV_SYNERR_BVIO    ((Fr_MTSStatusType)3)
#define FR_MTS_NOT_RCV            ((Fr_MTSStatusType)4)
#define FR_MTS_NOT_RCV_SYNERR     ((Fr_MTSStatusType)5)
#define FR_MTS_NOT_RCV_BVIO       ((Fr_MTSStatusType)6)
#define FR_MTS_NOT_RCV_SYNERR_BVIO ((Fr_MTSStatusType)7)

typedef uint8 Fr_ChannelType;
#define FR_CHANNEL_A  ((Fr_ChannelType)0)
#define FR_CHANNEL_B  ((Fr_ChannelType)1)
#define FR_CHANNEL_AB ((Fr_ChannelType)2)

typedef uint8 Fr_SlotModeType;
#define FR_SLOTMODE_SINGLE      ((Fr_SlotModeType)0)
#define FR_SLOTMODE_ALL_PENDING ((Fr_SlotModeType)1)
#define FR_SLOTMODE_ALL         ((Fr_SlotModeType)2)

typedef uint8 Fr_ErrorModeType;
#define FR_ERRORMODE_ACTIVE     ((Fr_ErrorModeType)0)
#define FR_ERRORMODE_PASSIVE    ((Fr_ErrorModeType)1)
#define FR_ERRORMODE_COMM_HALT  ((Fr_ErrorModeType)2)

typedef uint8 Fr_WakeupStatusType;
#define FR_WAKEUP_UNDEFINED         ((Fr_WakeupStatusType)0)
#define FR_WAKEUP_RECEIVED_HEADER   ((Fr_WakeupStatusType)1)
#define FR_WAKEUP_RECEIVED_WUP      ((Fr_WakeupStatusType)2)
#define FR_WAKEUP_COLLISION_HEADER  ((Fr_WakeupStatusType)3)
#define FR_WAKEUP_COLLISION_WUP     ((Fr_WakeupStatusType)4)
#define FR_WAKEUP_COLLISION_UNKNOWN ((Fr_WakeupStatusType)5)
#define FR_WAKEUP_TRANSMITTED       ((Fr_WakeupStatusType)6)

typedef uint8 Fr_StartupStateType;
#define  FR_STARTUP_UNDEFINED                     ((Fr_StartupStateType)0)
#define  FR_STARTUP_COLDSTART_LISTEN              ((Fr_StartupStateType)1)
#define  FR_STARTUP_INTEGRATION_COLDSTART_CHECK   ((Fr_StartupStateType)2)
#define  FR_STARTUP_COLDSTART_JOIN                ((Fr_StartupStateType)3)
#define  FR_STARTUP_COLDSTART_COLLISION_RESOLUTION  ((Fr_StartupStateType)4)
#define  FR_STARTUP_COLDSTART_CONSISTENCY_CHECK   ((Fr_StartupStateType)5)
#define  FR_STARTUP_INTEGRATION_LISTEN            ((Fr_StartupStateType)6)
#define  FR_STARTUP_INITIALIZE_SCHEDULE           ((Fr_StartupStateType)7)
#define  FR_STARTUP_INTEGRATION_CONSISTENCY_CHECK ((Fr_StartupStateType)8)
#define  FR_STARTUP_COLDSTART_GAP                 ((Fr_StartupStateType)9)

typedef struct{
   boolean ColdstartNoise;
   boolean CHIHaltRequest;
   boolean Freeze;
  Fr_SlotModeType SlotMode;
  Fr_WakeupStatusType WakeupStatus;
  Fr_ErrorModeType ErrorMode;
  Fr_StartupStateType StartupState;
  Fr_POCStateType State;
}Fr_POCStatusType;

typedef uint32 Fr_VErrorStatusType;

#define	FR_CIDX_GDCYCLE	0
#define	FR_CIDX_PMICROPERCYCLE	1
#define	FR_CIDX_PDLISTENTIMEOUT	2

#define	FR_CIDX_GMACROPERCYCLE	3
#define	FR_CIDX_GDMACROTICK	4
#define	FR_CIDX_GNUMBEROFMINISLOTS	5
#define	FR_CIDX_GNUMBEROFSTATICSLOTS	6
#define	FR_CIDX_GDNIT	7
#define	FR_CIDX_GDSTATICSLOT	8
#define	FR_CIDX_GDWAKEUPRXWINDOW	9
#define	FR_CIDX_PKEYSLOTID	10
#define	FR_CIDX_PLATESTTX 	11
#define	FR_CIDX_POFFSETCORRECTIONOUT	12
#define	FR_CIDX_POFFSETCORRECTIONSTART	13
#define	FR_CIDX_PRATECORRECTIONOUT	14
#define	FR_CIDX_PSECONDKEYSLOTID	15
#define	FR_CIDX_PDACCEPTEDSTARTUPRANGE	16

#define	FR_CIDX_GCOLDSTARTATTEMPTS	17
#define	FR_CIDX_GCYCLECOUNTMAX	18
#define	FR_CIDX_GLISTENNOISE	19
#define	FR_CIDX_GMAXWITHOUTCLOCKCORRECTFATAL 	20
#define	FR_CIDX_GMAXWITHOUTCLOCKCORRECTPASSIVE	21
#define	FR_CIDX_GNETWORKMANAGEMENTVECTORLENGTH	22
#define	FR_CIDX_GPAYLOADLENGTHSTATIC	23
#define	FR_CIDX_GSYNCFRAMEIDCOUNTMAX	24
#define	FR_CIDX_GDACTIONPOINTOFFSET	25
#define	FR_CIDX_GDBIT	26
#define	FR_CIDX_GDCASRXLOWMAX	27
#define	FR_CIDX_GDDYNAMICSLOTIDLEPHASE	28
#define	FR_CIDX_GDMINISLOTACTIONPOINTOFFSET	29
#define	FR_CIDX_GDMINISLOT	30
#define	FR_CIDX_GDSAMPLECLOCKPERIOD	31
#define	FR_CIDX_GDSYMBOLWINDOW	32
#define	FR_CIDX_GDSYMBOLWINDOWACTIONPOINTOFFSET	33
#define	FR_CIDX_GDTSSTRANSMITTER	34
#define	FR_CIDX_GDWAKEUPRXIDLE	35
#define	FR_CIDX_GDWAKEUPRXLOW	36
#define	FR_CIDX_GDWAKEUPTXACTIVE	37
#define	FR_CIDX_GDWAKEUPTXIDLE	38
#define	FR_CIDX_PALLOWPASSIVETOACTIVE	39
#define	FR_CIDX_PCHANNELS 	40
#define	FR_CIDX_PCLUSTERDRIFTDAMPING	41
#define	FR_CIDX_PDECODINGCORRECTION	42
#define	FR_CIDX_PDELAYCOMPENSATIONA	43
#define	FR_CIDX_PDELAYCOMPENSATIONB	44
#define	FR_CIDX_PMACROINITIALOFFSETA	45
#define	FR_CIDX_PMACROINITIALOFFSETB	46
#define	FR_CIDX_PMICROINITIALOFFSETA	47
#define	FR_CIDX_PMICROINITIALOFFSETB	48
#define	FR_CIDX_PPAYLOADLENGTHDYNMAX	49
#define	FR_CIDX_PSAMPLESPERMICROTICK 	50
#define	FR_CIDX_PWAKEUPCHANNEL	51
#define	FR_CIDX_PWAKEUPPATTERN	52
#define	FR_CIDX_PDMICROTICK	53
#define	FR_CIDX_PDEXTERNRATECORRECTION	54
#define	FR_CIDX_PDEXTERNOFFSETCORRECTION	55
#define	FR_CIDX_GDIGNOREAFTERTX	56

#define	FR_CIDX_PALLOWHALTDUETOCLOCK 	57
#define	FR_CIDX_PEXTERNALSYNC	58
#define	FR_CIDX_PFALLBACKINTERNAL	59
#define	FR_CIDX_PKEYSLOTONLYENABLED	60
#define	FR_CIDX_PKEYSLOTUSEDFORSTARTUP	61
#define	FR_CIDX_PKEYSLOTUSEDFORSYNC	62
#define	FR_CIDX_PNMVECTOREARLYUPDATE	63
#define	FR_CIDX_PTWOKEYSLOTMODE	64

#define FRTRCV_TRCVMODE_UNKNOWN         (FrTrcv_TrcvModeType)0u

#define FRTRCV_TRCVMODE_NORMAL          (FrTrcv_TrcvModeType)1u

#define FRTRCV_TRCVMODE_STANDBY         (FrTrcv_TrcvModeType)2u

#define FRTRCV_TRCVMODE_SLEEP           (FrTrcv_TrcvModeType)3u

#define FRTRCV_TRCVMODE_RECEIVEONLY     (FrTrcv_TrcvModeType)4u
typedef uint8 FrTrcv_TrcvModeType;

#define FRTRCV_WU_NOT_SUPPORTED         (FrTrcv_TrcvWUReasonType)0u

#define FRTRCV_WU_BY_BUS                (FrTrcv_TrcvWUReasonType)1u

#define FRTRCV_WU_INTERNALLY            (FrTrcv_TrcvWUReasonType)2u

#define FRTRCV_WU_RESET                 (FrTrcv_TrcvWUReasonType)3u

#define FRTRCV_WU_POWER_ON              (FrTrcv_TrcvWUReasonType)4u

#define FRTRCV_WU_BY_PIN                (FrTrcv_TrcvWUReasonType)5u
typedef uint8 FrTrcv_TrcvWUReasonType;

#endif
