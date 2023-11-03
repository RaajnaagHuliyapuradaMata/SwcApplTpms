

#include "RTE_Stub_DcmServices.h"
#include "Rte_CtApHufTpmsSWC.h"
#include "RTE_Stub_JumpTableX.h"

static ImpTypeArrayDcm_RdcAnlernenLokalisierungLesenReadDataType aucPalData;
static ImpTypeRefDcm_NegativeResponseCodeType  ucPalError = RTE_E_INVALID;

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcLesen( ImpTypeArrayDcm_StatusRdcLesenReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusRdcLesen_ConditionCheckRead_090( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {

    (void) RDCi_ROpInvDcmStatusRdcLesen_ReadData_091( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcMessdatenblock1( ImpTypeArrayDcm_RdcMessdatenblock1ReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcMessdatenblock1_ConditionCheckRead_066( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {

    RDCi_ROpInvDcmRdcMessdatenblock1_ReadData_067( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcMessdatenblock2( ImpTypeArrayDcm_RdcMessdatenblock2ReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcMessdatenblock2_ConditionCheckRead_068( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcMessdatenblock2_ReadData_069( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcMessdatenblock3( ImpTypeArrayDcm_RdcMessdatenblock3ReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcMessdatenblock3_ConditionCheckRead_070( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcMessdatenblock3_ReadData_071( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcMessdatenblock4( ImpTypeArrayDcm_RdcMessdatenblock4ReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcMessdatenblock4_ConditionCheckRead_072( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcMessdatenblock4_ReadData_073( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcVersion( ImpTypeArrayDcm_StatusRdcVersionReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusRdcVersion_ConditionCheckRead_092( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmStatusRdcVersion_ReadData_093( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcAnlernenLokalisierungLesen( ImpTypeArrayDcm_RdcAnlernenLokalisierungLesenReadDataType* Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;
  uint8 ucLoop;
  uint8 *pucData = (uint8 *) Data;

  retVal = RDCi_ROpInvDcmRdcAnlernenLokalisierungLesen_ConditionCheckRead_044( Rte_Inst_CtApHufTpmsSWC, &error);
  ucPalError = error;

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcAnlernenLokalisierungLesen_ReadData_045( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);

    for( ucLoop = 0; ucLoop < sizeof(ImpTypeArrayDcm_RdcAnlernenLokalisierungLesenReadDataType); ucLoop++)
    {
      aucPalData[ucLoop] = *pucData++;
    }
  }else{
    ucPalError = RTE_E_INVALID;
  }

  return error;
}

uint8 *Stub_RdcAnlernenLokalisierungLesen_Output( uint8 ucIndex)
{

  if( (ucPalError == RTE_E_OK) && (ucIndex < 16))
  {
    return &aucPalData[ucIndex * 12];
  }else{
    return (uint8 *) NULL_PTR;
  }
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsInaktivereignis( ImpTypeArrayDcm_RdcHsInaktivereignisReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsInaktivereignis_ConditionCheckRead_048( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsInaktivereignis_ReadData_049( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsKalibrierereignis( ImpTypeArrayDcm_RdcHsKalibrierereignisReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsKalibrierereignis_ConditionCheckRead_050( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsKalibrierereignis_ReadData_051( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignisRuecknahme( ImpTypeArrayDcm_RdcHsWarnereignisRuecknahmeReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignisRuecknahme_ConditionCheckRead_058( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignisRuecknahme_ReadData_059( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignis1( ImpTypeArrayDcm_RdcHsWarnereignis1ReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignis1_ConditionCheckRead_052( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignis1_ReadData_053( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignis2( ImpTypeArrayDcm_RdcHsWarnereignis2ReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignis2_ConditionCheckRead_054( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignis2_ReadData_055( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignis3( ImpTypeArrayDcm_RdcHsWarnereignis3ReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignis3_ConditionCheckRead_056( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignis3_ReadData_057( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignisWeich1( ImpTypeArrayDcm_RdcHsWarnereignisWeich1ReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignisWeich1_ConditionCheckRead_060( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignisWeich1_ReadData_061( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignisWeich2( ImpTypeArrayDcm_RdcHsWarnereignisWeich2ReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignisWeich2_ConditionCheckRead_062( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignisWeich2_ReadData_063( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcHsWarnereignisWeich3( ImpTypeArrayDcm_RdcHsWarnereignisWeich3ReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcHsWarnereignisWeich3_ConditionCheckRead_064( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcHsWarnereignisWeich3_ReadData_065( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusReLesenDruckcodierung( ImpTypeArrayDcm_StatusReLesenDruckcodierungReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusReLesenDruckcodierung_ConditionCheckRead_094( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmStatusReLesenDruckcodierung_ReadData_095( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcDeveloperDataLesen( ImpTypeArrayDcm_StatusRdcDeveloperDataLesenReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusRdcDeveloperDataLesen_ConditionCheckRead_082( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmStatusRdcDeveloperDataLesen_ReadData_083( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcErfsAktReifenLesen( ImpTypeArrayDcm_StatusRdcErfsAktReifenLesenReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusRdcErfsAktReifenLesen_ConditionCheckRead_086( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmStatusRdcErfsAktReifenLesen_ReadData_087( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcErfsEcoTabelleLesen( ImpTypeArrayDcm_RdcErfsEcoTabelleLesenReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcErfsEcoTabelleLesen_ConditionCheckRead_046( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcErfsEcoTabelleLesen_ReadData_047( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcErfsAktReifenEcoLesen( ImpTypeArrayDcm_StatusRdcErfsAktReifenEcoLesenReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ConditionCheckRead_084( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmStatusRdcErfsAktReifenEcoLesen_ReadData_085( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_RdcRidAktReifenQrCodeLesen (ImpTypeArrayDcm_RdcRidAktReifenQrCodeLesenReadDataType * Data)
{
   ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcRidAktReifenQrCodeLesen_ConditionCheckRead_076( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcRidAktReifenQrCodeLesen_ReadData_077( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_RdcRidAlteReifenQrCodeLesen (ImpTypeArrayDcm_RdcRidAlteReifenQrCodeLesenReadDataType * Data)
{
   ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcRidAlteReifenQrCodeLesen_ConditionCheckRead_080( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcRidAlteReifenQrCodeLesen_ReadData_081( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_RdcRidAktReifenLaufstreckeLesen (ImpTypeArrayDcm_RdcRidAktReifenLaufstreckeLesenReadDataType * Data)
{
   ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ConditionCheckRead_074( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcRidAktReifenLaufstreckeLesen_ReadData_075( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_RdcRidAlteReifenLaufstreckeLesen (ImpTypeArrayDcm_RdcRidAlteReifenLaufstreckeLesenReadDataType * Data)
{
   ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ConditionCheckRead_078( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmRdcRidAlteReifenLaufstreckeLesen_ReadData_079( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_StatusRdcExtParkSupervisionLesen (ImpTypeArrayDcm_StatusRdcExtParkSupervisionLesenType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmStatusRdcExtParkSupervisionLesen_ConditionCheckRead_177( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmStatusRdcExtParkSupervisionLesen_ReadData_178( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernDigitalRdc( uint8 ucFunction, uint8 ucAction)
{
  ImpTypeArrayDcm_SteuernDigitalRdcWriteDataType data;
  ImpTypeRefDcm_NegativeResponseCodeType         error = RTE_E_OK;

	data[0] = ucFunction;
  data[1] = ucAction;

  RDCi_ROpInvDcmSteuernDigitalRdc_WriteData_096( Rte_Inst_CtApHufTpmsSWC, (uint8 *) &data, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernRadelektronikVorgeben( uint32 ulReID, uint8 ucRadPos)
{
  ImpTypeArrayDcm_SteuernRadelektronikVorgebenWriteDataType data;
  ImpTypeRefDcm_NegativeResponseCodeType                    error = RTE_E_OK;

  data[0] = (uint8) ((uint32) (ulReID >> 24) & 0x000000FF);
  data[1] = (uint8) ((uint32) (ulReID >> 16) & 0x000000FF);
  data[2] = (uint8) ((uint32) (ulReID >>  8) & 0x000000FF);
  data[3] = (uint8) ((uint32) (ulReID >>  0) & 0x000000FF);
  data[4] = ucRadPos;

  (void) RDCi_ROpInvDcmSteuernRadelektronikVorgeben_WriteData_097( Rte_Inst_CtApHufTpmsSWC, (uint8 *) &data, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernRdcErfsEcoReifentabelleVorgeben(void)
{
  ImpTypeArrayDcm_SteuernRdcErfsEcoReifentabelleVorgebenWriteDataType data;
  ImpTypeRefDcm_NegativeResponseCodeType                              error = RTE_E_OK;
  const ImpTypeRecCRdciErfsReifenEco * pTyreListPtr;
  uint8 i;
  ImpTypeRefDcm_OpStatusType OpStatus = 0;

  pTyreListPtr = Rte_Prm_RpCalPrmRDCi_CRdciErfsReifenEco( Rte_Inst_CtApHufTpmsSWC);

  for (i=0;i<160;i++)
  {
    data[i] = pTyreListPtr->DeData[i];
  }
  data[161] = (uint8)(pTyreListPtr->DeCrc & 0x00FF);
  data[160] = (uint8)((pTyreListPtr->DeCrc >> 8) & 0x00FF);

  (void) RDCi_ROpInvDcmSteuernRdcErfsEcoReifentabelleVorgeben_WriteData_102( Rte_Inst_CtApHufTpmsSWC, (uint8 *) &data, OpStatus, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernRdcErfsEcoNeueReifenVorgeben(void)
{
  ImpTypeArrayDcm_SteuernRdcErfsEcoNeueReifenVorgebenWriteDataType data;
  ImpTypeRefDcm_NegativeResponseCodeType                           error = RTE_E_OK;
  ImpTypeRefDcm_OpStatusType OpStatus = 0;

  data[0] = 0x02;
  data[1] = 0x68;
  data[2] = 0x4A;
  data[3] = 0x59;
  data[4] = 0x59;
  data[5] = 0x24;
  data[6] = 0x5A;
  data[7] = 0x36;
  data[8] = 0x6A;

  (void) RDCi_ROpInvDcmSteuernRdcErfsEcoNeueReifenVorgeben_WriteData_101( Rte_Inst_CtApHufTpmsSWC, (uint8 *) &data, OpStatus, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernRdcErfsEcoAktReifenPosVorgeben(void)
{
  ImpTypeArrayDcm_SteuernRdcErfsEcoAktReifenPosVorgebenWriteDataType data;
  ImpTypeRefDcm_NegativeResponseCodeType                             error = RTE_E_OK;

  data[0] = 0x02;
  data[1] = 0x83;
  data[2] = 0x20;
  data[3] = 0x7E;
  data[4] = 0x41;
  data[5] = 0x56;
  data[6] = 0x89;
  data[7] = 0x68;
  data[8] = 0x2B;

  (void) RDCi_ROpInvDcmSteuernRdcErfsEcoAktReifenPosVorgeben_WriteData_100( Rte_Inst_CtApHufTpmsSWC, (uint8 *) &data, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernRdcErfsDeveloperConfig(void)
{
  ImpTypeArrayDcm_SteuernRdcErfsDeveloperConfigWriteDataType data;
  ImpTypeRefDcm_NegativeResponseCodeType                     error = RTE_E_OK;

  (void) RDCi_ROpInvDcmSteuernRdcErfsDeveloperConfig_WriteData_099( Rte_Inst_CtApHufTpmsSWC, (uint8 *) &data, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_SteuernRdcDeveloperConfig( ImpTypeArrayDcm_SteuernRdcDeveloperConfigWriteDataType *data)
{

  ImpTypeRefDcm_NegativeResponseCodeType                 error = RTE_E_OK;

  (void) RDCi_ROpInvDcmSteuernRdcDeveloperConfig_WriteData_098( Rte_Inst_CtApHufTpmsSWC, (uint8 *) data, &error);

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_FunktionenReifendruckkontrolle_ReadData( ImpTypeValDcm_FunktionenReifendruckkontrolleReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagFunktionenReifendruckkontrolle_ConditionCheckRead_004( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagFunktionenReifendruckkontrolle_ReadData_005( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcAktuelleAussentemperatur_ReadData( ImpTypeValDcm_RdcAktuelleAussentemperaturReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcAktuelleAussentemperatur_ConditionCheckRead_006( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcAktuelleAussentemperatur_ReadData_007( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcAussendruck_ReadData( ImpTypeArrayDcm_RdcAussendruckReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcAussendruck_ConditionCheckRead_008( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcAussendruck_ReadData_009( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcInaktivStatus_ReadData( ImpTypeValDcm_RdcInaktivStatusReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcInaktivStatus_ConditionCheckRead_010( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcInaktivStatus_ReadData_011( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcKalibrierungStatus_ReadData( ImpTypeValDcm_RdcKalibrierungStatusReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcKalibrierungStatus_ConditionCheckRead_012( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcKalibrierungStatus_ReadData_013( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcKonfiguration_ReadData( ImpTypeValDcm_RdcKonfigurationReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcKonfiguration_ConditionCheckRead_014( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcKonfiguration_ReadData_015( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcPosition_ReadData( ImpTypeValDcm_RdcPositionReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcPosition_ConditionCheckRead_016( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcPosition_ReadData_017( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReferenzAussentemperatur_ReadData( ImpTypeValDcm_RdcReferenzAussentemperaturReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReferenzAussentemperatur_ConditionCheckRead_018( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReferenzAussentemperatur_ReadData_019( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifendruckHl_ReadData( ImpTypeArrayDcm_RdcReifendruckHlReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifendruckHl_ConditionCheckRead_020( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifendruckHl_ReadData_021( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifendruckHr_ReadData( ImpTypeArrayDcm_RdcReifendruckHrReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifendruckHr_ConditionCheckRead_022( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifendruckHr_ReadData_023( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifendruckVl_ReadData( ImpTypeArrayDcm_RdcReifendruckVlReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifendruckVl_ConditionCheckRead_024( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifendruckVl_ReadData_025( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifendruckVr_ReadData( ImpTypeArrayDcm_RdcReifendruckVrReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifendruckVr_ConditionCheckRead_026( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifendruckVr_ReadData_027( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifentemperaturHl_ReadData( ImpTypeValDcm_RdcReifentemperaturHlReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifentemperaturHl_ConditionCheckRead_028( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifentemperaturHl_ReadData_029( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifentemperaturHr_ReadData( ImpTypeValDcm_RdcReifentemperaturHrReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifentemperaturHr_ConditionCheckRead_030( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifentemperaturHr_ReadData_031( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifentemperaturVl_ReadData( ImpTypeValDcm_RdcReifentemperaturVlReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifentemperaturVl_ConditionCheckRead_032( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifentemperaturVl_ReadData_033( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcReifentemperaturVr_ReadData( ImpTypeValDcm_RdcReifentemperaturVrReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcReifentemperaturVr_ConditionCheckRead_034( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcReifentemperaturVr_ReadData_035( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcSensorHersteller_ReadData( ImpTypeValDcm_RdcSensorHerstellerReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcSensorHersteller_ConditionCheckRead_036( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcSensorHersteller_ReadData_037( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcSolldruckHinten_ReadData( ImpTypeArrayDcm_RdcSolldruckHintenReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcSolldruckHinten_ConditionCheckRead_038( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcSolldruckHinten_ReadData_039( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcSolldruckVorn_ReadData( ImpTypeArrayDcm_RdcSolldruckVornReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcSolldruckVorn_ConditionCheckRead_040( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcSolldruckVorn_ReadData_041( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

ImpTypeRefDcm_NegativeResponseCodeType RTE_Stub_UWB_RdcStatus_ReadData( ImpTypeValDcm_RdcStatusReadDataType * Data)
{
  ImpTypeRefDcm_NegativeResponseCodeType error;
  Std_ReturnType retVal;

  retVal = RDCi_ROpInvDcmDiagRdcStatus_ConditionCheckRead_042( Rte_Inst_CtApHufTpmsSWC, &error);

  if( retVal == RTE_E_OK)
  {
    (void) RDCi_ROpInvDcmDiagRdcStatus_ReadData_043( Rte_Inst_CtApHufTpmsSWC, (uint8 *) Data);
  }

  return error;
}

