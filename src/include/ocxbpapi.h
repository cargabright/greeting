/*****************************************************************************
*
*   Title:        56SAM CIP API Definitions
*
*   Abstract:     This file contains definitions and declarations
*                 needed for developing applications which use the
*                 56SAM CIP API.
*
*   Environment:  56SAM Module
*                 Windows / CE / QNX / Linux
*                 Visual C++ / eVC++ / gcc
*
*                 Copyright (c) 1999-2016 Online Development, Inc.
*
*****************************************************************************/

#ifndef _OCXCIPAPI_H
#define _OCXCIPAPI_H

#if defined(__linux__)
#include    <time.h>
#include	<stdint.h>
#elif defined(__QNX__)
#else  //__linux__
#include    <windows.h>
#endif //__linux__


/**************************************
** Windows to Linux Type Translations
***************************************/
#ifdef __linux__
#define HANDLE  int
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int ULONG;
typedef int LONG;
typedef unsigned int DWORD;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef long long LARGE_INTEGER;
typedef unsigned long long ULONGLONG;
typedef union _ULARGE_INTEGER {
    struct {
        DWORD LowPart;
        DWORD HighPart;
    };
    struct {
        DWORD LowPart;
        DWORD HighPart;
    } u;
    ULONGLONG QuadPart;
} ULARGE_INTEGER;
#endif //__linux__

#ifdef __QNX__
#define HANDLE  int
typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned long ULONG;
typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned long DWORD;
#endif //__QNX__

/***********************************
**      TYPE DEFINITIONS
************************************/
typedef ULONG       OCXHANDLE;          // API handle
typedef ULONG       TAGHANDLE;          // Tag handle


/************************************
**    API FUNCTION RETURN CODES
*************************************/
#define OCX_SUCCESS                 0   // Function returned successfully
#define OCX_ERR_BADPARAM            1   // A parameter is invalid
#define OCX_ERR_REOPEN              2   // Device is already open
#define OCX_ERR_NODEVICE            3   // Device is not present
#define OCX_ERR_NOACCESS            4   // Invalid access
#define OCX_ERR_TIMEOUT             5   // The function has timed out
#define OCX_ERR_MSGTOOBIG           6   // The message is too large
#define OCX_ERR_BADCONFIG           7   // The IO is not configured properly
#define OCX_ERR_MEMALLOC            8   // Unable to allocate memory
#define OCX_ERR_NOTSUPPORTED        9   // Function is not supported on this platform
#define OCX_ERR_ALREADY_REGISTERED 10   // Object is already registered
#define OCX_ERR_INVALID_OBJHANDLE  11   // Object handle is not valid
#define OCX_ERR_NODATA             12   // No data has been received on this connection yet
#define OCX_ERR_INVALID            13   // Invalid function for current state or configuration
#define OCX_ERR_BUSY               14   // Device is busy - retry function
#define OCX_ERR_REINIT             15   // Failed because already initialized
#define OCX_ERR_NOINIT             16   // Failed because not initialized
#define OCX_ERR_DATAOVFL           17   // Data overflow
#define OCX_ERR_DATAUVFL           18   // Data underflow
#define OCX_ERR_DATAINCONSIST      19   // Inconsistent data error
#define OCX_ERR_VERMISMATCH        20   // Version mismatch
#define OCX_ERR_OBJEMPTY           21   // Object empty
#define OCX_ERR_PCCC               22   // PCCC error
#define OCX_ERR_RESET_REFUSED      23   // Application is refusing the ID reset request
#define OCX_ERR_RESET_APP_GEN      24   // Application will reset when it is ready
#define OCX_ERR_REQUEST_ID_LEN     25   // Requestor ID length error
#define OCX_ERR_VENDOR_ID          26   // Vendor ID mismatch
#define OCX_ERR_SERIAL_NUM         27   // Serial number mismatch
#define OCX_ERR_COMMAND_BYTE       28   // Command byte mismatch
#define OCX_ERR_TNSW               29   // TNSW mismatch
#define OCX_ERR_LOCAL_STS          30   // Local STS error indicated
#define OCX_ERR_RESET_SUCCESS      31   // Application will handle the reset request, return success
#define OCX_ERR_REMOTE_STS_OFFSET  100  // This offset is added to the remote status error codes to produce a raw code.
										// This offset plus the remote error code can never exceed 114.
#define OCX_ERR_REMOTE_EXTSTS_OFFSET  115  // This offset is added to the remote extended status error codes to produce a raw code.
										// This offset plus the remote extended error code must never exceed 255.

