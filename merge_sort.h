#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include <draw.h>

void merge_no(int *mas,int left, int m , int right, int N  )
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

void merge(int *mas, int left, int m , int right, int N,int rank  )
{

    draw_rectangles(mas, N, rank );
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

     draw_rectangles(mas, N,rank);
}

void merge_no(int *mas,int left, int m , int right, int N,int rank  )
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
void merge_sort (int *mas,int left,int right, int N, int rank){
    if (left<right){

        int m;
        m=(left+right)/2;
        merge_sort(mas,left,m, N, rank);

        merge_sort(mas, m+1,right, N, rank);

        merge_no(mas, left, m , right,N, rank);

    }



}

void merge_sort_no (int *mas,int left,int right, int N, int rank){

    if (left<right){
        draw_rectangles(mas, N,rank);
        int m;
        m=(left+right)/2;
        merge_sort_no(mas,left,m, N,rank);

        draw_rectangles(mas, N,rank);
        merge_sort_no(mas, m+1,right, N,rank);

        draw_rectangles(mas,N,rank);
        merge(mas, left, m , right,N,rank);
        draw_rectangles(mas, N,rank);
    }

     draw_rectangles(mas, N,rank);

}


int * merge_mas_no(int *First, int Fsize, int *Second, int Ssize, int rank) {
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


  if (fi >= Fsize){
        for (i = mi; i < Msize; i++, si++)
            merged[i] = Second[si];


  }

  else if (si >= Ssize){
        for (i = mi; i < Msize; i++, fi++)
            merged[i] = First[fi];


  }
  return merged;

 }
int * merge_mas(int *First, int Fsize, int *Second, int Ssize, int rank) {
  int fi = 0, si = 0, mi = 0, i;
  int *merged;
  int Msize = Fsize+Ssize;

  int *shows=new int[Msize];
  int tmp;
  tmp=0;
  for (int i=0; i<Fsize; i++){
      shows[tmp]=First[i];
      tmp+=1;

  }
  for (int i=0; i<Ssize; i++){
      shows[tmp]=Second[i];
      tmp+=1;
  }
  draw_rectangles(shows, Msize,rank);

  tmp=0;

  merged = (int *)malloc(Msize*sizeof(int));
  while ((fi < Fsize) && (si < Ssize)) {
    if (First[fi] <= Second[si]) {
      merged[mi] = First[fi];
      shows[tmp]=First[fi];
      draw_rectangles(shows, Msize, rank);
      mi++; fi++;
      tmp++;
    }
    else  {
      merged[mi] = Second[si];
      shows[tmp] = Second[si];
      draw_rectangles(shows, Msize, rank);
      mi++; si++;tmp++;
    }
     draw_rectangles(shows, Msize, rank);
  }
  draw_rectangles(shows, Msize, rank);

  if (fi >= Fsize){
        for (i = mi; i < Msize; i++, si++)
            merged[i] = Second[si];
            shows[i] = Second[si];

  }


  else if (si >= Ssize){
        for (i = mi; i < Msize; i++, fi++)
            merged[i] = First[fi];
            shows[i] = First[fi];


  }

  return merged;
  draw_rectangles(merged, Msize, rank);
 }

void parallel_merge (int RANK, int rank,int size,  int N, int * global_mas){
        clock_t start_time ;
        clock_t finish_time;
        start_time=clock();
        int mas_size;
        mas_size=N/size;
        int *mas_local=new int[mas_size];
        if (rank==RANK){
            /*int *global_mas=new int[N];
            for (int i=0; i<N; i++){
                global_mas[i]=rand()%900;
            }*/
            int *mas_t=new int[N];
            draw_rectangles(global_mas,N, rank);
            MPI_Bcast(&mas_size, 1, MPI_INT, RANK, MPI_COMM_WORLD);
            MPI_Scatter(global_mas, mas_size, MPI_INT,mas_local,mas_size, MPI_INT, RANK, MPI_COMM_WORLD);
            merge_sort_no(mas_local,0, mas_size-1, mas_size, rank);
            for (int i=0;i<mas_size; i++) {
                mas_t[i]=mas_local[i];
            }
            for (int i=mas_size; i<N; i++){
                 mas_t[i]=global_mas[i];
            }
            draw_rectangles(mas_t,N, rank);
        }
        else{
            MPI_Bcast(&mas_size, 1, MPI_INT, RANK, MPI_COMM_WORLD);
            MPI_Scatter(global_mas, mas_size, MPI_INT,mas_local,mas_size, MPI_INT, RANK, MPI_COMM_WORLD);
            merge_sort(mas_local, 0, mas_size-1, mas_size, rank);
            //delete []mas_t;

        }

        int step;
        step=1;
               while (step<size){
                   if (rank %(2*step)==0){
                       if (rank+step<size){
                           int count;
                           MPI_Recv(&count,1,MPI_INT, rank+step, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                           int *mas_after_recv=new int[count];
                           MPI_Recv(mas_after_recv,count, MPI_INT, rank+step, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE );

                           if (rank!=0){
                               mas_local=merge_mas_no(mas_after_recv, count,mas_local,mas_size, rank) ;
                           }
                           else{
                               mas_local=merge_mas(mas_after_recv, count,mas_local,mas_size, rank) ;

                           }
                           mas_size=mas_size+count;

                       }

                   }


                       else{

                           int next;
                           next=rank-step;
                           MPI_Send(&mas_size,1, MPI_INT,next, 1, MPI_COMM_WORLD) ;
                           MPI_Send(mas_local, mas_size,MPI_INT, next, 1, MPI_COMM_WORLD);
                           break;

                       }
                   step=step*2;
               }
     finish_time=clock();
     if (rank==0){
         for (int i=0; i<mas_size; i++){
             std::cout<< mas_local[i]<< std:: endl;
         }
       // std:: cout<< "TIME:"<< std:: endl;
        //std:: cout<<(finish_time-start_time)/CLOCKS_PER_SEC<< std:: endl;


     }
     delete [] mas_local;
     MPI_Finalize();
}
#endif // MERGE_SORT_H
