#include<merge_sort.h>
ALLEGRO_DISPLAY *display=NULL;

int main(int argc, char **argv){
    MPI_Init(&argc, &argv);
    int size;
    int rank;
    int RANK;
    RANK=0;
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    if (rank==0){
        if (!al_init()){
            std:: cout<< "init error"<< std:: endl;
        }
        display=al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);
        std:: cout<< "create display"<< std:: endl;
    }
    int N;
    N=80;
    int *global_mas=new int[N];
    for (int i=0; i<N; i++){
        global_mas[i]=rand()%900;
    }
    //N=rand()%100 * size;

    parallel_merge(RANK, rank,size, N, global_mas);

    std:: cout<<"final"<< std:: endl;
    return 0;
}