/*  Below is an explanation of the status byte(s) which can be returned in a PCCC packet
STS BYTE
There is the STS byte, which has two portions to it, and there is the EXT STS byte, which appears in some commands.
These lists are	handled separately. It should be noted that the EXT STS byte will not exist if the STS byte is zero in a response.
The STS byte is divided into two portions, the local and remote nibbles.

STS Local Errors (lower nibble of STS BYTE) - the cATM will handle these with a single error code - OCX_ERR_LOCAL_STS
STS Remote Errors (upper nibble of STS BYTE)
The remote error nibble is used to indicate errors that the responder finds. It is contained in the four most
significant bits of the STS byte and has the following encoding (in hexadecimal):
00 - Success, no error.
10 - Illegal command or format.
20 - Host has a problem and will not communicate.
30 - Remote station host is not there, disconnected, or shutdown.
40 - Host could not complete function due to hardware fault.
50 - Addressing problem or memory protect rungs.
60 - Function disallowed due to command protection selection.
70 - Processor is in program mode.
80 - Compatibility mode file missing or communication zone problem.
90 - Remote station cannot buffer command.
A0 - not used.
B0 - station problem, due to download.
C0 - Cannot execute command, due to active IPB�s.
D0 - Cannot route request.
E0 - not used.
F0 - Indicates that there is an error encoded in the EXT STS byte.

The EXT STS byte has the following encoding (in hexadecimal) for CMD byte = 0FH:
00- Not used.
01 - Illegal Address Format - a field has an illegal value.
02 - Illegal Address Format - not enough fields specified.
03 - Illegal Address Format - too many fields specified.
04 - Illegal Address - symbol not found.
05 - Illegal Address Format - symbol is 0 or greater than the maximum number of characters supported by this device.
06 - Illegal Address - address does not exist, or does not point to something usable by this command.
07 - Illegal size; file is wrong size; address is past end of file
08 - Cannot complete request, situation changed (file size, for example) during multipacket operation.
09 - Data or file is too large. Memory unavailable
0A - Request is too large; transaction size plus word address is too large
0B - Access denied, privilege violation.
0C - Resource is not available; condition cannot be generated
0D - Resource is already available; condition already exists
0E - Command cannot be executed.
0F - Overflow; histogram overflow
10 - No access.
11 - Illegal data type information.
12 - Invalid parameter; invalid data in search or command block
13 - Address reference exists to deleted area
14 - Command execution failure for unknown reason; PLC-3 histogram overflow
15 - Data conversion error
16 - The scanner is not able to communicate with a 1771 rack adapter. This could be due to the scanner not
	scanning, the selected adapter not being scanned, the adapter not responding, or an invalid request of a
	"DCM BT"
17 - The adapter is not able to communicate with the module.
18 - The 1771 module response was not valid: size, checksum, etc.
19 - Duplicated Label
1A - File is open - another station owns it
1B - Another station is the program owner
1C - Disk file is write protected or otherwise unaccessable (off-line only)
1D - Disk file is being used by another application, update not performed (off-line only)
1E - Data Table Element Protection violation
1F - Unable to execute command due to a temporary internal condition
Codes 20-FF are not used.
*/


/************************************
**    USER LED DEFINITIONS
**
**    These values are passed to the
**    OCXcip_SetUserLED function.
*************************************/
#define OCX_LED_STATE_OFF    0           // LED is OFF
#define OCX_LED_STATE_GREEN  1           // LED is GREEN
#define OCX_LED_STATE_RED    2           // LED is RED
#define OCX_LED_STATE_YELLOW 3			 // LED is YELLOW

/************************************
**    3-POSITION SWITCH DEFINITIONS
**
**    These values are returned from
**    OCXcip_GetSwitchPosition.
*************************************/
#define OCX_SWITCH_TOP      1           // Switch is in top position
#define OCX_SWITCH_BOTTOM   2           // Switch is in bottom position
#define OCX_SWITCH_MIDDLE   3           // Switch is in middle position

/************************************
**    MODULE STATUS DEFINITIONS
**
**    These values are passed to the
**    OCXcip_SetModuleStatus function.
*************************************/
#define OCX_MODULE_STATUS_OK        0   // Module is OK (status LED green)
#define OCX_MODULE_STATUS_FAULTED   1   // Module is faulted (status LED red)
#define OCX_MODULE_STATUS_FLASHING  2   // Blink module status LED (red/green)

/************************************
**    API CALLBACK REASON
**
**    These values are passed to the
**    connect_proc callback function.
*************************************/
#define OCX_CIP_CONN_OPEN           0   // Request to an open connection
#define OCX_CIP_CONN_CLOSE          1   // Request to close a connection
#define OCX_CIP_CONN_OPEN_COMPLETE  2   // Request to open a connection has completed
#define OCX_CIP_CONN_NULLOPEN       3   // NULL forward open request received
 /* Originator codes */
#define OCX_CIP_CONN_CLOSE_ORIG     4   // Request to close a connection

/************************************
**    API CALLBACK SERVICE CODES
**
**    These values are passed to the
**    service_proc callback function.
*************************************/
#define OCX_CIP_SC_GET_ATTR_SINGLE      0x0E
#define OCX_CIP_SC_SET_ATTR_SINGLE      0x10
#define OCX_CIP_SC_GET_MEMBER           0x18
#define OCX_CIP_SC_SET_MEMBER           0x19
#define OCX_CIP_SC_GENERIC_RW           0x35

/************************************
**    API CALLBACK INSTANCE ATTRIBUTES
**
**    These values are passed to the
**    service_proc callback function.
*************************************/
#define OCX_CIP_IA_NUM_MEMBERS 0x01  // Number of members in dynamic asy
#define OCX_CIP_IA_MEMBER_LIST 0x02  // Member list for dynamic asy
#define OCX_CIP_IA_DATA        0x03  // Data (as bytes)
#define OCX_CIP_IA_SIZE        0x04  // Size of data (in bytes)

/************************************
**    API CALLBACK RETURN CODES
**
**    These values are returned by the
**    connect_proc and service_proc
**    callback functions.
*************************************/
#define OCX_CIP_FAILURE            0x01  // Connection Failure
#define OCX_CIP_NO_RESOURCE        0x02  // No more resources
#define OCX_CIP_BAD_PATH           0x04  // Invalid Path segemnt
#define OCX_CIP_BAD_INSTANCE       0x05  // Invalid Class Instance
#define OCX_CIP_PARTIAL_DATA       0x06  // Invalid data size
#define OCX_CIP_BAD_SERVICE        0x08  // Invalid service code
#define OCX_CIP_BAD_ATTR_DATA      0x09  // Invalid attribute data
#define OCX_CIP_ATTR_NOT_SETTABLE  0x0e  // Attribute cannot be set
#define OCX_CIP_DEVICE_BUSY        0x10  // The device application is not
                                         //  able to respond to the service requeset
#define OCX_CIP_BAD_COMMAND_DATA   0x13  // Insufficient command data: command too
										 //  short for expected parameters
