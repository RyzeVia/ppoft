/*
 * libnspawn.h
 *
 *  Created on: 2013/05/09
 *      Author: RyzeVia
 */

#ifndef LIBNSPAWN_H_
#define LIBNSPAWN_H_

extern void spawn_init();
extern int spawn_comm_get_parent(MPI_Comm *parent);
extern void spawn_fini();
extern int spawn_exec(MPI_Comm *intercomm);

#endif /* LIBNSPAWN_H_ */
