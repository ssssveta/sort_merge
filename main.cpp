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
    if (!al_init()){
            std:: cout<< "init error"<< std:: endl;
    }

        //al_init_primitives_addon();
    display=al_create_display(SCREEN_WIDTH,SCREEN_HEIGHT);
    std:: cout<< "create display"<< std:: endl;

    int N;
    N=8;
    int global_1[]={100, 4 ,6, 25, 30, 250, 60};

    //int *global_1=new int[N];
    //for (int i=0; i<N; i++){
     //   global_1[i]=rand()%400;
    //}
    parallel_merge(RANK, rank,size, N, global_1);
    //delete []global_1;
    MPI_Finalize();
}
