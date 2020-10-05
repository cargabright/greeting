/** $Revision:   1.19  $ **/
/**/
/************************************************************************
*
*   Title:        56SAM CIP Tag Database API Definitions
*
*   Abstract:     This file contains definitions and declarations
*                 needed for developing applications which require
*                 Logix Symbol and Structure definition interfaces.
*
*   Environment:  56SAM Module
*                 Windows NT / CE
*                 Visual C++ / eVC++
*
*                 Copyright (c) 2003-2005 Online Development, Inc.
*
************************************************************************/

#ifndef _OCXTAGDB_H
#define _OCXTAGDB_H

/*************************************
**      DEFINED CONSTANTS           **
*************************************/
                                            // "PROGRAM:" + ProgName + "." + SymName
#define OCX_CIP_MAX_SYMNAME_LEN         (16+40+1+40)
#define OCX_CIP_MAX_STRUCTNAME_LEN      40
#define OCX_CIP_MAX_STRUCTMBRNAME_LEN   40

/*****************************************
** Structure I/O type defines.          **
**                                      **
** See the ioType member of the         **
** OCXTAGDBSTRUCT structure.            **
******************************************/
#define OCX_CIP_STRUCT_IOTYPE_NA     '!'    // Memory type (whole struct not accessible)
#define OCX_CIP_STRUCT_IOTYPE_INP    'i'    // Input type (whole struct read only)
#define OCX_CIP_STRUCT_IOTYPE_OUT    'o'    // Output type (whole struct read only)
#define OCX_CIP_STRUCT_IOTYPE_RMEM   '#'    // Memory (whole struct read only)
#define OCX_CIP_STRUCT_IOTYPE_MEM    'n'    // Memory (whole struct read/write)
#define OCX_CIP_STRUCT_IOTYPE_STRING '$'    // Memory string (whole struct read/write)

/*****************************************
** Recommended display format for       **
** structure members.                   **
**                                      **
** See the dispFmt member of the        **
** OCXCIPTAGDBSTRUCTMBR structure.      **
******************************************/
#define OCX_CIP_STRUCTMBR_FMT_UNKNOWN  'A'  // Unknown format
#define OCX_CIP_STRUCTMBR_FMT_GENERAL  'B'  // General format
#define OCX_CIP_STRUCTMBR_FMT_BINARY   'C'  // Format as binary
#define OCX_CIP_STRUCTMBR_FMT_OCTAL    'D'  // Format as octal
#define OCX_CIP_STRUCTMBR_FMT_DECIMAL  'E'  // Format as decimal
#define OCX_CIP_STRUCTMBR_FMT_HEX      'F'  // Format as hex
#define OCX_CIP_STRUCTMBR_FMT_EXPONENT 'G'  // Format as exponential
#define OCX_CIP_STRUCTMBR_FMT_FLOAT    'H'  // Format as float
#define OCX_CIP_STRUCTMBR_FMT_ASCII    'I'  // Format as ascii


/*****************************************
** Normalization option bits for        **
** OCXcip_SetTagDbOptions().            **
******************************************/
#define OCX_CIP_TAGDBOPT_NORM_STRINGS               0x0001  // Normalized strings are <DATA><NULL>
#define OCX_CIP_TAGDBOPT_NORM_BOOLS                 0x0002  // Normalized BOOLs are bytes
#define OCX_CIP_TAGDBOPT_ALLOW_IO_WRITE             0x0004  // Allow input/output tag writes
#define OCX_CIP_TAGDBOPT_STRUCT_MBR_ORDER_NATIVE    0x0040  // Order struct memebers by offset in struct
                                                            // (instead of the default alphabetical order)

/*****************************************
** Extended/Normalized data types       **
** (in addition to OCX_CIP_BOOL, etc.)  **
** The standard data types will only fit**
** in a WORD.  Extended data types must **
** have at least one hi-WORD bit set.   **
** Note that the MSB (0x80000000) is	**
** reserved for internal use.			**
******************************************/
#define OCX_CIP_TAGDB_DATYPE_NORM_INVALID   0x10000         // Normalization failed for this item
#define OCX_CIP_TAGDB_DATYPE_NORM_STRING    0x10001         // Normalized string (<DATA><NULL>)
#define OCX_CIP_TAGDB_DATYPE_NORM_BITMASK   0x10002         // Normalized bit masked BOOL


/*************************************
**      TYPE DEFINITIONS
*************************************/
typedef DWORD OCXTAGDBHANDLE;


/*************************************
**      SRUCTURE DEFINITIONS        **
*************************************/

typedef struct tagOCXCIPTAGDBSYM
{
                                    // NULL terminated symbol name with possible
                                    // "PROGRAM:" + ProgName + "." prefix
    char    name[OCX_CIP_MAX_SYMNAME_LEN+1];
    DWORD   daType;                 // Symbol data type (0x00C3, etc...)
    WORD    hStruct;                // 0 = symbol not struct, else = structure handle
    DWORD   eleSize;                // Element size in bytes
    DWORD   xDim;                   // X dimension (0 = not array)
    DWORD   yDim;                   // Y dimension (0 = no dimension specified)
    DWORD   zDim;                   // Z dimension (0 = no dimension specified)
    WORD    fAttr;                  // Bit masked attribute flags (possible bits follow)
    #define OCXCIPTAGDBSYM_ATTR_ALIAS 0x0001    // Symbol is an alias for a tag
    #define OCXCIPTAGDBSYM_ATTR_IO    0x0002    // Symbol is input or output
} OCXCIPTAGDBSYM;

