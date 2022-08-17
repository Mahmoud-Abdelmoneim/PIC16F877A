/* 
 * File:   hal_ccp1_cfg.h
 * Author: Mahmoud Abdelmoniem
 *
 * Created on 01 , 2022, 07:36 
 */

#ifndef HAL_CCP1_CFG_H
#define	HAL_CCP1_CFG_H
#define _XTAL_FREQ 4000000
/*........section: macro declarations......... */

#define CCP1_CFG_CAPTURE_MODE_SELSECT       0
#define CCP1_CFG_COMPARE_MODE_SELSECT       1
#define CCP_CFG_PWN_MODE_SELSECT           2

#define CCP1_CFG_SELECTED_MODE              CCP_CFG_PWN_MODE_SELSECT
#define CCP2_CFG_SELECTED_MODE              CCP_CFG_PWN_MODE_SELSECT
/*........section: macro function declarations......... */


/*........section: data type declarations......... */


/*........section: function declarations......... */
#endif	/* HAL_CCP1_CFG_H */

