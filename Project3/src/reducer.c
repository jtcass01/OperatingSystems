
#include "headers/reducer.h"

int main(int argc, char *argv[]) {
	char *outputFile;

	if (argc != 2) {
		printf("Usage: ./reducer [outputFile]\n");

		return 1;
	} else {
		outputFile = *(argv + 1);
	}

	printf("\treducer started.  outputFile: %s\n", outputFile);

	return 0;
}