#define OCX_CIP_BAD_ATTR           0x14  // Invalid attribute
#define OCX_CIP_DATA_TOO_BIG       0x15  // Data size is too large
#define OCX_CIP_DEFER_RESPONSE     0x81  // Defer message response until call to OCXcip_MsgResponse

/*****************************************
**    API CALLBACK EXTENDED ERROR CODES
**
**    These values may be returned by
**    the connect_proc callback function.
******************************************/
#define OCX_CIP_EX_CONNECTION_USED 0x100 // Connection already being used
#define OCX_CIP_EX_BAD_SIZE        0x109 // Invalid size
#define OCX_CIP_EX_NO_CNTRL_CONN   0x119 // No controlling connection is open
#define OCX_CIP_EX_BAD_RPI         0x111 // Unsupportable requested packet interval

/*****************************************
**    API DATA TABLE RETURN CODES
**    These values are returned by the
**    OCXcip_DataTableRead and
**    OCXcip_DataTableWrite functions.
******************************************/
#define OCX_CIP_INVALID_TAG        50   // Invalid Tag name specified
#define OCX_CIP_INSUFF_PKT_SPACE   51   // Insufficient packet space for response data
#define OCX_CIP_INVALID_REQUEST    52   // The data table request was invalid
#define OCX_CIP_DATATYPE_MISMATCH  53   // Data type in request doesn't match response type
#define OCX_CIP_GENERAL_ERROR      54   // General Error associated with unconnected message
#define OCX_CIP_MEMBER_UNDEFINED   55   // Destination unknown, class unsupported, instance
                                        // undefined or structure element undefined
#define OCX_CIP_ACCESS_PAST_END    56   // Tried to access past the end of the data object
#define OCX_CIP_UCMM_TIMEOUT       57

/*****************************************
** API DATA TABLE data types.
**    These are passed as data types in
**    the OCXcip_DataTableRead and
**    OCXcip_DataTableWrite functions.
******************************************/
#define OCX_CIP_BOOL               0xC1 // Logical Boolean with values True and False
#define OCX_CIP_SINT               0xC2 // Signed 8-bit integer
#define OCX_CIP_INT                0xC3 // Signed 16-bit integer
#define OCX_CIP_DINT               0xC4 // Signed 32-bit integer
#define OCX_CIP_LINT               0xC5 // Signed 64-bit integer
#define OCX_CIP_USINT              0xC6 // Unsigned 8-bit integer
#define OCX_CIP_UINT               0xC7 // Unsigned 16-bit integer
#define OCX_CIP_UDINT              0xC8 // Unsigned 32-bit integer
#define OCX_CIP_ULINT              0xC9 // Unsigned 64-bit integer
#define OCX_CIP_REAL               0xCA // 32-bit floating point value
#define OCX_CIP_LREAL              0xCB // 64-bit floating point value
#define OCX_CIP_BYTE               0xD1 // bit string, 8-bits
#define OCX_CIP_WORD               0xD2 // bit string, 16-bits
#define OCX_CIP_DWORD              0xD3 // bit string, 32-bits
#define OCX_CIP_LWORD              0xD4 // bit string, 64-bits
#define OCX_CIP_STRING82         0x0FCE // OCX_CIP_STRING82_TYPE

/*****************************************
** API DATA TABLE data access types.
**    These are passed in the
**    OCXcip_TagDefine function.
******************************************/
#define OCX_ACCESS_TYPE_READ_ONLY  0x00 // Tag access type read only
#define OCX_ACCESS_TYPE_RDWR       0x01 // Tag access type read/write

/*****************************************
** API Device Id Status Read bit masks.
**    These are used to mask the status
**    word returned by the
**    OCXcip_GetDeviceIdStatus function.
******************************************/
#define OCX_ID_STATUS_DEVICE_STATUS_MASK 0x00F0
#define OCX_ID_STATUS_FLASHUPDATE        0x0010  // Flash update in progress
#define OCX_ID_STATUS_FLASHBAD           0x0040  // Flash is bad
#define OCX_ID_STATUS_FAULTED            0x0050  // Faulted
#define OCX_ID_STATUS_RUN                0x0060  // Run mode
#define OCX_ID_STATUS_PROGRAM            0x0070  // Program mode

#define OCX_ID_STATUS_FAULT_STATUS_MASK  0x0F00
#define OCX_ID_STATUS_RCV_MINOR_FAULT    0x0100  // Recoverable minor fault
#define OCX_ID_STATUS_URCV_MINOR_FAULT   0x0200  // Unrecoverable minor fault
#define OCX_ID_STATUS_RCV_MAJOR_FAULT    0x0400  // Recoverable major fault
#define OCX_ID_STATUS_URCV_MAJOR_FAULT   0x0800  // Unrecoverable major fault

// The key and controller mode bits are 555x specific
#define OCX_ID_STATUS_KEY_SWITCH_MASK    0x3000  // Key switch position mask
#define OCX_ID_STATUS_KEY_RUN            0x1000  // Keyswitch in run
#define OCX_ID_STATUS_KEY_PROGRAM        0x2000  // Keyswitch in program
#define OCX_ID_STATUS_KEY_REMOTE         0x3000  // Keyswitch in remote

#define OCX_ID_STATUS_CNTR_MODE_MASK     0xC000  // Controller mode bit mask
#define OCX_ID_STATUS_MODE_CHANGING      0x4000  // Controller is changing modes
#define OCX_ID_STATUS_DEBUG_MODE         0x8000  // Debug mode if controller is in Run mode


/*****************************************
** Module Status Word Definitions
**
**  Bit masks and bit definitions for
**  the module status word set by the
**  OCXcip_SetModuleStatusWord function.
******************************************/
// General status
#define OCX_MOD_STATUS_OWNED_MASK                0x0001
#define OCX_MOD_STATUS_OWNED                     0x0001
#define OCX_MOD_STATUS_UNOWNED                   0x0000

