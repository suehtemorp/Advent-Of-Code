#include <stdio.h>
#define MAX_LINE_WIDTH 2024

int main() {
    FILE* input = fopen("input.txt", "r");
    if (input == NULL) {
        perror("Unable to open input");
        return -1;
    }

    size_t safeReports = 0;

    while (feof(input) == 0) {
        char reportLine[MAX_LINE_WIDTH];

        if (fgets(reportLine, sizeof reportLine, input) != reportLine) { // Scan for line
            printf("Unable to read report line\n");

            if (feof(input)) {
                printf("Due to EOF reached (blank line?)\n");
                break;
            } else if (ferror(input)) {
                perror("Due to file error");
            } else {
                printf("Due to some unknown error\n");
            }

            fclose(input);
            return -1;
        }

        // Keep track of adyacent levels and their monotonicity
        enum { UNKNOWN, INCREASING, DECREASING } monotonicity = UNKNOWN;
        size_t scannedLevels[2];

        // Keep track of the position and state for the string scanning
        size_t scanWidth = 0;
        int scanState = 1;

        for (size_t scanPosition = 0; scanState == 1; scanPosition += scanWidth) { // Scan for levels
            scanState = sscanf((const char *) (&reportLine[0] + scanPosition), "%zu%n", &scannedLevels, &scanWidth);

            if (scanState == 1) { // Succesful level scan

                if (scanPosition > 0) { // Beyond initial scan
                    if (monotonicity == UNKNOWN) { // Monotonicity yet unknown, check
                        if (scannedLevels[0] == scannedLevels[1]) { break; } // Unsafe level
                        monotonicity = scannedLevels[0] > scannedLevels[1] ? INCREASING : DECREASING;
                    }

                    if ( // Assert mantained monotonicity
                        scannedLevels[0] == scannedLevels[1]
                        || (monotonicity == INCREASING && (scannedLevels[0] < scannedLevels[1]))
                        || (monotonicity == DECREASING && (scannedLevels[0] > scannedLevels[1]))
                    ) { break; }

                    size_t diff = monotonicity == INCREASING ? 
                        scannedLevels[0] - scannedLevels[1] : scannedLevels[1] - scannedLevels[0];

                    if (diff < 1 || diff > 3) { break; }
                }

                scannedLevels[1] = scannedLevels[0]; // Shift level queue

            } else { // Unsuccesfull scan
                if (scanState == EOF) { // Due to EOF, report is done
                    safeReports += 1;
                } else { // Due to some unknown error
                    perror("Unable to read level");
                    fclose(input);
                    return -1;
                }
            }
        }
    }

    fclose(input);

    printf("Safe reports: %zu\n", safeReports);
    return 0;
}