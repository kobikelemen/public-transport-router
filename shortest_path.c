#include "shortest_path.h"


float walk_time(int start_e, int end_e, int start_n, int end_n)
{
    
    // based on distance and average walking speed
    return 0;
}




void dijkstras(int start_e, int start_n, int end_e, int end_n, neighbour * bs_graph[], bus_stop * bs_array[], int num_bs)
{
    // use array for Q first then improve to priority queue



    float inf = 10e10;
    bus_stop * prev[num_bs];
    float dist[num_bs];
    // bus_stop * Q[num_bs];
    int processed[num_bs];

    float min_dist_toend = inf;
    bus_stop * last_bs = NULL;

    for (int i=0; i < num_bs; i++) {
        dist[i] = walk_time(start_e, (bs_array[i])->easting, start_n, (bs_array[i])->northing);
        prev[i] = NULL;
        // Q[i] = bs_array[i];
        processed[i] = 0;
    }

    int u; // id/ index of current node 
    float min = inf;
    
    for (int i=0; i < num_bs; i ++ ) {
        if (dist[i] < min) {
            u = i;
            min = dist[i];
        }
    }
    

    while (!processed[u]) {
        processed[u] = 1;

        float dist_toend = dist[u] + walk_time((bs_array[u])->easting, end_e, (bs_array[u])->northing, end_n);
        if (dist_toend < min_dist_toend) {
            min_dist_toend = dist_toend;
            last_bs = (bs_array[u]);
        }
        neighbour * vneigh = bs_graph[u]; // neighbours of u (current node)
        
        while (vneigh != NULL) {
            int v = vneigh->node->id;
            // if (!processed[v]) {
            float alt = dist[u] + vneigh->time;
            if (alt < dist[v]) {
                dist[v] = vneigh->time;
                prev[v] = bs_array[u];
            }
            // }
            vneigh = vneigh->next;
        }
        // update Q -
        float min = inf;
        for (int i=0; i < num_bs; i ++ ) {
            if ((dist[i] < min) && !processed[i]) {
                u = i;
                min = dist[i];
            }
        }
    }

    printf("last_bs: %s\n", last_bs->name);
    

}   