#define OCX_MOD_STATUS_CONFIGURED_MASK           0x0004
#define OCX_MOD_STATUS_CONFIGURED                0x0004
#define OCX_MOD_STATUS_UNCONFIGURED              0x0000

// Device state
#define OCX_MOD_STATUS_STATE_MASK                0x00F0
#define OCX_MOD_STATUS_SELF_TESTING              0x0000
#define OCX_MOD_STATUS_NVS_UPDATE                0x0010
#define OCX_MOD_STATUS_COMM_FAULT                0x0020
#define OCX_MOD_STATUS_AWAIT_CONN                0x0030
#define OCX_MOD_STATUS_NVS_BAD_CONFIG            0x0040
#define OCX_MOD_STATUS_MAJOR_FAULT               0x0050
#define OCX_MOD_STATUS_CONNECTED                 0x0060
#define OCX_MOD_STATUS_IDLE                      0x0070

// Faults
#define OCX_MOD_STATUS_FAULT_MASK                0x0F00
#define OCX_MOD_STATUS_MINOR_RECOVERABLE_FAULT   0x0100
#define OCX_MOD_STATUS_MINOR_UNRECOVERABLE_FAULT 0x0200
#define OCX_MOD_STATUS_MAJOR_RECOVERABLE_FAULT   0x0400
#define OCX_MOD_STATUS_MAJOR_UNRECOVERABLE_FAULT 0x0800


/*****************************************
** Abort codes for
** OCXcip_AccessTagDataAbortable
******************************************/
#define OCX_ABORT_TAG_ACCESS_MINOR  1   // Abort between tag accesses
#define OCX_ABORT_TAG_ACCESS_MAJOR  2   // Abort between CIP packets


/****************************************
**    SERIAL PORT CONFIGURATION
**
**    These values are returned from the
**    OCXcip_GetSerialConfig function,
**    and passed to the
**    OCXcip_SetSerialConfig function.
**    (These functions are not supported
**    on all platforms.)
*****************************************/
#define SAM_SERIAL_CONFIG_NONE      0   // No jumper is installed (use default/SW config)
#define SAM_SERIAL_CONFIG_RS232     1   // Port is configured for RS-232
#define SAM_SERIAL_CONFIG_RS422     2   // Port is configured for RS-422
#define SAM_SERIAL_CONFIG_RS485     4   // Port is configured for RS-485


/*****************************************
** Valid Timer ID values for
** OCXcip_ReadTimer
******************************************/
#define OCX_TIMERID_0       0           // 32-bit 1us timer
#define OCX_TIMERID_1       1           // 16-bit 1us timer (lower overhead access than 0)


/*****************************************
** Application Reset callback type codes
** OCXcip_RegisterResetParamReqRtn callback
******************************************/
#define OCX_RESET_REQ_TYPE_RESET                    0   // Module reset has been requested
#define OCX_RESET_REQ_TYPE_FACTORY_DEFAULTS         1   // Application should return to factory default state
#define OCX_RESET_REQ_TYPE_FACTORY_DEFAULTS_NO_COMM 2   // Application should return to factory default state,
                                                        //   but don't reset the communication settings.
#define OCX_RESET_REQ_RESET_SECURITY                100 // Application should reset it's security settings


/*****************************************
** Shutdown Type request codes for
** OCXcip_RegisterShutdownReqRtn callback
******************************************/
#define OCX_SHUTDOWN_REQ_TYPE_SHUTDOWN        0 // Application is being told to shutdown
#define OCX_SHUTDOWN_REQ_TYPE_STATUS          1 // Application should return shutdown status


/*****************************************
** Shutdown Status Response codes for
** OCXcip_RegisterShutdownReqRtn callback
** response status
******************************************/
#define OCX_SHUTDOWN_REQ_STATUS_COMPLETE      0 // Application shutdown is complete
#define OCX_SHUTDOWN_REQ_STATUS_IN_PROGRESS   1 // Application shutdown is in progress
#define OCX_SHUTDOWN_REQ_STATUS_NOT_INITIATED 2 // Application shutdown has not been initiated


/*****************************************
** Reset Button Event type definitions
** for OCXcip_RegisterResetButtonRtn callback
******************************************/
#define OCX_RESET_BUTTON_NOEVENT    0
#define OCX_RESET_BUTTON_PRESSED    1
#define OCX_RESET_BUTTON_RELEASED   2

/*****************************************
** Connection size selections for
** OCXcip_SetTagAccessConnSize
******************************************/
#define OCX_TAGACC_CONNSIZE_SM		1
#define OCX_TAGACC_CONNSIZE_MED		2
#define OCX_TAGACC_CONNSIZE_LG		3


/* ************************************ */
/* **    STRUCTURES                  ** */
/* ************************************ */

//
// Note: The original API libraries for Windows used byte-aligned structures.  
// This has been deprecated in favor of default 32-bit alignment, which is more 
// compatible with VB and other languages.  Older applications using the old 
// byte-aligned libraries should be recompiled.
//

/************************************************************
* Structure Name: OCXCIPVERSIONINFO
*
* Description:
*
*   Returned by OCXcip_GetVersionInfo().
*   API version numbers.
*
*************************************************************/
typedef struct tagOCXCIPVERSIONINFO
{
    WORD        APISeries;     // API series
    WORD        APIRevision;   // API revision
    WORD        BPEngSeries;   // Backplane engine series
    WORD        BPEngRevision; // Backplane engine revision
    WORD        BPDDSeries;    // Backplane driver series
    WORD        BPDDRevision;  // Backplane driver revision
} OCXCIPVERSIONINFO;

