/* 
 * File:   mcal_std_types.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 10 , 2022, 03:19 
 */

#ifndef MCAT_STD_TYPES_H
#define	MCAT_STD_TYPES_H

/*........section include.........*/

#include "std_libraries.h"
#include "compiler.h"




/*........section: macro function declarations......... */


/*........section: data type declarations......... */

typedef unsigned char              uint8;
typedef unsigned short             uint16;
typedef unsigned int               uint32;
typedef signed   char              sint8;
typedef signed   short             sint16;
typedef signed   long              sint32;

typedef uint8 std_returntype;

#define ZERO_INT    0

/*........section: macro declarations......... */

#define STD_HIGH        0x01

#define STD_LOW         0x00

#define SDT_ON          0x01

#define SDT_OFF         0x00

#define STD_ACTIVE      0x01

#define STD_IDLE        0x00

#define E_OK            (uint8 )0x01
#define E_NOT_OK        (uint8 )0x00


/*........section: function declarations......... */

#endif	/* MCAT_STD_TYPES_H */

