// Any copyright is dedicated to the Public Domain.
// http://creativecommons.org/publicdomain/zero/1.0/

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

/*
 * Ask to JS about an integer
 */
int __play_with_js(void);

/*
 * Passing a string through linear memory and print it
 */
void __console_log(int str, int len);
void console_log(char *str) {
	__console_log((int) str, strlen(str));
}

/*
 * Fn exported to JS
 */
__attribute__((visibility("default")))
int do_something() {
	int sum = 0;
	char *str = malloc(300);

	uint8_t* a = malloc(1400000);
	sum += a[1400000 - 1];

	sprintf(&str, "%p", a);
	console_log(str);

	uint8_t* b = malloc(999999999);
	sum += b[999999999 - 1];

	sprintf(&str, "%p", b);
	console_log(str);

	uint8_t* c = malloc(1400000);
	sum += c[1400000 - 1];

	sprintf(&str, "%p", c);
	console_log(str);

	uint8_t* d = malloc(1400000);
	sum += d[1400000 - 1];

	uint8_t* e = malloc(1400000);
	sum += e[1400000 - 1];

	// free(e);
	// free(d);
	// free(c);
	// free(b);
	// free(a);

	return sum;
}
