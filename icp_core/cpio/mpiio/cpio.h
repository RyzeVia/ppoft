/*
 * cpio.h
 *
 *  Created on: 2013/09/18
 *      Author: RyzeVia
 */

#ifndef CPIO_H_
#define CPIO_H_

#define ICP_DMG_MPIIO

#define CPIO_TYPEDEF \
	void* comm;

void CPIO_MPIIO_init(void *icp_info, void *comm);
void CPIO_MPIIO_fini(void *icp_info);

#endif /* CPIO_H_ */
