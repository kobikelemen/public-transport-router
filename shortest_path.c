#include "shortest_path.h"
#include <math.h>

float walk_time(int start_e, int end_e, int start_n, int end_n)
{
    // assuming 1 easting/ northing is 1 metre
    float walkspeed = 1.4;
    // float walkspeed = 0.001;
    float dist = sqrt(pow(start_e-end_e, 2) + pow(start_n-end_n, 2));
    return (dist / walkspeed)/60;
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
        if (strcmp(bs_array[i]->name, "BUSH ROAD") == 0) {
            // printf("\ntime_toend BUSH ROAD: %f", time_toend);
            printf("\n time[u] BUSH ROAD: %f", time[i]);
        }
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
        

        // if (strcmp(bs_array[u]->name, "MUSEUM STREET") == 0) {
        //     printf("\n\n MUSEUM STREET FOUND\n\n");
        // }


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
            // printf("\ntime_toend %f", time_toend);
            // printf("\ntime_tohere %f", time[u]);
            min_time_toend = time_toend;
            last_bs = u;
        }
        neighbour * vneigh = bs_graph[u]; // neighbours of u (current node)
        
        while (vneigh != NULL) {
            // printf("\n %s ",  bs_array[u]->name);
            int v = vneigh->node->id;
            float alt = time[u] + vneigh->time;
            // printf("  %s", vneigh->node->name);
            if (alt < time[v]) {
                // printf("\ntime: %f", time[v]);
                // time[v] = vneigh->time;
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

    printf("\n\nlast_bs: %s\n", bs_array[last_bs]->name);


    int x = last_bs;
    float min_time = 0;

    printf("\n\nbus path:   ");
    while (x != -1) {
        printf("  %i  %s, ", busroute[x],bs_array[x]->name);
        
        min_time += time[x];
        x = prev[x];
    }
    printf("\n");
    printf(" Journey time %f ,", min_time_toend); // 188
    
    

}   

