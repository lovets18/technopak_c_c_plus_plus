/* 
Вариант #26
Создать структуру для хранения информации о сервере: его DNS-имени, IP-адресе, 
сетевой маске, количестве процессоров и количестве ядер. Составить с ее использованием 
программу вывода информации обо всех серверах с группировкой по подсетям.
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "server.h"


int main()
{
    int n;
    printf("Enter the number of servers: ");
    scanf("%d", &n);
    server* network = create_servers_arr(n);
    for (int i = 0; i < n; ++i) {
        int success = 1;
        int* successptr = &success;
        do {
            success = 1;
            char name[16], ip[16], mask[16];
            int processor, core;
            printf("Enter dns-name: ");
            if (!scanf("%16s", name)) {
                printf("Name wasn't readen!\n");
                return -1;
            };
            printf("Enter ip: ");
            if (!scanf("%16s", ip)) {
                printf("Ip wasn't readen!\n");
                return -1;
            };
            printf("Enter mask: ");
            if (!scanf("%16s", mask)) {
                printf("Mask wasn't readen!\n");
                return -1;
            };
            printf("Enter processor number: ");
            if (!scanf("%d", &processor)) {
                printf("Processor wasn't readen!\n");
                return -1;
            };
            printf("Enter core number: ");
            if (!scanf("%d", &core)) {
                printf("Core wasn't readen!\n");
                return -1;
            };
            network[i] = server_init(name, ip, mask, processor, core, successptr);
        } while (!success);
    }
    
    set groups = unique_nets_to_set(network, n);
    print_by_groups(network, n, groups);

    set_destroy(&groups);
    destoy_servers_arr(network);

    return 0;
}
