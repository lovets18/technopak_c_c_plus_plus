#pragma once

typedef struct server {
    char dns[16];
    char ip[16];
    char mask[16];
    int processor;
    int core;
} server;


typedef struct set {
    int cur_size;
    int max_size;
    char** host;
} set;

server server_init(char dns[], char ip[], char mask[], int processor, int core, int* flag);

void set_destroy(set* net);

server* create_servers_arr(int size);

set unique_nets_to_set(server* arr, int arrsize);

void destoy_servers_arr(server arr[]);

void print_by_groups(server* serv, int serversize, set net);