typedef struct tagOCXCIPTAGDBSTRUCT
{
                                    // NULL terminated structure name
    char    name[OCX_CIP_MAX_STRUCTNAME_LEN+1];
    DWORD   daType;                 // Structure data type
    DWORD   daSize;                 // Size of structure data in bytes
    BYTE    ioType;                 // I/O type, see OCX_CIP_STRUCT_IOTYPE_* defines
    WORD    numMbr;                 // Number of structure members
} OCXCIPTAGDBSTRUCT;

typedef struct tagOCXCIPTAGDBSTRUCTMBR
{
                                    // NULL terminated structure member name
    char    name[OCX_CIP_MAX_STRUCTMBRNAME_LEN+1];
    DWORD   daType;                 // Structure member data type
    WORD    hStruct;                // 0 = member not struct, else = structure handle
    DWORD   eleSize;                // Element size of one member in bytes
    DWORD   daOfs;                  // Byte offset of member data in structure
    WORD    bitId;                  // Bit ID if daType is 0x00C1
    DWORD   arrDim;                 // 0 = struct member not array, else = array dimension
    BYTE    dispFmt;                // Recommended display format
    WORD    fAttr;                  // Bit masked attribute flags (possible bits follow)
    #define OCXCIPTAGDBSTRUCTMBR_ATTR_ALIAS 0x0001  // Member is an alias for another member
    WORD    baseMbrId;              // Value of aliased member if alias bit in fAttr set
} OCXCIPTAGDBSTRUCTMBR;

typedef struct tagOCXCIPTAGINFO
{
    DWORD   daType;                 // Data type code (as returned from OCXcip_GetSymbolInfo()).
    WORD    hStruct;                // 0 = tag not struct, else = structure definition handle.
    DWORD   eleSize;                // Size in bytes of one data element.
    DWORD   xDim;                   // X dimension, 0 = not array.
    DWORD   yDim;                   // Y dimension, 0 = no Y dimension, struct members yDim=0.
    DWORD   zDim;                   // Z dimension, 0 = no Z dimension, struct members zDim=0.
    DWORD   xIdx;                   // X index, always 0 if not an array
    DWORD   yIdx;                   // Y index, always 0 if yDim does not apply
    DWORD   zIdx;                   // Z index, always 0 if zDim does not apply
    BYTE    dispFmt;                // Recommended display format.
} OCXCIPTAGINFO;

/************************************************************
* Structure Name: OCXCIPTAGDBACCESS
*
* Description:
*
*   A pointer to a structure of this type is passed to
*   the OCXcip_AccessTagDataDb function.
*
*************************************************************/
typedef struct tagOCXCIPTAGDBACCESS
{
    char * tagName;                 // Fully qualified tag name (symName[x,y,z].mbr.mbr[x].etc).

    WORD   opType;                  // Read/Write operation type (input, see defines below).
                                    // Same as OCXCIPTAGACCESS operation defines.

    DWORD  daType;                  // Data type code.
    DWORD  eleSize;                 // Size of one data element.
    DWORD  numEle;                  // Number of elements to read or write (input).  Must be 1
                                    // if tagName does not specify an array.

    void * data  ;                  // Read/Write data pointer (input - write, input/output - read).
    void * wrMask;                  // Pointer to write bit mask data, NULL if not masked write (input).

    int    result;                  // Read/Write operation result (output), OCX_SUCCESS = success, else = failure

} OCXCIPTAGDBACCESS;


/*************************************
**      FUNCTION PROTOTYPES         **
*************************************/
OCXAPIENTRY OCXcip_CreateTagDbHandle(OCXHANDLE, char *, WORD, OCXTAGDBHANDLE *);
OCXAPIENTRY OCXcip_DeleteTagDbHandle(OCXHANDLE, OCXTAGDBHANDLE);
OCXAPIENTRY OCXcip_BuildTagDb(OCXHANDLE, OCXTAGDBHANDLE, WORD *);
OCXAPIENTRY OCXcip_TestTagDbVer(OCXHANDLE, OCXTAGDBHANDLE);
OCXAPIENTRY OCXcip_GetSymbolInfo(OCXHANDLE, OCXTAGDBHANDLE, WORD, OCXCIPTAGDBSYM *);
OCXAPIENTRY OCXcip_GetStructInfo(OCXHANDLE, OCXTAGDBHANDLE, WORD, OCXCIPTAGDBSTRUCT *);
OCXAPIENTRY OCXcip_GetStructMbrInfo(OCXHANDLE, OCXTAGDBHANDLE, WORD, WORD, OCXCIPTAGDBSTRUCTMBR *);
OCXAPIENTRY OCXcip_GetTagDbTagInfo(OCXHANDLE, OCXTAGDBHANDLE, char *, OCXCIPTAGINFO *);
OCXAPIENTRY OCXcip_AccessTagDataDb(OCXHANDLE, OCXTAGDBHANDLE, OCXCIPTAGDBACCESS **, WORD, WORD *);
OCXAPIENTRY OCXcip_SetTagDbOptions(OCXHANDLE, OCXTAGDBHANDLE, DWORD, WORD);
OCXAPIENTRY OCXcip_MsgData2HostDb(OCXHANDLE, OCXTAGDBHANDLE, void *, DWORD, DWORD, void *, DWORD, DWORD);

#endif