/************************************************************
* Structure Name: OCXCIPIDOBJ
*
* Description:
*
*   Returned by OCXcip_GetIdObject().
*
*************************************************************/
typedef struct tagOCXCIPIDOBJ
{
    WORD    VendorID;           // Vendor identification
    WORD    DeviceType;         // Device type code
    WORD    ProductCode;        // Device model code
    BYTE    MajorRevision;      // Module major revision
    BYTE    MinorRevision;      // Module minor revision
    DWORD   SerialNo;           // Serial number
    BYTE    Name[32];           // Device name (string)
    BYTE    Slot;               // Slot number
} OCXCIPIDOBJ;

/************************************************************
* Structure Name: OCXCIPICPOBJ
*
* Description:
*
*   Returned by OCXcip_GetICPObject().
*
*************************************************************/
typedef struct tagOCXCIPICPOBJ
{
   BYTE    RxBadMulticastCrcCounter;    // Number of multicast Rx CRC errors
   BYTE    MulticastCrcErrorThreshold;  // Threshold for entering fault state due to multicast CRC errors
   BYTE    RxBadCrcCounter;             // Number of CRC errors that occurred on Rx
   BYTE    RxBusTimeoutCounter;         // Number of Rx bus timeouts
   BYTE    TxBadCrcCounter;             // Number of CRC errors that occurred on Tx
   BYTE    TxBusTimeoutCounter;         // Number of Tx bus timeouts
   BYTE    TxRetryLimit;                // Number of times a Tx is retried if an error occurs
   BYTE    Status;                      // ControlBus status
   WORD    ModuleAddress;               // Module's slot number
   BYTE    RackMajorRev;                // Chassis major revision
   BYTE    RackMinorRev;                // Chassis minor revision
   DWORD   RackSerialNumber;            // Chassis serial number
   WORD    RackSize;                    // Chassis size (number of slots)
} OCXCIPICPOBJ;

/************************************************************
* Structure Name: OCXCIPCONNSTRUC
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the connect_proc callback routine.
*
*************************************************************/
typedef struct tagOCXCIPCONNSTRUC
{
    OCXHANDLE   connHandle;     // unique value which identifies this connection
    void        *reg_param;     // value passed via OCXcip_RegisterAssemblyObj
    WORD        reason;         // specifies reason for callback
    WORD        instance;       // instance specified in open
    WORD        producerCP;     // producer connection point specified in open
    WORD        consumerCP;     // consumer connection point specified in open
    DWORD       *lOTApi;        // pointer to originator to target actual packet interval
    DWORD       *lTOApi;        // pointer to target to originator packet interval
    DWORD       lODeviceSn;     // Serial number of the originator
    WORD        iOVendorId;     // Vendor Id of the originator
    WORD        rxDataSize;     // size in bytes of receive data
    WORD        txDataSize;     // size in bytes of transmit data
    BYTE        *configData;    // pointer to configuration data sent in open
    WORD        configSize;     // size of configuration data sent in open
    WORD        *extendederr;   // Contains an extended error code if an error occurs
} OCXCIPCONNSTRUC;

/************************************************************
* Structure Name: OCXCIPSERVSTRUC
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the service_proc callback routine.
*
*************************************************************/
typedef struct tagOCXCIPSERVSTRUC
{
    void        *reg_param;     // value passed via OCXcip_RegisterAssemblyObj
    WORD        instance;       // instance number of object being accessed
    BYTE        serviceCode;    // service being requested
    WORD        attribute;      // attribute being accessed
    BYTE        **msgBuf;       // pointer to pointer to message data
    WORD        offset;         // member offset
    WORD        *msgSize;       // pointer to size in bytes of message data
    WORD        *extendederr;   // Contains an extended error code if an error occurs
    BYTE        fromSlot;       // Slot number in local rack from which message was
                                //  received (may not be originator if via bridge)
    void       *msgHandle;      // only needed if response is deferred (see OCXcip_MsgResponse)
} OCXCIPSERVSTRUC;

/************************************************************
* Structure Name: OCXCIPRECVSTRUC
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the rxdata_proc callback routine.
*
*************************************************************/
typedef struct tagOCXCIPRECVSTRUC
{
    void        *reg_param;     // value passed via OCXcip_RegisterAssemblyObj
    OCXHANDLE   connHandle;     // unique value which identifies this connection
    BYTE        *rxData;        // pointer to buffer of received data
    WORD        dataSize;       // size of received data in bytes
} OCXCIPRECVSTRUC;

/************************************************************
* Structure Name: OCXTAGDEFSTRUC
*
* Description:
*
*   Tag definition structure.
*
*************************************************************/
typedef struct tagOCXTAGDEFSTRUC
{
    BYTE *pName;
    WORD  data_type;
    WORD  size;
    WORD  access_type;
    BYTE *pPath;
    WORD  timeout;
} OCXTAGDEFSTRUC;

/************************************************************
* Structure Name: OCXBPIACONNINFO
*
* NOTE: This structure is only used by backplane interface
* agent clients.
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the OCXcip_Open routine.
*
*************************************************************/
typedef struct tagOCXBPIACONNINFO
{
    char *server_name;
} OCXBPIACONNINFO;

/************************************************************
* Structure Name: SYSTEMTIME
*
* Description:
*
*   This structure is equivalent to the Win32 SYSTEMTIME
*   structure.  It is included for Linux-based systems.
*   See the OCXCIPWCT structure.
*
*************************************************************/
#ifdef __linux__
typedef struct _SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;        // Sunday = 0, Monday = 1, etc.
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME;
#endif //__linux__

