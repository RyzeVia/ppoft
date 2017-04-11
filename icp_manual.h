/*
 * icp_manual.h
 *
 *  Created on: 2013/03/21
 *      Author: RyzeVia
 */

#ifndef ICP_MANUAL_H_
#define ICP_MANUAL_H_

/*
 * ENV value
 *
 *
 * - ICP_CKPTNAME
 * checkpoint file name. if you not fix it, it use from argument of API.
 *
 * - ICP_RESTART_FLAG
 * restart flag. if you set it 1, program start from restart file.
 * file name was fixed by ICP_CKPTNAME rules.
 *
 * - ICP_RESTART_ITER
 * what number of iteration checkpoint file you use.
 * if you not set it, program use newest one.
 *
 * - ICP_ROOT_HOSTNAME
 * set to leader process's hostname
 * default: 127.0.0.1
 *
 * - MICP_FR_DBFILE
 * failure rate recoded dbfile
 *
 */


/*
 * FTB XPT module
 *
 * - XPTI_FTB_DATABASE_SERVER
 * ftb database server's command which called by shell. default: ftb_database_server
 *
 * - XPTI_FTB_AGENT
 * ftb agent's command which called by shell. default: ftb_agent
 *
 * - XPTI_FTB_DATABASE_SERVER_IP
 * ftb database server's node ip. default: ICP_ROOT_HOSTNAME
 *
 */

/* For Failure Rate DB
 * DB has following data:
 * hostname%sFIT:
 * FIT is used (count/second)
 */

/* Test env
 *
 * - ICP_TEST_CPWAIT
 * how many additional time for checkpointing
 *
 * - ICP_TEST_SINGLEGEN
 * it fixed checkpoint generation. it means: all checkpoint saved on ckpt.0.<fixed NUM>
 *
 */

#endif /* ICP_MANUAL_H_ */
