#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>

char random_alnum_char();
void print_usage();

int main(int argc, char* argv[])
{
	int triplet_count;

	if (argc == 1) {
		triplet_count = 4;
	}
	else if (argc == 3) {
		int count = (int)strtol(argv[2], (char **)NULL, 10);
		if (count < 1 || count > 32) {
			print_usage();
			return EXIT_FAILURE;
		}

		triplet_count = count;
	}
	else {
		print_usage();
		return EXIT_FAILURE;
	}

	size_t buf_size = 3*triplet_count + (triplet_count-1) + 1;
	char *password = malloc(buf_size);
	if (!password) {
		return EXIT_FAILURE;
	}

	int dash_countdown = 3;
	for (size_t i = 0; i < (buf_size-1); i++) {
		if (!dash_countdown) {
			password[i] = '-';
			dash_countdown = 3;
		}
		else {
			password[i] = random_alnum_char();
			dash_countdown--;
		}
	}
	password[buf_size-1] = '\0';

	printf("%s\n", password);
	free(password);

	return EXIT_SUCCESS;
}

char random_alnum_char()
{
	const char from = '0';
	const char to   = 'z';
	uint32_t delta  = (uint32_t)to - (uint32_t)from;
	char ch = (char)(arc4random() % delta + (uint32_t)from);

	return isalnum(ch)? ch : random_alnum_char();
}

void print_usage()
{
	fprintf(stderr, "usage: ./passgen [-n count_of_triplets]\n");
}
