#include "shortest_path.h"
#include <math.h>

float walk_time(int start_e, int end_e, int start_n, int end_n)
{
    // assuming 1 easting/ northing is 1 metre
    float walkspeed = 1.4;
    float dist = sqrt(pow(start_e-end_e, 2) + pow(start_n-end_n, 2));
    return dist / walkspeed;
}





void dijkstras(int start_e, int start_n, int end_e, int end_n, neighbour * bs_graph[], bus_stop * bs_array[], int num_bs, int testids[])
{
    // use array for Q first then improve to priority queue

    float inf = 10e10;
    int prev[num_bs];
    float time[num_bs];
    // bus_stop * Q[num_bs];
    int processed[num_bs];

    float min_time_toend = inf;
    int last_bs;

    for (int i=0; i < num_bs; i++) {
        time[i] = walk_time(start_e, (bs_array[i])->easting, start_n, (bs_array[i])->northing);
        prev[i] = -1;
        // Q[i] = bs_array[i];
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
        printf("bs_array[u] %s\n", bs_array[u]->name);

        float dist_toend = time[u] + walk_time((bs_array[u])->easting, end_e, (bs_array[u])->northing, end_n);
        if (dist_toend < min_time_toend) {
            min_time_toend = dist_toend;
            last_bs = u;
        }
        neighbour * vneigh = bs_graph[u]; // neighbours of u (current node)
        
        while (vneigh != NULL) {
            int v = vneigh->node->id;
            // if (!processed[v]) {
            float alt = time[u] + vneigh->time;
            if (alt < time[v]) {
                time[v] = vneigh->time;
                prev[v] = u;
            }
            // }
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

    printf("last_bs: %s\n", bs_array[last_bs]->name);


    int x = last_bs;
    printf("\n\nbus path:   ");
    while (x != -1) {
        printf("%s, ", bs_array[x]->name);
        x = prev[x];
    }
    printf("\n");


    printf("numvisited: %i\n", numvisited);
    printf("min timetoend: %f\n", min);    
    

}   

