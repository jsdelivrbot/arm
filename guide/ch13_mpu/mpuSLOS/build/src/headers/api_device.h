/*
 *  ____________________________________________________________________
 * 
 *  Copyright (c) 2003, Andrew N. Sloss, Chris Wright and Dominic Symes
 *  All rights reserved.
 *  ____________________________________________________________________
 * 
 *  NON-COMMERCIAL USE License
 *  
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met: 
 *  
 *  1. For NON-COMMERCIAL USE only.
 * 
 *  2. Redistributions of source code must retain the above copyright 
 *     notice, this list of conditions and the following disclaimer. 
 * 
 *  3. Redistributions in binary form must reproduce the above 
 *     copyright notice, this list of conditions and the following 
 *     disclaimer in the documentation and/or other materials provided 
 *     with the distribution. 
 * 
 *  4. All advertising materials mentioning features or use of this 
 *     software must display the following acknowledgement:
 * 
 *     This product includes software developed by Andrew N. Sloss,
 *     Chris Wright and Dominic Symes. 
 * 
 *   THIS SOFTWARE IS PROVIDED BY THE CONTRIBUTORS ``AS IS'' AND ANY 
 *   EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 *   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 *   PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE CONTRIBUTORS BE 
 *   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, 
 *   OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
 *   OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR 
 *   TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 *   OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 *   OF SUCH DAMAGE. 
 * 
 *  If you have questions about this license or would like a different
 *  license please email :
 * 
 * 	andrew@sloss.net
 * 
 * 
 */
 
/*****************************************************************************
 * Simple Little Operating System - SLOS
 *****************************************************************************/

/*****************************************************************************
 *
 * Module     : api_device.h
 * Descripion : SWI API for DDF model (liMa)
 * OS         : SLOS 0.09
 * Platform   : generic
 * History    :
 *
 * 15th July 2002 Andrew N. Sloss
 * - added header
 *
 * 9th July 2003 Andrew N. Sloss
 * - added new headers
 *****************************************************************************/

/*****************************************************************************
 * IMPORT
 *****************************************************************************/

#include "../cm940iap/events/swis.h"

/*****************************************************************************
 * API's
 *****************************************************************************/

/* -- eventIODeviceInit ------------------------------------------------------
 *
 * Description : initializes all internal device driver data structures.
 *               this routine should only be called once. Unless for some
 *               reason you need to reset all the device drivers.
 *
 * Parameters  : none....
 * Return      : none...
 * Notes       :
 * 
 *  This function is called in the core/cinit.c file
 *  
 *    eventIOdeviceInit();
 *
 */

__swi (SLOS) void _eventIODeviceInit (UINT);
#define eventIODeviceInit() _eventIODeviceInit (Event_IODeviceInit)

/* -- eventIODeviceOpen ------------------------------------------------------
 *
 * Description : open a device driver
 *
 * Parameters  : UID * - address for UID
 *             : UINT - major device. For example, SERIAL
               : UINT - minor device. For exmaple, COM1
 * Return      : device_treestr * - pointer to device driver
 * Notes       :
 * 
 *   This function is used to open a COM1 of a SERIAL device.
 *   Example: 
 *
 *   handle = eventIODeviceOpen(&UID,SERIAL,COM1);
 *
 *   if (handle==DEVICE_UNKNOWN || handle==DEVICE_IN_USE)
 *   {
 *   canNotOpenDevice(); 
 *   }
 */

__swi (SLOS) device_treestr *_eventIODeviceOpen (UINT,UID *,UINT,UINT);
#define eventIODeviceOpen(a,b,c) _eventIODeviceOpen \
          (Event_IODeviceOpen,(a),(b),(c))

/* -- eventIODeviceClose -----------------------------------------------------
 *
 * Description : close a device driver
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifer
 * Return      : int
 * Notes       : 
 *
 *  This is used to close an open device
 *  Example: 
 *
 *    if (eventIODeviceClose(handle,id)!=DEVICE_SUCCESS)
 *    {
 *    couldNotCloseDevice();
 *    }
 */

__swi (SLOS) int _eventIODeviceClose (UINT,device_treestr *,UID);
#define eventIODeviceClose(a,b) _eventIODeviceClose \
          (Event_IODeviceClose,(a),(b))

/* -- eventIOeviceWriteByte --------------------------------------------------
 *
 * Description : write a byte to an open device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 *             : UINT - byte store in the lower 8-bits
 * Return      : none...
 * Notes       :
 *
 *   This is used to write a byte to an open device 
 *   Example: eventIODeviceWriteByte(handle,id,c);
 */

__swi (SLOS) void _eventIODeviceWriteByte (UINT,device_treestr *,UID,UINT);
#define eventIODeviceWriteByte(a,b,c) _eventIODeviceWriteByte \
          (Event_IODeviceWriteByte,(a),(b),(c))

/* -- eventIODeviceReadByte --------------------------------------------------
 *
 * Description : read a byte from a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 * Return      : UINT - least significant 8-bits contain the byte
 * Notes       :
 * 
 *  This is used to read a byte from an open device
 *  Example: c = eventIODeviceReadByte(handle,id);
 */

__swi (SLOS) UINT _eventIODeviceReadByte (UINT,device_treestr *,UID);
#define eventIODeviceReadByte(a,b) _eventIODeviceReadByte \
          (Event_IODeviceReadByte,(a),(b))

/* -- eventIODeviceWriteBit --------------------------------------------------
 *
 * Description : write a bit to a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 *             : UINT - byte store in the lower 1-bits 
 * Return      : none...
 * Notes       :
 * 
 *  This is used to write a bit to an open device
 *  Example: eventIOdeviceWriteBit(handle,id,bit);
 */

__swi (SLOS) void _eventIODeviceWriteBit (UINT,device_treestr *,UID,UINT);
#define eventIODeviceWriteBit(a,b,c) _eventIODeviceWriteBit \
          (Event_IODeviceWriteBit,(a),(b),(c))

/* -- eventIODeviceReadBit ---------------------------------------------------
 *
 * Description : read a bit from a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 * Return      : UINT - least significant bits contains the bit
 * Notes       :
 * 
 *  This is used to read a bit from an open device
 *  Example: bit = eventIODeviceReadBit(handle,id);
 */

__swi (SLOS) UINT _eventIODeviceReadBit (UINT,device_treestr *,UID);
#define eventIODeviceReadBit(a,b) _eventIODeviceReadBit \
          (Event_IODeviceReadBit,(a),(b))

/* -- eventIODeviceWriteBlock ------------------------------------------------
 *
 * Description : write a block to a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 *             : void * - point block to write to a device
 * Notes       :
 * 
 *  This is used to write a block to an open device
 *  Example: eventIODeviceWriteBlock(handle,id,&block);
 */

__swi (SLOS) void _eventIODeviceWriteBlock (UINT,device_treestr *,UID,void *);
#define eventIODeviceWriteBlock(a,b,c) _eventIODeviceWriteBlock \
          (Event_IODeviceWriteBlock,(a),(b),(c))

/* -- event_eventIODeviceReadBlock -------------------------------------------
 *
 * Description : read a block from a device
 *
 * Parameters  : device_treestr * - pointer to device driver
 *             : UID - unique identifier
 * Return      : void * - pointer to data block
 * Notes       :
 * 
 *  This is used to read a block from an open device
 *  Example: block = eventIODeviceReadBlock(handle,id);
 */

__swi (SLOS) void * _eventIODeviceReadBlock (UINT,device_treestr *,UID);
#define eventIODeviceReadBlock(a,b) _eventIODeviceReadBlock \
          (Event_IODeviceReadBlock,(a),(b))


