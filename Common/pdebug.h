#include <stdio.h>
#include <stdint.h>

void print_chars_as_hex(const char *str) {
    while (*str) {
        printf("%02X ", (unsigned char)*str);
        str++;
    }
}

void print_array_as_hex(const char *str, uint32_t len)
{
	for(int i = 0; i < len; ++i) {
		printf("%x ", str[i]);
	}
}

void print_uint32_as_hex(uint32_t num) {
    char hex_str[9];
    snprintf(hex_str, sizeof(hex_str), "%08X", num);
    printf("%s", hex_str);
}

void print_uint16_as_hex(uint16_t num) {
    char hex_str[5];
    snprintf(hex_str, sizeof(hex_str), "%04X", num);
    printf("%s", hex_str);
}

void print_newline()
{
	printf("\r\n");
}