/************************************************************
* Structure Name: OCXCIPWCT
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the OCXcip_GetWCTime function.  It is used to read/set
*   the local Wall Clock Time information from a device.
*
*************************************************************/
#ifndef __QNX__
typedef struct tagOCXCIPWCT
{
    ULARGE_INTEGER CurrentValue;       // 64-bit local wall clock time (read only; microsecs since 1/1/1972)
    WORD           TimeZone;           // not used / obsolete
    ULARGE_INTEGER CSTOffset;          // Positive offset from the CST (read only; microsecs)
    WORD           LocalTimeAdj;       // not used / obsolete
    SYSTEMTIME     SystemTime;         // WCT local time converted to Win32 system time format
} OCXCIPWCT;
#endif

/************************************************************
* Structure Name: OCXCIPWCTUTC
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the OCXcip_GetWCTimeUTC function.  It is used to read/set
*   the Wall Clock Time information from a device.
*
*************************************************************/
#ifndef __QNX__
typedef struct tagOCXCIPWCTUTC
{
    ULARGE_INTEGER CurrentUTCValue;    // 64-bit local UTC wall clock time (read only; microsecs since 1/1/1970)
    char           TimeZone[84];       // Time zone string as GMT +/-hh:mm <location>
    int            DSTOffset;          // minute adjustment for DST
    int            DSTEnable;          // True if DST is in effect
    SYSTEMTIME     SystemTime;         // WCT UTC time converted to Win32 system time format
} OCXCIPWCTUTC;
#endif


/************************************************************
* Structure Name: OCXCIPTAGACCESS
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the OCXcip_AccessTagData function.
*
*************************************************************/
typedef struct tagOCXCIPTAGACCESS
{
    char * tagName;                 // Fully qualified tag name (symName[x,y,z].mbr.mbr[x].etc).
    WORD   daType;                  // Data type code.
    WORD   eleSize;                 // Size of one data element.

    WORD   opType;                  // Read/Write operation type (input, see defines below).
      #define OCX_CIP_TAG_NO_OP    0
      #define OCX_CIP_TAG_READ_OP  1
      #define OCX_CIP_TAG_WRITE_OP 2

    WORD   numEle;                  // Number of elements to read or write (input).  Must be 1
                                    // if tagName does not specify an array.

    void * data  ;                  // Read/Write data pointer (input - write, input/output - read).
    void * wrMask;                  // Pointer to write bit mask data, NULL if not masked write (input).

    int    result;                  // Read/Write operation result (output), OCX_SUCCESS = success, else = failure

} OCXCIPTAGACCESS;

/************************************************************
* Structure Name: OCX_CIP_STRING82_TYPE
*
* Description:
*
*   A pointer to a structure of this type may is expected
*   as the OCXCIPTAGACCESS data pointer when accessing
*   STRING data types.
*
*************************************************************/
typedef struct                      // String definition in read/write format
{
    DWORD length;                   // String length in chars (bytes)
    char  data[82];                 // ASCII string data
    WORD  pad;                      // Pad word for DWORD alignment
} OCX_CIP_STRING82_TYPE;

/************************************************************
* Structure Name: OCXCIPEXDEVPORTATTR
*
* Description:
*
*   Structure used in port list attribute. Contains the port number and
*   the port's use.
*
*************************************************************/
typedef struct tagOCXCIPEXDEVPORTATTR
{
    WORD    PortNum;
    WORD    PortUse;
} OCXCIPEXDEVPORTATTR;

/************************************************************
* Structure Name: OCXCIPEXDEVOBJ
*
* Description:
*
*   Returned by OCXcip_GetExDevObject().
*
*************************************************************/
typedef struct tagOCXCIPEXDEVOBJ
{
    BYTE                Name[64];
    BYTE                Description[64];
    BYTE                GeoLocation[64];
    WORD                NumPorts;
    OCXCIPEXDEVPORTATTR PortList[8];
} OCXCIPEXDEVOBJ;

/************************************************************
* Structure Name: OCX_CIP_PLC5_RMW_CMD
*
* Description:
*
*   Structure to be passed to OCXcip_PLC5ReadModWrite.
*
*************************************************************/
typedef struct tagOCX_CIP_PLC5_RMW_CMD
{
    char *AddrStr;
    WORD AndMask;
    WORD OrMask;
}OCX_CIP_PLC5_RMW_CMD;

/************************************************************
* Structure Name: OCX_CIP_PLC5_IDHOST
*
* Description:
*
*   Structure to be passed to OCXcip_PLC5GetIDHost.
*
*************************************************************/
typedef struct tagOCX_CIP_PLC5_IDHOST
{
    BYTE Status;
	BYTE Proc;
	BYTE Ext;
	DWORD Mem_Size;
    BYTE SerRev;
    BYTE Num_DH;
    BYTE IOaddr;
    BYTE IOcomm;
	WORD NumDataFiles;
	WORD NumProgTypes;
	BYTE ForcStat;
	BYTE MemProt;
	BYTE BadRAM;
}OCX_CIP_PLC5_IDHOST;

/************************************************************
* Structure Name: OCX_CIP_PLC5_SECTION
*
* Description:
*
*   Structure to be passed to OCXcip_ReadSectionPLC5.
*
*************************************************************/
typedef struct tagOCX_CIP_PLC5_SECTION
{
	WORD Size;
	WORD Count;
	BYTE Type_Size;
	BYTE Ext_Type;
	BYTE Ext_Size;
}OCX_CIP_PLC5_SECTION;


/************************************************************
* Structure Name: OCXSPCONFIG
*
* Description:
*
*   Serial Port configuration structure
*
*************************************************************/
typedef struct _OCXSPCONFIG {
    int port_num;
    int port_cfg;
} OCXSPCONFIG, *POCXSPCONFIG;


