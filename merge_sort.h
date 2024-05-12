#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <draw.h>

void merge(int *mas,int left, int m , int right, int N )
{
    int i;
    i=left;
    int j;
    j=m+1;
    int t;
    t=left;
    int *mas_tmp=new int [N];
    while ((i<=m) && (j<=right)){
        if (mas[i]<=mas[j]){
            mas_tmp[t]=mas[i];
            t++;
            i++;
        }
        else{
            mas_tmp[t]=mas[j];
            j++;
            t++;
        }
    }
    while (i<=m){
        mas_tmp[t]=mas[i];
        i++;
        t++;
    }
    while (j<=right){
        mas_tmp[t]=mas[j];
        j++;
        t++;
    }
    for (int s=left; s<=right; s++){
        mas[s]=mas_tmp[s];
    }

}

void merge_sort (int *mas,int left,int right, int N){
    if (left<right){
        //{
          //  draw_rectangles(mas);
        //}
        int m;
        m=(left+right)/2;
        merge_sort(mas,left,m, N);
        merge_sort(mas, m+1,right, N);
        merge (mas, left, m , right,N);
    }
}
int * merge_mas(int *First, int Fsize, int *Second, int Ssize) {
  int fi = 0, si = 0, mi = 0, i;
  int *merged;
  int Msize = Fsize+Ssize;

  merged = (int *)malloc(Msize*sizeof(int));
  while ((fi < Fsize) && (si < Ssize)) {
    if (First[fi] <= Second[si]) {
      merged[mi] = First[fi];
      mi++; fi++;
    } else {
      merged[mi] = Second[si];
      mi++; si++;
    }
  }

  if (fi >= Fsize)
    for (i = mi; i < Msize; i++, si++)
      merged[i] = Second[si];
  else if (si >= Ssize)
    for (i = mi; i < Msize; i++, fi++)
      merged[i] = First[fi];

  return merged;
 }
void parallel_merge (int RANK, int rank,int size,  int N, int *global_mas){
        int mas_size;
        mas_size=N/size;
        int *mas_local=new int[mas_size];
        if (rank==RANK){
        //  maibe generate massiv
            MPI_Bcast(&mas_size, 1, MPI_INT, RANK, MPI_COMM_WORLD);

            MPI_Scatter(global_mas, mas_size, MPI_INT,mas_local,mas_size, MPI_INT, RANK, MPI_COMM_WORLD);
            merge_sort(mas_local, 0, mas_size-1, mas_size);
            std:: cout<< "after sort rank 0"<< std:: endl;
            //for (int i=0; i<mas_size; i++){
              //  std:: cout<< mas_local[i]<< std:: endl;
            //}
        }
        else{

            MPI_Bcast(&mas_size, 1, MPI_INT, RANK, MPI_COMM_WORLD);

            MPI_Scatter(global_mas, mas_size, MPI_INT,mas_local,mas_size, MPI_INT, RANK, MPI_COMM_WORLD);

            std:: cout<<"receive_mas" << std:: endl;
            merge_sort(mas_local, 0, mas_size-1, mas_size);
            std:: cout<< " SORT"<< std:: endl;

            //for (int i=0; i<mas_size; i++){
              //  std:: cout<< mas_local[i]<< std:: endl;
            //}

        }
        MPI_Barrier(MPI_COMM_WORLD);
        int step;
        step=1;
        while (step<size){
            if (rank %(2*step)==0){
                if (rank+step<size){
                    std:: cout<<"recv"<< std:: endl;
                    int count;
                    MPI_Recv(&count,1,MPI_INT, rank+step, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    int *mas_after_recv=new int[count];
                    MPI_Recv(mas_after_recv,count, MPI_INT, rank+step, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE );
                    std:: cout<< "mas_local before"<<std:: endl;
                    for (int i=0; i<mas_size; i++){

                        std:: cout<< mas_local[i]<<std:: endl;
                    }
                    mas_local=merge_mas(mas_after_recv, count,mas_local,mas_size) ;
                    //std:: cout<< "size"<< std:: endl;
                    //std:: cout <<mas_size+count<< std:: endl;

                    mas_size=mas_size+count;
                }
            }
                else{
                    std:: cout<<"send"<< std:: endl;
                    int next;
                    next=rank-step;
                    MPI_Send(&mas_size,1, MPI_INT,next, 1, MPI_COMM_WORLD) ;
                    MPI_Send(mas_local, mas_size,MPI_INT, next, 1, MPI_COMM_WORLD);
                    break;

                }
            step=step*2;
        }

        if (rank==0){
            for (int i=0; i<N; i++){
                std:: cout<<"RESULT"<< std:: endl;
                std:: cout<< mas_local[i]<< std:: endl;
            }
       }

    }
#endif // MERGE_SORT_H
