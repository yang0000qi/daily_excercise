/***************************************************************************
 *                                                                         *
 *       Shanghai Zongmu Technology Co. Ltd.                               *
 *                                                                         *
 *    Copyright (c) 2013 by Shanghai Zongmu Technology Co. Ltd.            *
 *    All rights reserved.                                                 *
 *                                                                         *
 *    This Software is protected by People's Republic of China copyright   *
 *    laws and international treaties.  You may not reverse engineer,      *
 *    decompile or disassemble this Software.                              *
 *                                                                         *
 *    WARNING:                                                             *
 *    This Software contains Shanghai Zongmu Technology Co. Ltd.'s         *
 *    confidential and proprietary information. UNAUTHORIZED COPYING,      *
 *    USE, DISTRIBUTION, PUBLICATION, TRANSFER, SALE, RENTAL OR DISCLOSURE *
 *    IS PROHIBITED AND MAY RESULT IN SERIOUS LEGAL CONSEQUENCES.  Do not  *
 *    copy this Software without Shanghai Zongmu Technology Co. Ltd.'s     *
 *    express written permission.   Use of any portion of the contents of  *
 *    this Software is subject to and restricted by your written agreement *
 *    with Shanghai Zongmu Technology Co. Ltd.                             *
 *                                                                         *
 ***************************************************************************/

#ifndef _PARAMS_H
#define _PARAMS_H

typedef enum {
        SENSOR_CAMERA_INVAILD = 0,
        SENSOR_CAMERA_OV10640,
        SENSOR_CAMERA_OV10635,
        SENSOR_CAMERA_AR0143AT,
} sensor_camera_type;

extern int parse_xml_config_camera_type(const char *filename);

#endif /* _PARAMS_H */
