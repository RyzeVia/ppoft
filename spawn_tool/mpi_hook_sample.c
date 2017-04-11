#include <mpi.h>
extern MPI_Comm MPI_COMM_SMALLER_WORLD;
int MPI_Send(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Send(buf,count,datatype,dest,tag,comm);
}
int MPI_Recv(void * buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Recv(buf,count,datatype,source,tag,comm,status);
}
int MPI_Bsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Bsend(buf,count,datatype,dest,tag,comm);
}
int MPI_Ssend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ssend(buf,count,datatype,dest,tag,comm);
}
int MPI_Rsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Rsend(buf,count,datatype,dest,tag,comm);
}
int MPI_Isend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Isend(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Ibsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ibsend(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Issend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Issend(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Irsend(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Irsend(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Irecv(void * buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Irecv(buf,count,datatype,source,tag,comm,request);
}
int MPI_Iprobe(int source, int tag, MPI_Comm comm, int * flag, MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iprobe(source,tag,comm,flag,status);
}
int MPI_Probe(int source, int tag, MPI_Comm comm, MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Probe(source,tag,comm,status);
}
int MPI_Send_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Send_init(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Bsend_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Bsend_init(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Ssend_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ssend_init(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Rsend_init(const void * buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Rsend_init(buf,count,datatype,dest,tag,comm,request);
}
int MPI_Recv_init(void * buf, int count, MPI_Datatype datatype, int source, int tag,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Recv_init(buf,count,datatype,source,tag,comm,request);
}
int MPI_Sendrecv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, int dest,int sendtag, void * recvbuf, int recvcount, MPI_Datatype recvtype,int source, int recvtag, MPI_Comm comm, MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Sendrecv(sendbuf,sendcount,sendtype,dest,sendtag,recvbuf,recvcount,recvtype,source,recvtag,comm,status);
}
int MPI_Sendrecv_replace(void * buf, int count, MPI_Datatype datatype, int dest,int sendtag, int source, int recvtag, MPI_Comm comm,MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Sendrecv_replace(buf,count,datatype,dest,sendtag,source,recvtag,comm,status);
}
int MPI_Pack(const void * inbuf, int incount, MPI_Datatype datatype, void * outbuf,int outsize, int * position, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Pack(inbuf,incount,datatype,outbuf,outsize,position,comm);
}
int MPI_Unpack(const void * inbuf, int insize, int * position, void * outbuf, int outcount,MPI_Datatype datatype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Unpack(inbuf,insize,position,outbuf,outcount,datatype,comm);
}
int MPI_Pack_size(int incount, MPI_Datatype datatype, MPI_Comm comm, int * size){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Pack_size(incount,datatype,comm,size);
}
int MPI_Barrier(MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Barrier(comm);
}
int MPI_Bcast(void * buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Bcast(buffer,count,datatype,root,comm);
}
int MPI_Gather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Gather(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,root,comm);
}
int MPI_Gatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,const int * recvcounts, const int * displs, MPI_Datatype recvtype, int root,MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Gatherv(sendbuf,sendcount,sendtype,recvbuf,recvcounts,displs,recvtype,root,comm);
}
int MPI_Scatter(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Scatter(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,root,comm);
}
int MPI_Scatterv(const void * sendbuf, const int * sendcounts, const int * displs,MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype,int root, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Scatterv(sendbuf,sendcounts,displs,sendtype,recvbuf,recvcount,recvtype,root,comm);
}
int MPI_Allgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Allgather(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm);
}
int MPI_Allgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,const int * recvcounts, const int * displs, MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Allgatherv(sendbuf,sendcount,sendtype,recvbuf,recvcounts,displs,recvtype,comm);
}
int MPI_Alltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Alltoall(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm);
}
int MPI_Alltoallv(const void * sendbuf, const int * sendcounts, const int * sdispls,MPI_Datatype sendtype, void * recvbuf, const int * recvcounts,const int * rdispls, MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Alltoallv(sendbuf,sendcounts,sdispls,sendtype,recvbuf,recvcounts,rdispls,recvtype,comm);
}
int MPI_Alltoallw(const void * sendbuf, const int sendcounts[], const int sdispls[],const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[],const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Alltoallw(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,recvcounts,rdispls,recvtypes,comm);
}
int MPI_Exscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype,MPI_Op op, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Exscan(sendbuf,recvbuf,count,datatype,op,comm);
}
int MPI_Reduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype,MPI_Op op, int root, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Reduce(sendbuf,recvbuf,count,datatype,op,root,comm);
}
int MPI_Allreduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype,MPI_Op op, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Allreduce(sendbuf,recvbuf,count,datatype,op,comm);
}
int MPI_Reduce_scatter(const void * sendbuf, void * recvbuf, const int recvcounts[],MPI_Datatype datatype, MPI_Op op, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Reduce_scatter(sendbuf,recvbuf,recvcounts,datatype,op,comm);
}
int MPI_Scan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op,MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Scan(sendbuf,recvbuf,count,datatype,op,comm);
}
int MPI_Comm_group(MPI_Comm comm, MPI_Group * group){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_group(comm,group);
}
int MPI_Comm_size(MPI_Comm comm, int * size){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_size(comm,size);
}
int MPI_Comm_rank(MPI_Comm comm, int * rank){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_rank(comm,rank);
}
int MPI_Comm_compare(MPI_Comm comm1, MPI_Comm comm2, int * result){
  if(comm1 == MPI_COMM_WORLD){comm1 = MPI_COMM_SMALLER_WORLD;}
  if(comm2 == MPI_COMM_WORLD){comm2 = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_compare(comm1,comm2,result);
}
int MPI_Comm_dup(MPI_Comm comm, MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_dup(comm,newcomm);
}
int MPI_Comm_dup_with_info(MPI_Comm comm, MPI_Info info, MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_dup_with_info(comm,info,newcomm);
}
int MPI_Comm_create(MPI_Comm comm, MPI_Group group, MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_create(comm,group,newcomm);
}
int MPI_Comm_split(MPI_Comm comm, int color, int key, MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_split(comm,color,key,newcomm);
}
int MPI_Comm_test_inter(MPI_Comm comm, int * flag){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_test_inter(comm,flag);
}
int MPI_Comm_remote_size(MPI_Comm comm, int * size){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_remote_size(comm,size);
}
int MPI_Comm_remote_group(MPI_Comm comm, MPI_Group * group){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_remote_group(comm,group);
}
int MPI_Intercomm_create(MPI_Comm local_comm, int local_leader, MPI_Comm peer_comm,int remote_leader, int tag, MPI_Comm * newintercomm){
  if(local_comm == MPI_COMM_WORLD){local_comm = MPI_COMM_SMALLER_WORLD;}
  if(peer_comm == MPI_COMM_WORLD){peer_comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Intercomm_create(local_comm,local_leader,peer_comm,remote_leader,tag,newintercomm);
}
int MPI_Intercomm_merge(MPI_Comm intercomm, int high, MPI_Comm * newintracomm){
  if(intercomm == MPI_COMM_WORLD){intercomm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Intercomm_merge(intercomm,high,newintracomm);
}
int MPI_Attr_put(MPI_Comm comm, int keyval, void * attribute_val){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Attr_put(comm,keyval,attribute_val);
}
int MPI_Attr_get(MPI_Comm comm, int keyval, void * attribute_val, int * flag){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Attr_get(comm,keyval,attribute_val,flag);
}
int MPI_Attr_delete(MPI_Comm comm, int keyval){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Attr_delete(comm,keyval);
}
int MPI_Topo_test(MPI_Comm comm, int * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Topo_test(comm,status);
}
int MPI_Cart_create(MPI_Comm comm_old, int ndims, const int dims[], const int periods[],int reorder, MPI_Comm * comm_cart){
  if(comm_old == MPI_COMM_WORLD){comm_old = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_create(comm_old,ndims,dims,periods,reorder,comm_cart);
}
int MPI_Graph_create(MPI_Comm comm_old, int nnodes, const int indx[], const int edges[],int reorder, MPI_Comm * comm_graph){
  if(comm_old == MPI_COMM_WORLD){comm_old = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Graph_create(comm_old,nnodes,indx,edges,reorder,comm_graph);
}
int MPI_Graphdims_get(MPI_Comm comm, int * nnodes, int * nedges){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Graphdims_get(comm,nnodes,nedges);
}
int MPI_Graph_get(MPI_Comm comm, int maxindex, int maxedges, int indx[], int edges[]){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Graph_get(comm,maxindex,maxedges,indx,edges);
}
int MPI_Cartdim_get(MPI_Comm comm, int * ndims){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cartdim_get(comm,ndims);
}
int MPI_Cart_get(MPI_Comm comm, int maxdims, int dims[], int periods[], int coords[]){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_get(comm,maxdims,dims,periods,coords);
}
int MPI_Cart_rank(MPI_Comm comm, const int coords[], int * rank){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_rank(comm,coords,rank);
}
int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdims, int coords[]){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_coords(comm,rank,maxdims,coords);
}
int MPI_Graph_neighbors_count(MPI_Comm comm, int rank, int * nneighbors){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Graph_neighbors_count(comm,rank,nneighbors);
}
int MPI_Graph_neighbors(MPI_Comm comm, int rank, int maxneighbors, int neighbors[]){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Graph_neighbors(comm,rank,maxneighbors,neighbors);
}
int MPI_Cart_shift(MPI_Comm comm, int direction, int disp, int * rank_source, int * rank_dest){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_shift(comm,direction,disp,rank_source,rank_dest);
}
int MPI_Cart_sub(MPI_Comm comm, const int remain_dims[], MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_sub(comm,remain_dims,newcomm);
}
int MPI_Cart_map(MPI_Comm comm, int ndims, const int dims[], const int periods[], int * newrank){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Cart_map(comm,ndims,dims,periods,newrank);
}
int MPI_Graph_map(MPI_Comm comm, int nnodes, const int indx[], const int edges[], int * newrank){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Graph_map(comm,nnodes,indx,edges,newrank);
}
int MPI_Errhandler_set(MPI_Comm comm, MPI_Errhandler errhandler){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Errhandler_set(comm,errhandler);
}
int MPI_Errhandler_get(MPI_Comm comm, MPI_Errhandler * errhandler){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Errhandler_get(comm,errhandler);
}
int MPI_DUP_FN(MPI_Comm oldcomm, int keyval, void * extra_state, void * attribute_val_in,void * attribute_val_out, int * flag){
  if(oldcomm == MPI_COMM_WORLD){oldcomm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_DUP_FN(oldcomm,keyval,extra_state,attribute_val_in,attribute_val_out,flag);
}
int MPI_Comm_accept(const char * port_name, MPI_Info info, int root, MPI_Comm comm,MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_accept(port_name,info,root,comm,newcomm);
}
int MPI_Comm_connect(const char * port_name, MPI_Info info, int root, MPI_Comm comm,MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_connect(port_name,info,root,comm,newcomm);
}
int MPI_Comm_set_info(MPI_Comm comm, MPI_Info info){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_set_info(comm,info);
}
int MPI_Comm_get_info(MPI_Comm comm, MPI_Info * info){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_get_info(comm,info);
}
int MPI_Win_create(void * base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm,MPI_Win * win){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Win_create(base,size,disp_unit,info,comm,win);
}
int MPI_Win_allocate(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, void * baseptr,MPI_Win * win){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Win_allocate(size,disp_unit,info,comm,baseptr,win);
}
int MPI_Win_allocate_shared(MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm,void * baseptr, MPI_Win * win){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Win_allocate_shared(size,disp_unit,info,comm,baseptr,win);
}
int MPI_Win_create_dynamic(MPI_Info info, MPI_Comm comm, MPI_Win * win){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Win_create_dynamic(info,comm,win);
}
int MPI_Comm_call_errhandler(MPI_Comm comm, int errorcode){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_call_errhandler(comm,errorcode);
}
int MPI_Comm_delete_attr(MPI_Comm comm, int comm_keyval){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_delete_attr(comm,comm_keyval);
}
int MPI_Comm_get_attr(MPI_Comm comm, int comm_keyval, void * attribute_val, int * flag){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_get_attr(comm,comm_keyval,attribute_val,flag);
}
int MPI_Comm_get_name(MPI_Comm comm, char * comm_name, int * resultlen){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_get_name(comm,comm_name,resultlen);
}
int MPI_Comm_set_attr(MPI_Comm comm, int comm_keyval, void * attribute_val){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_set_attr(comm,comm_keyval,attribute_val);
}
int MPI_Comm_set_name(MPI_Comm comm, const char * comm_name){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_set_name(comm,comm_name);
}
int MPI_Comm_get_errhandler(MPI_Comm comm, MPI_Errhandler * errhandler){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_get_errhandler(comm,errhandler);
}
int MPI_Comm_set_errhandler(MPI_Comm comm, MPI_Errhandler errhandler){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_set_errhandler(comm,errhandler);
}
int MPI_Reduce_scatter_block(const void * sendbuf, void * recvbuf, int recvcount,MPI_Datatype datatype, MPI_Op op, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Reduce_scatter_block(sendbuf,recvbuf,recvcount,datatype,op,comm);
}
int MPI_Dist_graph_create_adjacent(MPI_Comm comm_old, int indegree, const int sources[],const int sourceweights[], int outdegree,const int destinations[], const int destweights[],MPI_Info info, int reorder, MPI_Comm * comm_dist_graph){
  if(comm_old == MPI_COMM_WORLD){comm_old = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Dist_graph_create_adjacent(comm_old,indegree,sources,sourceweights,outdegree,destinations,destweights,info,reorder,comm_dist_graph);
}
int MPI_Dist_graph_create(MPI_Comm comm_old, int n, const int sources[], const int degrees[],const int destinations[], const int weights[], MPI_Info info,int reorder, MPI_Comm * comm_dist_graph){
  if(comm_old == MPI_COMM_WORLD){comm_old = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Dist_graph_create(comm_old,n,sources,degrees,destinations,weights,info,reorder,comm_dist_graph);
}
int MPI_Dist_graph_neighbors_count(MPI_Comm comm, int * indegree, int * outdegree, int * weighted){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Dist_graph_neighbors_count(comm,indegree,outdegree,weighted);
}
int MPI_Dist_graph_neighbors(MPI_Comm comm, int maxindegree, int sources[], int sourceweights[],int maxoutdegree, int destinations[], int destweights[]){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Dist_graph_neighbors(comm,maxindegree,sources,sourceweights,maxoutdegree,destinations,destweights);
}
int MPI_Improbe(int source, int tag, MPI_Comm comm, int * flag, MPI_Message * message,MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Improbe(source,tag,comm,flag,message,status);
}
int MPI_Mprobe(int source, int tag, MPI_Comm comm, MPI_Message * message, MPI_Status * status){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Mprobe(source,tag,comm,message,status);
}
int MPI_Comm_idup(MPI_Comm comm, MPI_Comm * newcomm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_idup(comm,newcomm,request);
}
int MPI_Ibarrier(MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ibarrier(comm,request);
}
int MPI_Ibcast(void * buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ibcast(buffer,count,datatype,root,comm,request);
}
int MPI_Igather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Igather(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,root,comm,request);
}
int MPI_Igatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,const int recvcounts[], const int displs[], MPI_Datatype recvtype, int root,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Igatherv(sendbuf,sendcount,sendtype,recvbuf,recvcounts,displs,recvtype,root,comm,request);
}
int MPI_Iscatter(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, int root, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iscatter(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,root,comm,request);
}
int MPI_Iscatterv(const void * sendbuf, const int sendcounts[], const int displs[],MPI_Datatype sendtype, void * recvbuf, int recvcount, MPI_Datatype recvtype,int root, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iscatterv(sendbuf,sendcounts,displs,sendtype,recvbuf,recvcount,recvtype,root,comm,request);
}
int MPI_Iallgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iallgather(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,request);
}
int MPI_Iallgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,const int recvcounts[], const int displs[], MPI_Datatype recvtype,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iallgatherv(sendbuf,sendcount,sendtype,recvbuf,recvcounts,displs,recvtype,comm,request);
}
int MPI_Ialltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype, void * recvbuf,int recvcount, MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ialltoall(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,request);
}
int MPI_Ialltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[],MPI_Datatype sendtype, void * recvbuf, const int recvcounts[],const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ialltoallv(sendbuf,sendcounts,sdispls,sendtype,recvbuf,recvcounts,rdispls,recvtype,comm,request);
}
int MPI_Ialltoallw(const void * sendbuf, const int sendcounts[], const int sdispls[],const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[],const int rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ialltoallw(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,recvcounts,rdispls,recvtypes,comm,request);
}
int MPI_Ireduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype,MPI_Op op, int root, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ireduce(sendbuf,recvbuf,count,datatype,op,root,comm,request);
}
int MPI_Iallreduce(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype,MPI_Op op, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iallreduce(sendbuf,recvbuf,count,datatype,op,comm,request);
}
int MPI_Ireduce_scatter(const void * sendbuf, void * recvbuf, const int recvcounts[],MPI_Datatype datatype, MPI_Op op, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ireduce_scatter(sendbuf,recvbuf,recvcounts,datatype,op,comm,request);
}
int MPI_Ireduce_scatter_block(const void * sendbuf, void * recvbuf, int recvcount,MPI_Datatype datatype, MPI_Op op, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ireduce_scatter_block(sendbuf,recvbuf,recvcount,datatype,op,comm,request);
}
int MPI_Iscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype, MPI_Op op,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iscan(sendbuf,recvbuf,count,datatype,op,comm,request);
}
int MPI_Iexscan(const void * sendbuf, void * recvbuf, int count, MPI_Datatype datatype,MPI_Op op, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Iexscan(sendbuf,recvbuf,count,datatype,op,comm,request);
}
int MPI_Ineighbor_allgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype,void * recvbuf, int recvcount, MPI_Datatype recvtype,MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ineighbor_allgather(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,request);
}
int MPI_Ineighbor_allgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype,void * recvbuf, const int recvcounts[], const int displs[],MPI_Datatype recvtype, MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ineighbor_allgatherv(sendbuf,sendcount,sendtype,recvbuf,recvcounts,displs,recvtype,comm,request);
}
int MPI_Ineighbor_alltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype,void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ineighbor_alltoall(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm,request);
}
int MPI_Ineighbor_alltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[],MPI_Datatype sendtype, void * recvbuf, const int recvcounts[],const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm,MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ineighbor_alltoallv(sendbuf,sendcounts,sdispls,sendtype,recvbuf,recvcounts,rdispls,recvtype,comm,request);
}
int MPI_Ineighbor_alltoallw(const void * sendbuf, const int sendcounts[],const MPI_Aint sdispls[], const MPI_Datatype sendtypes[],void * recvbuf, const int recvcounts[], const MPI_Aint rdispls[],const MPI_Datatype recvtypes[], MPI_Comm comm, MPI_Request * request){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Ineighbor_alltoallw(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,recvcounts,rdispls,recvtypes,comm,request);
}
int MPI_Neighbor_allgather(const void * sendbuf, int sendcount, MPI_Datatype sendtype,void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Neighbor_allgather(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm);
}
int MPI_Neighbor_allgatherv(const void * sendbuf, int sendcount, MPI_Datatype sendtype,void * recvbuf, const int recvcounts[], const int displs[],MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Neighbor_allgatherv(sendbuf,sendcount,sendtype,recvbuf,recvcounts,displs,recvtype,comm);
}
int MPI_Neighbor_alltoall(const void * sendbuf, int sendcount, MPI_Datatype sendtype,void * recvbuf, int recvcount, MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Neighbor_alltoall(sendbuf,sendcount,sendtype,recvbuf,recvcount,recvtype,comm);
}
int MPI_Neighbor_alltoallv(const void * sendbuf, const int sendcounts[], const int sdispls[],MPI_Datatype sendtype, void * recvbuf, const int recvcounts[],const int rdispls[], MPI_Datatype recvtype, MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Neighbor_alltoallv(sendbuf,sendcounts,sdispls,sendtype,recvbuf,recvcounts,rdispls,recvtype,comm);
}
int MPI_Neighbor_alltoallw(const void * sendbuf, const int sendcounts[], const MPI_Aint sdispls[],const MPI_Datatype sendtypes[], void * recvbuf, const int recvcounts[],const MPI_Aint rdispls[], const MPI_Datatype recvtypes[], MPI_Comm comm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Neighbor_alltoallw(sendbuf,sendcounts,sdispls,sendtypes,recvbuf,recvcounts,rdispls,recvtypes,comm);
}
int MPI_Comm_split_type(MPI_Comm comm, int split_type, int key, MPI_Info info, MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_split_type(comm,split_type,key,info,newcomm);
}
int MPI_Comm_create_group(MPI_Comm comm, MPI_Group group, int tag, MPI_Comm * newcomm){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPI_Comm_create_group(comm,group,tag,newcomm);
}
int MPIX_Comm_group_failed(MPI_Comm comm, MPI_Group * failed_group){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPIX_Comm_group_failed(comm,failed_group);
}
int MPIX_Comm_remote_group_failed(MPI_Comm comm, MPI_Group * failed_group){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPIX_Comm_remote_group_failed(comm,failed_group);
}
int MPIX_Comm_reenable_anysource(MPI_Comm comm, MPI_Group * failed_group){
  if(comm == MPI_COMM_WORLD){comm = MPI_COMM_SMALLER_WORLD;}
  return PMPIX_Comm_reenable_anysource(comm,failed_group);
}
#ifdef MPICH_VERSION
#pragma weak MPI_INIT = mpi_init_f
#pragma weak mpi_init = mpi_init_f
#pragma weak mpi_init_ = mpi_init_f
#pragma weak mpi_init__ = mpi_init_f
void MPI_INIT (MPI_Fint* v1);
void mpi_init (MPI_Fint* v1);
void mpi_init_ (MPI_Fint* v1);
void mpi_init__ (MPI_Fint* v1);
void mpi_init_f (MPI_Fint* v1){
    *v1 = MPI_Init( 0, 0 );
}

