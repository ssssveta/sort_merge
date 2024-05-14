#ifndef DRAW_MERGE_H
#define DRAW_MERGE_H
#include <draw.h>


void merge(int *mas, int left, int m , int right, int N, int rank)
{
    if (rank==0){
        draw_rectangles(mas, N);
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
            t+=1;
            i+=1;

        }
        else{
            mas_tmp[t]=mas[j];
            j+=1;
            t+=1;

        }
    }
    while (i<=m){
        mas_tmp[t]=mas[i];
        i+=1;
        t+=1;
    }
    while (j<=right){
        mas_tmp[t]=mas[j];
        j+=1;
        t+=1;
    }
    for (int s=left; s<=right; s++){
        mas[s]=mas_tmp[s];
    }
    if (rank==0){
        draw_rectangles(mas, N);
     }
}

void merge_sort(int *mas,int left,int right, int N, int rank){

    if (left<right){
        if (rank==0){
            draw_rectangles(mas, N);
         }
        int m;
        m=(left+right)/2;
        merge_sort(mas,left,m, N,rank);
        if (rank==0){
            draw_rectangles(mas, N);
         }
        merge_sort(mas, m+1,right, N,rank);
        if (rank==0){
            draw_rectangles(mas, N);
         }
        merge(mas, left, m , right,N,rank);
        if (rank==0){
            draw_rectangles(mas, N);
         }
    }
    if (rank==0){
        draw_rectangles(mas, N);
     }
}

int * merge_mas(int *mas_1, int mas_size_1, int *mas_2, int mas_size_2, int rank) {
        int index_first;
        int index_second;
        int index;
        int size;
        int tmp;
        int i;
        index_first=0;
        index_second=0;
        index=0;
        tmp=0;
        size=mas_size_1+mas_size_2;
        int *merge_mas=new int [size];
        int *shows=new int[size];
        for (int i=0;i< mas_size_1; i++){
            shows[tmp]=mas_1[i];
            tmp+=1;
        }
        for (int i=0;i< mas_size_2; i++){
            shows[tmp]=mas_2[i];
            tmp+=1;
        }
        if (rank==0){
            draw_rectangles(shows, size);
         }
        tmp=0;
        while ((index_first<mas_size_1) && (index_second<mas_size_2)){
                if (mas_1[index_first]<=mas_2[index_second]){
                    merge_mas[index]=mas_1[index_first];
                    shows[tmp]=mas_1[index_first];
                    if (rank==0){
                        draw_rectangles(shows, size);
                     }
                    index+=1;
                    index_first+=1;
                    tmp+=1;
                }
                else{
                    merge_mas[index]=mas_2[index_second];
                    shows[tmp]=mas_2[index_second];
                    if (rank==0){
                        draw_rectangles(shows, size);
                     }
                    index+=1;
                    index_second+=1;
                    tmp+=1;
                }
                if (rank==0){
                    draw_rectangles(shows, size);
                 }
        }
        if (rank==0){
            draw_rectangles(shows, size);
         }
        if (index_first>=mas_size_1){
            for (i=index;i<size;i++)
                merge_mas[i]=mas_2[index_second];
                shows[i]=mas_2[index_second];
                index_second+=1;

        }
        else if (index_second>=mas_size_2){
            for (i=index;i<size; i++)
                merge_mas[i]=mas_2[index_first];
                shows[i]=mas_2[index_first];
                index_first+=1;
        }
        return merge_mas;
        if (rank==0){
            draw_rectangles(shows, size);
         }


}
#endif // DRAW_MERGE_H
