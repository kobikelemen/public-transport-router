#include "shortest_path.h"
#include <math.h>

float walk_time(int start_e, int end_e, int start_n, int end_n)
{
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

    float inf = 10e10;
    int prev[num_bs];
    float time[num_bs];
    int processed[num_bs];
    int busroute[num_bs];
    float min_time_toend = inf;
    int last_bs;
    
    for (int i=0; i < num_bs; i++) {
        time[i] = walk_time(start_e, (bs_array[i])->easting, start_n, (bs_array[i])->northing);    
        prev[i] = -1;
        processed[i] = 0;
    }

    int u;
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
        // update Q
        float min = inf;
        for (int i=0; i < num_bs; i ++ ) {
            if ((time[i] < min) && !processed[i]) {
                u = i;
                min = time[i];
            }
        }
    }

    save_path(&busroute,bs_array, prev, time, last_bs, min_time_toend);    
}   





