#ifndef MERGE_SORT_H
#define MERGE_SORT_H
#include <draw.h>

void merge(int *mas, int left, int m , int right, int N,int rank  )
{
    if (rank==0){
        draw_rectangles(mas, N, rank );
     }
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
    if (rank==0){
        draw_rectangles(mas, N,rank);
    }
}


void merge_sort(int *mas,int left,int right, int N, int rank){

    if (left<right){
        //if (rank==0){
         //   draw_rectangles(mas, N,rank);
        //}
        int m;
        m=(left+right)/2;
        merge_sort(mas,left,m, N,rank);
        if (rank==0){
            draw_rectangles(mas, N,rank);
        }
        merge_sort(mas, m+1,right, N,rank);
        if (rank==0){
            draw_rectangles(mas,N,rank);
        }
        merge(mas, left, m , right,N,rank);
        if (rank==0){
            draw_rectangles(mas, N,rank);
        }
    }
     if (rank==0){
        draw_rectangles(mas, N,rank);
     }

}


int * merge_mas(int *mas_1, int size_1, int *mas_2, int size_2, int rank) {
  int first= 0;
  int second = 0;
  int s = 0;
  int i=0;
  int size=size_1+size_2;
  int *sort_mas= new int[size];

  int *shows=new int[size];
  int tmp;
  tmp=0;
  for (int i=0; i<size_1; i++){
      shows[tmp]=mas_1[i];
      tmp+=1;

  }
  for (int i=0; i<size_2; i++){
      shows[tmp]=mas_2[i];
      tmp+=1;
  }
  if (rank==0){
    draw_rectangles(shows,size,rank);
  }
  tmp=0;
  while ((first <size_1) && (second  < size_2)) {
    if (mas_1[first] <= mas_2[second]) {
      sort_mas[s] = mas_1[first];
      shows[tmp]=mas_1[first];
      if (rank==0){
        draw_rectangles(shows,size,rank);
      }
      s++;
      first++;
      tmp++;

    } else {
      sort_mas[s] = mas_2[second];
      shows[tmp]= mas_2[second];
      if (rank==0){
        draw_rectangles(shows,size,rank);
      }
      s++;
      second ++;
      tmp++;
    }
    if (rank==0){
      draw_rectangles(shows,size,rank);
    }
  }

  if (rank==0){
    draw_rectangles(shows,size,rank);
  }
  if (first >= size_1){
        for (i =s; i < size; i++)
            sort_mas[i] = mas_2[second];
            shows[i]=mas_2[second];
            second ++;
  }

  else if (second  >= size_2){
        for (i =s; i < size; i++)
            sort_mas[i] = mas_1[first];
            shows[i] = mas_1[first];
            first++;


  }
  return sort_mas;
  if (rank==0){
    draw_rectangles(shows,size,rank);
  }

 }

void parallel_merge (int RANK, int rank,int size,  int N){
        int mas_size;
        mas_size=N/size;
        int *mas_local=new int[mas_size];
        int *global_mas=new int[N];
        if (rank==RANK){
            for (int i=0; i<N; i++){
                global_mas[i]=rand()%900;
            }
            int *mas_t=new int[N];
            draw_rectangles(global_mas,N, rank);
            MPI_Bcast(&mas_size, 1, MPI_INT, RANK, MPI_COMM_WORLD);
            MPI_Scatter(global_mas, mas_size, MPI_INT,mas_local,mas_size, MPI_INT, RANK, MPI_COMM_WORLD);
            merge_sort(mas_local,0, mas_size-1, mas_size, rank);
            /*
            for (int i=0;i<mas_size; i++) {
                mas_t[i]=mas_local[i];
            }
            for (int i=mas_size; i<N; i++){
                 mas_t[i]=global_mas[i];
            }
            */
            //draw_rectangles(mas_t,N, rank);
        }
        else{
            MPI_Bcast(&mas_size, 1, MPI_INT, RANK, MPI_COMM_WORLD);
            MPI_Scatter(global_mas, mas_size, MPI_INT,mas_local,mas_size, MPI_INT, RANK, MPI_COMM_WORLD);
            merge_sort(mas_local, 0, mas_size-1, mas_size, rank);

        }

        int step;
        step=1;
               while (step<size){
                   if (rank %(2*step)==0){
                           int count;
                           MPI_Recv(&count,1,MPI_INT, rank+step, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                           int *mas_after_recv=new int[count];
                           MPI_Recv(mas_after_recv,count, MPI_INT, rank+step, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE );
                           mas_local=merge_mas (mas_after_recv, count,mas_local,mas_size, rank) ;
                           mas_size=mas_size+count;

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
/*
     if (rank==0){
         std:: cout<< "TIME:"<< std:: endl;
         std:: cout<<(finish_time-start_time)/CLOCKS_PER_SEC<< std:: endl;
         //for (int i=0; i<mas_size; i++){
             //std::cout<< mas_local[i]<< std:: endl;
     }

*/


     delete [] mas_local;

}
#endif // MERGE_SORT_H
