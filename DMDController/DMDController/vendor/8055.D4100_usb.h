#define DLL_EXPORT

#if defined DLL_EXPORT
#define USB_DLL __declspec(dllexport)
#else
#define USB_DLL __declspec(dllimport)
#endif

#undef UNICODE //Use multi-byte character set


#include <windows.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "stdarg.h"
#include "RegisterDefines.h"


extern "C"
{
	namespace USB {
		USB_DLL short int GetNumDev();
		USB_DLL int GetDescriptor(int* Array, short int DeviceNum);
		USB_DLL unsigned int GetFirmwareRev(short int DeviceNumber);
		USB_DLL unsigned int GetDriverRev(short int DeviceNumber);
		USB_DLL long GetDLLRev();
		USB_DLL short int GetUsbSpeed(short int DeviceNumber);
		USB_DLL int program_FPGA(UCHAR *write_buffer, LONG write_size, short int DeviceNumber);

		USB_DLL short LoadControl(short DeviceNumber);
		USB_DLL short ClearFifos(short DeviceNumber);
		USB_DLL int LoadData(UCHAR* RowData, long length, short DMDType, short DeviceNumber);
		USB_DLL short SetBlkMd(short value, short DeviceNumber);
		USB_DLL short GetBlkMd(short DeviceNumber);
		USB_DLL short SetBlkAd(short value, short DeviceNumber);
		USB_DLL short GetBlkAd(short DeviceNumber);
		USB_DLL short SetRST2BLKZ(short value, short DeviceNumber);
		USB_DLL short GetRST2BLKZ(short DeviceNumber);
		USB_DLL short SetRowMd(short value, short DeviceNumber);
		USB_DLL short GetRowMd(short DeviceNumber);
		USB_DLL short SetRowAddr(short value, short DeviceNumber);
		USB_DLL short GetRowAddr(short DeviceNumber);
		USB_DLL short SetSTEPVCC(short value, short DeviceNumber);
		USB_DLL short GetSTEPVCC(short DeviceNumber);
		USB_DLL short SetCOMPDATA(short value, short DeviceNumber);
		USB_DLL short GetCOMPDATA(short DeviceNumber);
		USB_DLL short SetNSFLIP(short value, short DeviceNumber);
		USB_DLL short GetNSFLIP(short DeviceNumber);
		USB_DLL short SetWDT(short value, short DeviceNumber);
		USB_DLL short GetWDT(short DeviceNumber);
		USB_DLL short SetPWRFLOAT(short value, short DeviceNumber);
		USB_DLL short GetPWRFLOAT(short DeviceNumber);
		USB_DLL short SetEXTRESETENBL(short value, short DeviceNumber);
		USB_DLL short GetEXTRESETENBL(short DeviceNumber);
		USB_DLL short SetGPIO(short value, short DeviceNumber);
		USB_DLL short GetGPIO(short DeviceNumber);
		USB_DLL short GetDMDTYPE(short DeviceNumber);
		USB_DLL short GetDDCVERSION(short DeviceNumber);

		USB_DLL unsigned int GetFPGARev(short int DeviceNumber);
		USB_DLL short GetRESETCOMPLETE(int waittime, short int DeviceNumber);
		USB_DLL short SetGPIORESETCOMPLETE(short int DeviceNumber);

		USB_DLL short GetTPGEnable(short int DeviceNumber);
		USB_DLL short SetTPGEnable(short value, short int DeviceNumber);

		USB_DLL short GetSWOverrideEnable(short int DeviceNumber);
		USB_DLL short SetSWOverrideEnable(short value, short int DeviceNumber);

		USB_DLL short GetPatternForce(short int DeviceNumber);
		USB_DLL short SetPatternForce(short value, short int DeviceNumber);

		USB_DLL short GetSWOverrideValue(short int DeviceNumber);
		USB_DLL short SetSWOverrideValue(short value, short int DeviceNumber);

		USB_DLL short GetPatternSelect(short int DeviceNumber);
		USB_DLL short SetPatternSelect(short value, short int DeviceNumber);

		USB_DLL short SetLoad4(short value, short DeviceNumber);
		USB_DLL short GetLoad4(short DeviceNumber);

        USB_DLL int RegisterWrite(unsigned short regAddress, unsigned short data, short devNumber);
        USB_DLL int RegisterRead(unsigned short int regAddress, short devNumber);

        USB_DLL short RegisterWriteBit(unsigned short regAddress, unsigned short mask, unsigned short value, short devNumber);
        USB_DLL short RegisterReadBit(unsigned short regAddress, unsigned short mask, short devNumber);
	}
}