#pragma weak MPI_COMM_RANK = mpi_comm_rank_f
#pragma weak mpi_comm_rank = mpi_comm_rank_f
#pragma weak mpi_comm_rank_ = mpi_comm_rank_f
#pragma weak mpi_comm_rank__ = mpi_comm_rank_f
void MPI_COMM_RANK (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_rank (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_rank_ (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_rank__ (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_rank_f (void* v1,void* v2,MPI_Fint* v3){
    *v3 = MPI_Comm_rank( (MPI_Comm)(*((MPI_Fint*)v1)), v2 ) ;
}

#pragma weak MPI_COMM_SIZE = mpi_comm_size_f
#pragma weak mpi_comm_size = mpi_comm_size_f
#pragma weak mpi_comm_size_ = mpi_comm_size_f
#pragma weak mpi_comm_size__ = mpi_comm_size_f
void MPI_COMM_SIZE (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_size (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_size_ (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_size__ (void* v1,void* v2,MPI_Fint* v3);
void mpi_comm_size_f (void* v1,void* v2,MPI_Fint* v3){
    *v3 = MPI_Comm_size( (MPI_Comm)(*((MPI_Fint*)v1)), v2 );
}

#pragma weak MPI_BCAST = mpi_bcast_f
#pragma weak mpi_bcast = mpi_bcast_f
#pragma weak mpi_bcast_ = mpi_bcast_f
#pragma weak mpi_bcast__ = mpi_bcast_f
void MPI_BCAST (void* v1,void* v2,void* v3,void* v4,void* v5,MPI_Fint* v6);
void mpi_bcast (void* v1,void* v2,void* v3,void* v4,void* v5,MPI_Fint* v6);
void mpi_bcast_ (void* v1,void* v2,void* v3,void* v4,void* v5,MPI_Fint* v6);
void mpi_bcast__ (void* v1,void* v2,void* v3,void* v4,void* v5,MPI_Fint* v6);
void mpi_bcast_f (void* v1,void* v2,void* v3,void* v4,void* v5,MPI_Fint* v6){
    *v6 = MPI_Bcast(v1, (int)*(MPI_Fint*)v2, (MPI_Datatype)(*(MPI_Fint*)v3), (int)*(int*)v4, (MPI_Comm)(*(MPI_Fint*)v5) );
}

#pragma weak MPI_ISEND = mpi_isend_f
#pragma weak mpi_isend = mpi_isend_f
#pragma weak mpi_isend_ = mpi_isend_f
#pragma weak mpi_isend__ = mpi_isend_f
void MPI_ISEND (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_isend (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_isend_ (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_isend__ (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_isend_f (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8){
    *v8 = MPI_Isend(v1, (int)*(MPI_Fint*)v2, (MPI_Datatype)(*(MPI_Fint*)v3), (int)*(MPI_Fint*)v4, (int)*(MPI_Fint*)v5, (MPI_Comm)(*(MPI_Fint*)v6), (MPI_Request *)(v7) );
}

#pragma weak MPI_IRECV = mpi_irecv_f
#pragma weak mpi_irecv = mpi_irecv_f
#pragma weak mpi_irecv_ = mpi_irecv_f
#pragma weak mpi_irecv__ = mpi_irecv_f
void MPI_IRECV (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_irecv (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_irecv_ (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_irecv__ (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8);
void mpi_irecv_f (void* v1,void* v2,void* v3,void* v4,void* v5,void* v6,void* v7,MPI_Fint* v8){
    *v8 = MPI_Irecv( v1, (int)*(MPI_Fint*)v2, (MPI_Datatype)(*(MPI_Fint*)v3), (int)*(MPI_Fint*)v4, (int)*(MPI_Fint*)v5, (MPI_Comm)(*(MPI_Fint*)v6), (MPI_Request *)(v7) );
}

#pragma weak MPI_WAITALL = mpi_waitall_f
#pragma weak mpi_waitall = mpi_waitall_f
#pragma weak mpi_waitall_ = mpi_waitall_f
#pragma weak mpi_waitall__ = mpi_waitall_f
void MPI_WAITALL (void* v1,void* v2,void* v3,MPI_Fint* v4);
void mpi_waitall (void* v1,void* v2,void* v3,MPI_Fint* v4);
void mpi_waitall_ (void* v1,void* v2,void* v3,MPI_Fint* v4);
void mpi_waitall__ (void* v1,void* v2,void* v3,MPI_Fint* v4);
void mpi_waitall_f (void* v1,void* v2,void* v3,MPI_Fint* v4){
    if (v3 == MPI_F_STATUSES_IGNORE) { v3 = (void *)MPI_STATUSES_IGNORE; }
    *v4 = MPI_Waitall( (int)*(MPI_Fint*)v1, (MPI_Request *)(v2), (MPI_Status *)v3 );
}

#pragma weak MPI_BARRIER = mpi_barrier_f
#pragma weak mpi_barrier = mpi_barrier_f
#pragma weak mpi_barrier_ = mpi_barrier_f
#pragma weak mpi_barrier__ = mpi_barrier_f
void MPI_BARRIER (void* v1,MPI_Fint* v2);
void mpi_barrier (void* v1,MPI_Fint* v2);
void mpi_barrier_ (void* v1,MPI_Fint* v2);
void mpi_barrier__ (void* v1,MPI_Fint* v2);
void mpi_barrier_f (void* v1,MPI_Fint* v2){
    *v2 = MPI_Barrier( (MPI_Comm)(*(MPI_Fint*)v1) );
}

#endif
