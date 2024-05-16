#include<merge_sort.h>
ALLEGRO_DISPLAY *display=NULL;

int main(int argc, char **argv){
    clock_t start_time;
    clock_t finish_time;
    start_time=clock();
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
    N=256*4;
    if (rank==0){
        std:: cout<<"N"<< std:: endl;
        std:: cout<<N<< std:: endl;
    }

    parallel_merge(RANK, rank,size, N);
    if (rank==0){
        finish_time=clock();
        std:: cout<< "TIME:"<< std:: endl;
        std:: cout<<(finish_time-start_time)/CLOCKS_PER_SEC<< std:: endl;
    }
    return 0;
    MPI_Finalize();
}
