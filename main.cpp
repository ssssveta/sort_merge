#include <merge_sort.h>

int main(int argc, char **argv){
   //show=1;
   //if (show==1){
   al_init();
   al_init_primitives_addon();
   //display=al_create_display(600,600);

   int N;
   N=8;
   int global_1[]={0,1,8,12,9, 67,89,700};
   MPI_Init(&argc, &argv);
   int size;
   int rank;
   int RANK;
   RANK=0;
   MPI_Comm_size(MPI_COMM_WORLD,&size);
   MPI_Comm_rank(MPI_COMM_WORLD,&rank);
   parallel_merge(RANK, rank,size, N, global_1);

   //q.parallel_start(num,size,  N, mas_size , global, RANK);
   //MPI_Barrier(MPI_COMM_WORLD);
   MPI_Finalize();

   return 0;
}

