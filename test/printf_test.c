/*
 * printf_test.c
 *
 *  Created on: 2018-2-20
 *      Author: virusv
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "smart_ocd.h"
#include "target/JTAG.h"

#define GET_Nth_BIT(pos,n) ((*(CAST(uint8_t *, (pos)) + (((n)-1)>>3)) >> (((n)-1) & 0x7)) & 0x1)

int get_last_bit(uint8_t *data, int n){
	uint8_t x = data[n >> 3];
	uint8_t y = n & 0x7;
	return (x >> (y)) & 0x1;
}

char* itoa(int num, char *str, int radix) {
	/*索引表*/
	char index[] = "0123456789ABCDEF";
	unsigned unum;/*中间变量*/
	int i = 0, j, k;
	/*确定unum的值*/
	if (radix == 10 && num < 0)/*十进制负数*/
	{
		unum = (unsigned) -num;
		str[i++] = '-';
	} else
		unum = (unsigned) num;/*其他情况*/
	/*转换*/
	do {
		str[i++] = index[unum % (unsigned) radix];
		unum /= radix;
	} while (unum);
	str[i] = '\0';
	/*逆序*/
	if (str[0] == '-')
		k = 1;/*十进制负数*/
	else k = 0;
	char temp;
	for (j = k; j <= (i - 1) / 2; j++) {
		temp = str[j];
		str[j] = str[i - 1 + k - j];
		str[i - 1 + k - j] = temp;
	}
	return str;
}

int main(){
	uint8_t tms_seq[6] = {0xab,0xcd,0xef,0xad,0xec,0xdd};
	char str[64];
	//printf("%s\n", itoa(tms_seq, str, 2));
	for(int n=1; n<=48; n++){
		printf("%d", GET_Nth_BIT(&tms_seq, n));
		if(n % 4 == 0)printf(" ");
	}
	printf("\n");
	return 0;
}
