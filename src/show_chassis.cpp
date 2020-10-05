/************************************************************************
*
*   Title: Show Chassis Example Code
*
*   Abstract:
*
*   This simple example program will display the contents of each slot
*   in the local chassis.
*
************************************************************************/

#include <iostream>
#include <string>

#if _MSC_VER > 1500
#pragma warning( disable : 4996 )	// Disable the fopen/ctime/sprintf/strcpy/strcat/etc unsafe warnings
#pragma warning( disable : 4100 )	// Disable unreferenced formal parameter warnings
#endif //_MSC_VER > 1500

#ifdef _WIN32
#include <windows.h>
#else
#include    <unistd.h>
#endif
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <ctype.h>
#include "ocxbpapi.h"
#include "show_chassis.h"

std::string showChassis() {
    int rc;
    	OCXHANDLE apiHandle;
    	OCXCIPIDOBJ idobj;
    	char buf[256];
    	BYTE path[16];
    	DWORD ant;
    	int chassisSize;
    	int n;

    	// Initialize backplane API
    	if (OCX_SUCCESS != (rc = OCXcip_Open(&apiHandle)))
    	{
    		OCXcip_ErrorString(rc, buf);
    		fprintf(stderr, "\nOCXcip_Open failed! (%d - %s)\n", rc, buf);
            return "OCXcip_Open failed!\n";
    	}

    	// Get chassis size and active slots
    	if (OCX_SUCCESS != (rc = OCXcip_GetActiveNodeTable(apiHandle, &chassisSize, &ant)))
    	{
    		OCXcip_ErrorString(rc, buf);
    		fprintf(stderr, "\nOCXcip_GetActiveNodeTable failed! (%d - %s)", rc, buf);
    		OCXcip_Close(apiHandle);
    		exit(1);
    	}

    	// Enumerate each slot of the chassis (including ours)
    	for (n=0; n<chassisSize; n++)
    	{
    		if (ant & (1 << n))								// Skip empty slots
    		{
    			sprintf((char *)path, "p:1,s:%d", n);
    			if (OCX_SUCCESS != (rc = OCXcip_GetDeviceIdObject(apiHandle, &path[0], &idobj, 5000)))
    			{
    				OCXcip_ErrorString(rc, buf);
    				printf("\nModule in slot %d did not respond to ID request (%d - %s)\n", n, rc, buf);
    				continue;
    			}
    			else
    			{
    				printf("\nSlot %d", n);
    				printf("\nVendor: %d", idobj.VendorID);
    				printf("\nProduct Type: %d", idobj.DeviceType);
    				printf("\nProduct Code: %d", idobj.ProductCode);
    				printf("\nRevision: %d.%d", idobj.MajorRevision, idobj.MinorRevision);
    				printf("\nSerial No: %08X", idobj.SerialNo);
    				printf("\n%s\n", idobj.Name);
    			}
    		}
    		else
    		{
    			printf("\nSlot %d - Empty\n", n);
    		}
    	}

    	OCXcip_Close(apiHandle);

    	return "Done showing chassis!";
}

std::string dontShowChassis() {
    	return "Done NOT showing chassis!";
}
