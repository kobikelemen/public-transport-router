#include "shortest_path.h"
#include <math.h>

float walk_time(int start_e, int end_e, int start_n, int end_n)
{
    // assuming 1 easting/ northing is 1 metre
    // float walkspeed = 1.4;
    float walkspeed = 1;
    float dist = sqrt(pow(start_e-end_e, 2) + pow(start_n-end_n, 2));
    return (dist / walkspeed)/60;
}



void save_path(int *busroute, bus_stop * bs_array[], int *prev, float *time, int last_bs, float min_time_toend)
{
    FILE *f = fopen("frontend/route.txt", "w");
    float min_time = 0;
    int x = last_bs;
    while (x != -1) {
        fprintf(f, "%i:%s:%i:%i\n", busroute[x], bs_array[x]->name, bs_array[x]->easting, bs_array[x]->northing);
        min_time += time[x];
        x = prev[x];
    }
    fprintf(f,"Journey time:%f", min_time_toend);
    fclose(f);
}




void dijkstras(int start_e, int start_n, int end_e, int end_n, neighbour * bs_graph[], bus_stop * bs_array[], int num_bs)
{
    // use array for Q first then improve to priority queue

    float inf = 10e10;
    int prev[num_bs];
    float time[num_bs];
    int processed[num_bs];
    int busroute[num_bs];

    
    // for (int e=0; e < num_bs; e++) {
    //     neighbour * vneigh = bs_graph[e];
    //     while (vneigh != NULL) {
    //         printf(" %f", vneigh->time);
    //         vneigh = vneigh->next;
    //     }
    // }

    float min_time_toend = inf;
    int last_bs;
    
    
    for (int i=0; i < num_bs; i++) {
        
        time[i] = walk_time(start_e, (bs_array[i])->easting, start_n, (bs_array[i])->northing);    
        prev[i] = -1;
        processed[i] = 0;
    }


    int u; // id/ index of current node 
    float min = inf;
    
    for (int i=0; i < num_bs; i ++ ) {
        if (time[i] < min) {
            u = i;
            min = time[i];
        }
    }

    int numvisited = 0;
    
    while (!processed[u]) {

        numvisited ++;
        processed[u] = 1;
        float time_toend = time[u] + walk_time((bs_array[u])->easting, end_e, (bs_array[u])->northing, end_n);
        // if (strcmp(bs_array[u]->name, "SURREY QUAYS STATION") == 0) {
        //     printf("\ntime_toend SURREY QUAYS STATION: %f", time_toend);
        //     printf("\n time[u] SURREY QUAYS STATION: %f", time[u]);
        // }

        // if (strcmp(bs_array[u]->name, "BUSH ROAD") == 0) {
        //     printf("\ntime_toend BUSH ROAD: %f", time_toend);
        //     printf("\n time[u] BUSH ROAD: %f", time[u]);
        // }
        if (time_toend < min_time_toend) {
            min_time_toend = time_toend;
            last_bs = u;
        }
        neighbour * vneigh = bs_graph[u]; // neighbours of u (current node)
        
        while (vneigh != NULL) {
            int v = vneigh->node->id;
            float alt = time[u] + vneigh->time;
            if (atoi(vneigh->bus_number) != busroute[u]) {
                alt += 4;
            }
            if (alt < time[v]) {
                time[v] = alt;
                prev[v] = u;
                busroute[v] = atoi(vneigh->bus_number);
            }
            vneigh = vneigh->next;
        }   
        // update Q -
        float min = inf;
        for (int i=0; i < num_bs; i ++ ) {
            if ((time[i] < min) && !processed[i]) {
                u = i;
                min = time[i];
            }
        }
    }

    // printf("\n\nlast_bs: %s\n", bs_array[last_bs]->name);

    save_path(&busroute,bs_array, prev, time, last_bs, min_time_toend);    

}   





