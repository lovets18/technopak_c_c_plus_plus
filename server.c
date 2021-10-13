#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "server.h"


#define POINT '.'
#define MISTAKE "mistake"
#define ADR_STR_SIZE 16
#define ADR_NUM_SIZE 4


static void get_adress_nums(char addr[], int result[]) {
    if (!addr || !result) {
        return;
    }
    size_t len = (strlen(addr) > (ADR_STR_SIZE-1)) ? (ADR_STR_SIZE-1) : strlen(addr);
    int j = 0, temp = 0;
    for (int i = 0; i < len; ++i) {
        if (addr[i] == POINT) {
            result[j] = temp;
            temp = 0;
            ++j;
            continue;
        }
        temp *= 10;
        temp += addr[i] - '0';

    }
    result[j] = temp;
}

server server_init(char dns[], char ip[], char mask[], int processor, int core, int* flag) {
    server serv;
    int valid_ip_arr[4] = { -1, -1, -1, -1 };
    int valid_mask_arr[4] = { -1, -1, -1, -1 };
    if (strlen(dns) >= 16 || strlen(ip) >= 16 || strlen(mask) >= 16) {
        printf("Wrong line entered! Try again!\n");
        *flag = 0;
        strncpy(serv.dns, MISTAKE, 16 * sizeof(char));
        return serv;
    }
    get_adress_nums(ip, valid_ip_arr);
    get_adress_nums(mask, valid_mask_arr);
    for (int i = 0; i < 4; ++i) {
        if (valid_ip_arr[i] > 255 || valid_ip_arr[i] < 0 || valid_mask_arr[i] > 255 || valid_mask_arr[i] < 0) {
            printf("Wrong line entered! Try again!\n");
            *flag = 0;
            strncpy(serv.dns, "Mistake", 16 * sizeof(char));
            return serv;
        }
    }
    strncpy(serv.dns, dns, 16 * sizeof(char));
    strncpy(serv.ip, ip, 16 * sizeof(char));
    strncpy(serv.mask, mask, 16 * sizeof(char));
    if (processor >= 1) {
        serv.processor = processor;
    }
    else {
        serv.processor = 1;
    }

    if (core >= 1) {
        serv.core = core;
    }
    else {
        serv.core = 1;
    }
    return serv;
}

static void server_print(server test) {

    printf("--------------------------------------\n");

    if (!printf("\t%s\n", test.dns)) {
        printf("Printf returned 0!\n");
        return;
    };

    if (!printf("\t%s\n", test.ip)) {
        printf("Printf returned 0!\n");
        return;
    };

    if (!printf("\t%s\n", test.mask)) {
        printf("Printf returned 0!\n");
        return;
    };

    if (!printf("\t%d\n", test.processor)) {
        printf("Printf returned 0!\n");
        return;
    };

    if (!printf("\t%d\n", test.core)) {
        printf("Printf returned 0!");
        return;
    };

    printf("--------------------------------------\n");

}

static void get_address_str(int adr[], char result[]) {
    if (!adr || !result) {
        return;
    }
    char resstr[ADR_STR_SIZE] = { 0 };
    for (int i = 0; i < ADR_NUM_SIZE - 1; ++i) {
        char tempstr[ADR_NUM_SIZE];
        snprintf(tempstr, ADR_NUM_SIZE, "%d", adr[i]);
        strcat(resstr, tempstr);
        strcat(resstr, ".");
    }
    char tempstr[ADR_NUM_SIZE];
    snprintf(tempstr, ADR_NUM_SIZE, "%d", adr[ADR_NUM_SIZE - 1]);
    strcat(resstr, tempstr);
    strcpy(result, resstr);
}


static void get_network_adress(server serv, int result[]) {
    if (!result) {
        return;
    }
    int ip[ADR_NUM_SIZE] = { 0, 0, 0, 0 }, mask[ADR_NUM_SIZE] = { 0, 0, 0, 0 };
    get_adress_nums(serv.ip, ip);
    get_adress_nums(serv.mask, mask);
    for (int i = 0; i < ADR_NUM_SIZE; ++i) {
        result[i] = (ip[i] & mask[i]);
    }
}


static bool in_set(char elem[], char* set[], int size) {
    if (!set || !elem) {
        return false;
    }
    for (int i = 0; i < size; ++i) {
        if (!strcmp(elem, set[i])) {
            return true;
        }
    }
    return false;
}

static void add_to_set(int elem[], set* net) {
    if (!net || !elem) {
        return;
    }
    if (net->cur_size >= net->max_size) {
        printf("Not enough space in set\n");
        return;
    }
    char* elemstr = (char*)malloc(ADR_STR_SIZE * sizeof(char));
    if (!elemstr) {
        free(elemstr);
        elemstr = NULL;
        printf("Exception\n");
        return;
    }
    get_address_str(elem, elemstr);


    if (in_set(elemstr, net->host, net->cur_size)) {
        free(elemstr);
        elemstr = NULL;
        return;
    }

    strcpy(net->host[net->cur_size], elemstr);
    ++net->cur_size;
    free(elemstr);
    elemstr = NULL;
}

static set set_init(int max_size) {
    if (max_size < 0) {
        max_size = 0;
    }
    set net;
    net.cur_size = 0;
    net.max_size = max_size;
    net.host = (char**)malloc(max_size * sizeof(char*));
    if (!net.host) {
        printf("Set wasn't created!\n");
        net.max_size = 0;
        return net;
    }
    for (int i = 0; i < max_size; ++i) {
        net.host[i] = (char*)malloc(ADR_STR_SIZE * sizeof(char));
        if (!net.host[i]) {
            printf("The size of set was shortened!\n");
            net.max_size = i;
            return net;
        }
    }
    return net;
}

set unique_nets_to_set(server serv_arr[], int arrsize) {
    set net = set_init(arrsize);
    set* netptr = &net;
    if (!serv_arr || !netptr) {
        return net;
    }
    for (int i = 0; i < arrsize; ++i) {
        int arr[ADR_NUM_SIZE] = { 0, 0, 0, 0 };
        get_network_adress(serv_arr[i], arr);
        add_to_set(arr, netptr);
    }
    return net;
}

void set_destroy(set* net) {
    for (int i = 0; i < net->max_size; i++) {
        free(net->host[i]);
    }
    net->cur_size = 0;
    net->max_size = 0;
    free(net->host);
    net->host = NULL;
}

server* create_servers_arr(int size) {
    size_t arr_size = (size > 0) ? size : 0;
    server* net = (server*)malloc(arr_size * sizeof(server));
    if (!net) {
        printf("Array of servers wasn't created");
        return NULL;
    }
    return net;
}

void destoy_servers_arr(server *arr) {
    free(arr);
}

void print_by_groups(server* serv, int serversize, set net) {
    if (!serv) {
        return;
    }
    for (int i = 0; i < net.cur_size; ++i) {
        printf("\n=========================================\nGROUP NET: %s\n", net.host[i]);
        for (int j = 0; j < serversize; ++j) {
            int adr[ADR_NUM_SIZE];
            get_network_adress(serv[j], adr);
            char* adrstr = (char*)malloc(ADR_STR_SIZE * sizeof(char));
            if (!adrstr) {
                return;
            }
            get_address_str(adr, adrstr);
            if (!strcmp(adrstr, net.host[i])) {
                server_print(serv[j]);
            }
            free(adrstr);
            adrstr = NULL;
        }
        printf("END OF GROUP\n=========================================\n\n");
    }
}