/************************************************************
* Structure Name: OCXEDSFILEDATA
*
* Description:
*
*   EDS file definition structure.
*
*************************************************************/
typedef struct tagOCXEDSFILEDATA
{
    WORD    iInstanceId;         // EDS file instance to modify
    BYTE    bMajorRevision;      // EDS file major revision
    BYTE    bMinorRevision;      // EDS file minor revision
	BYTE    bFileEncoding;       // File encoding to use for EDS (Compressed or Uncompressed)
	DWORD   lFileSize;           // size in bytes of EDS file being loaded
	BYTE   *pFileData;           // pointer to EDS file data to be loaded
} OCXEDSFILEDATA;


/* Common definition for API callback functions */
#define OCXCALLBACK     int __cdecl


/*************************************
**      FUNCTION PROTOTYPES         **
*************************************/

#if !defined(__linux__) && !defined(__QNX__)

/* Define a convenient macro for library function declarations */
#if !defined(_DLLEXPORT_)

#if defined(__cplusplus)
#define DLLENTRY extern "C" __declspec(dllimport)
#else
#define DLLENTRY __declspec(dllimport)
#endif

#else  /* _DLLEXPORT_ */

#if defined(__cplusplus)
#define DLLENTRY extern "C" __declspec(dllexport)
#else
#define DLLENTRY __declspec(dllexport)
#endif

#endif /* _DLLEXPORT_ */

/* Define API calling convention */
#define APICALLCONV   __stdcall

/* Define standard API function declaration */
#define OCXAPIENTRY     DLLENTRY int APICALLCONV

#else //__linux__ or __QNX__

#ifdef __cplusplus
#define OCXAPIENTRY     extern "C" int
#else
#define OCXAPIENTRY     int
#endif

#define __cdecl

#endif //__linux__ or __QNX__

/* API Function Declarations */

OCXAPIENTRY OCXcip_Open(OCXHANDLE *);
OCXAPIENTRY OCXcip_OpenNB(OCXHANDLE *);
OCXAPIENTRY OCXcip_ClientOpen(OCXHANDLE *, OCXBPIACONNINFO *);
OCXAPIENTRY OCXcip_Close(OCXHANDLE);
OCXAPIENTRY OCXcip_GetIdObject(OCXHANDLE, OCXCIPIDOBJ *);
OCXAPIENTRY OCXcip_SetIdObject(OCXHANDLE, OCXCIPIDOBJ *);
OCXAPIENTRY OCXcip_SetEmbeddedEDSFile(OCXHANDLE, OCXEDSFILEDATA *);
OCXAPIENTRY OCXcip_GetVersionInfo(OCXHANDLE, OCXCIPVERSIONINFO *);
OCXAPIENTRY OCXcip_ErrorString(int, char *);
OCXAPIENTRY OCXcip_SetUserLED(OCXHANDLE, int);
OCXAPIENTRY OCXcip_GetUserLED(OCXHANDLE, int *);
OCXAPIENTRY OCXcip_SetLED3(OCXHANDLE, int);
OCXAPIENTRY OCXcip_GetLED3(OCXHANDLE, int *);
OCXAPIENTRY OCXcip_SetLED(OCXHANDLE, int, int);
OCXAPIENTRY OCXcip_GetLED(OCXHANDLE, int, int *);
OCXAPIENTRY OCXcip_SetModuleStatus(OCXHANDLE, int);
OCXAPIENTRY OCXcip_GetModuleStatus(OCXHANDLE, int *);
OCXAPIENTRY OCXcip_RegisterAssemblyObj(OCXHANDLE, OCXHANDLE *, void *,
                int (__cdecl *)(OCXHANDLE, OCXCIPCONNSTRUC *),
                int (__cdecl *)(OCXHANDLE, OCXCIPSERVSTRUC *));
OCXAPIENTRY OCXcip_UnregisterAssemblyObj(OCXHANDLE, OCXHANDLE);
OCXAPIENTRY OCXcip_WriteConnected(OCXHANDLE, OCXHANDLE, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_ImmediateOutput(OCXHANDLE, OCXHANDLE);
OCXAPIENTRY OCXcip_WriteConnectedImmediate(OCXHANDLE, OCXHANDLE, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_ReadConnected(OCXHANDLE, OCXHANDLE, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_RegisterFatalFaultRtn(OCXHANDLE, int (__cdecl *)(void));
OCXAPIENTRY OCXcip_RegisterResetReqRtn(OCXHANDLE, int (__cdecl *)(void));
OCXAPIENTRY OCXcip_RegisterFlashUpdateRtn(OCXHANDLE, int (__cdecl *)(void));
OCXAPIENTRY OCXcip_RegisterResetParamReqRtn(OCXHANDLE, int (__cdecl *)(BYTE));
OCXAPIENTRY OCXcip_RegisterShutdownReqRtn(OCXHANDLE, int (__cdecl *)(BYTE, BYTE *));
OCXAPIENTRY OCXcip_RegisterResetButtonRtn(OCXHANDLE, int (__cdecl *)(DWORD, DWORD, DWORD));
OCXAPIENTRY OCXcip_Sleep(OCXHANDLE, WORD);
OCXAPIENTRY OCXcip_SetDisplay(OCXHANDLE, char *);
OCXAPIENTRY OCXcip_GetDisplay(OCXHANDLE, char *);
OCXAPIENTRY OCXcip_GetSwitchPosition(OCXHANDLE, int *);
OCXAPIENTRY OCXcip_GetTemperature(OCXHANDLE, int *);
OCXAPIENTRY OCXcip_ReadSRAM(OCXHANDLE, BYTE *, DWORD, DWORD);
OCXAPIENTRY OCXcip_WriteSRAM(OCXHANDLE, BYTE *, DWORD, DWORD);
OCXAPIENTRY OCXcip_CalculateCRC(BYTE *, DWORD, WORD *);
OCXAPIENTRY OCXcip_DataTableRead(OCXHANDLE, BYTE *, WORD, WORD, BYTE, BYTE *, WORD *, BYTE, WORD);
OCXAPIENTRY OCXcip_DataTableWrite(OCXHANDLE, BYTE *, WORD, WORD, BYTE, BYTE *, BYTE, WORD);
OCXAPIENTRY OCXcip_InitTagDefTable(OCXHANDLE);
OCXAPIENTRY OCXcip_UninitTagDefTable(OCXHANDLE);
OCXAPIENTRY OCXcip_TagDefine(OCXHANDLE, OCXTAGDEFSTRUC *, TAGHANDLE *);
OCXAPIENTRY OCXcip_TagUndefine(OCXHANDLE, TAGHANDLE);
OCXAPIENTRY OCXcip_DtTagRd(OCXHANDLE, TAGHANDLE, void *);
OCXAPIENTRY OCXcip_DtTagWr(OCXHANDLE, TAGHANDLE, void *);
OCXAPIENTRY OCXcip_GetDeviceIdObject(OCXHANDLE, BYTE *, OCXCIPIDOBJ *, WORD);
OCXAPIENTRY OCXcip_GetDeviceIdStatus(OCXHANDLE, BYTE *, WORD *, WORD);
OCXAPIENTRY OCXcip_GetDeviceICPObject(OCXHANDLE, BYTE *, OCXCIPICPOBJ *, WORD);
OCXAPIENTRY OCXcip_RdIdStatusDefine(OCXHANDLE, OCXTAGDEFSTRUC *, TAGHANDLE *);
#ifndef __QNX__
OCXAPIENTRY OCXcip_GetWCTime(OCXHANDLE, BYTE *, OCXCIPWCT *, WORD);
OCXAPIENTRY OCXcip_SetWCTime(OCXHANDLE, BYTE *, OCXCIPWCT *, WORD);
OCXAPIENTRY OCXcip_GetWCTimeUTC(OCXHANDLE, BYTE *, OCXCIPWCTUTC *, WORD);
OCXAPIENTRY OCXcip_SetWCTimeUTC(OCXHANDLE, BYTE *, OCXCIPWCTUTC *, WORD);
#endif
OCXAPIENTRY OCXcip_WaitForRxData(OCXHANDLE, OCXHANDLE, int);
OCXAPIENTRY OCXcip_GetModuleStatusWord(OCXHANDLE, WORD *);
OCXAPIENTRY OCXcip_SetModuleStatusWord(OCXHANDLE, WORD, WORD);
OCXAPIENTRY OCXcip_AccessTagData(OCXHANDLE, char *, WORD, OCXCIPTAGACCESS **, WORD);
OCXAPIENTRY OCXcip_AccessTagDataAbortable(OCXHANDLE, char *, WORD, OCXCIPTAGACCESS **, WORD, WORD *);
OCXAPIENTRY OCXcip_MsgResponse(OCXHANDLE, void *, BYTE, BYTE *, WORD, BYTE, WORD);
OCXAPIENTRY OCXcip_GetActiveNodeTable(OCXHANDLE, int *, DWORD *);
OCXAPIENTRY OCXcip_GetExDevObject(OCXHANDLE, BYTE *, OCXCIPEXDEVOBJ *, WORD);
OCXAPIENTRY OCXcip_PLC5TypedRead(OCXHANDLE, BYTE *, void *, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_PLC5TypedWrite(OCXHANDLE, BYTE *, BYTE *, void *, WORD, WORD);
OCXAPIENTRY OCXcip_PLC5WordRangeRead(OCXHANDLE, BYTE *, void *, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_PLC5WordRangeWrite(OCXHANDLE, BYTE *, BYTE *, void *, WORD, WORD);
OCXAPIENTRY OCXcip_PLC5ReadModWrite(OCXHANDLE, BYTE *, OCX_CIP_PLC5_RMW_CMD *, WORD, WORD);
OCXAPIENTRY OCXcip_SLCProtTypedRead(OCXHANDLE, BYTE *, void *, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_SLCProtTypedWrite(OCXHANDLE, BYTE *, BYTE *, void *, WORD, WORD);
OCXAPIENTRY OCXcip_SLCReadModWrite(OCXHANDLE, BYTE *, BYTE *, WORD *, WORD *, WORD);
OCXAPIENTRY OCXcip_PLC5GetIDHost(OCXHANDLE, BYTE *, OCX_CIP_PLC5_IDHOST *, WORD);
OCXAPIENTRY OCXcip_ReadSectionPLC5(OCXHANDLE,BYTE *,WORD,OCX_CIP_PLC5_SECTION *,WORD);
OCXAPIENTRY OCXcip_MLGXProtTypedRead(OCXHANDLE, BYTE *, void *, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_MLGXProtTypedWrite(OCXHANDLE, BYTE *, BYTE *, void *, WORD, WORD);
OCXAPIENTRY OCXcip_MLGXReadModWrite(OCXHANDLE, BYTE *, BYTE *, WORD *, WORD *, WORD);
OCXAPIENTRY OCXcip_MLGX14ProtTypedRead(OCXHANDLE, BYTE *, void *, BYTE *, WORD, WORD);
OCXAPIENTRY OCXcip_MLGX14ProtTypedWrite(OCXHANDLE, BYTE *, BYTE *, void *, WORD, WORD);
OCXAPIENTRY OCXcip_MLGX14ReadModWrite(OCXHANDLE, BYTE *, BYTE *, WORD *, WORD *, WORD);
OCXAPIENTRY OCXcip_GetSerialConfig(OCXHANDLE, OCXSPCONFIG *);
OCXAPIENTRY OCXcip_SetSerialConfig(OCXHANDLE, OCXSPCONFIG *);
OCXAPIENTRY OCXcip_ReadTimer(OCXHANDLE, int, DWORD *);
OCXAPIENTRY OCXcip_SetTagAccessConnSize(OCXHANDLE,int);
#endif  /* _OCXCIPAPI_H */




