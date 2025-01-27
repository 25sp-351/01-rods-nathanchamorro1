#include <stdio.h>
#include <stdlib.h>

// Calculates the best value of a rod with a given length
int calculate_best_value(int rod_length, int rod_pieces[], int rod_values[], 
                        int num_pieces, int used_pieces[]) {
    if (rod_length == 0) {
        return 0; // Base case for recurrsion. No more cuts needed.
    }

    int max_value = 0;
    int current_cut[num_pieces]; // Tracks cuts


    for (int i = 0; i < num_pieces; i++) {
        if (rod_pieces[i] <= rod_length) {
            // Moved used pieces to current cut
            for (int j = 0; j < num_pieces; j++) {
                current_cut[j] = used_pieces[j];
            }

            // Move to next cut
            current_cut[i]++;

            // Calculate value
            int value = calculate_best_value(
                rod_length - rod_pieces[i], 
                rod_pieces, 
                rod_values, 
                num_pieces, 
                current_cut
            ) + rod_values[i];

            // Identify best value
            if (value > max_value) {
                max_value = value;
                for (int j = 0; j < num_pieces; j++) {
                    used_pieces[j] = current_cut[j];
                }
            }
        }
    }

    return max_value;
}

int main(int argc, char *argv[]) {
    // Parse to find the rod length
    int rod_length = atoi(argv[1]);

    // Read from input
    int rod_pieces[100], rod_values[100];
    int num_pieces = 0;

    while (scanf("%d, %d", &rod_pieces[num_pieces], &rod_values[num_pieces]) == 2) {
        num_pieces++;
    }

    // Track used pieces
    int used_pieces[100] = {0};

    // Calculate value
    int length_used = 0;
    int max_value = calculate_best_value(rod_length, rod_pieces, rod_values, 
                                        num_pieces, used_pieces);

    // Cutting list output
    for (int i = 0; i < num_pieces; i++) {
        if (used_pieces[i] > 0) {
            printf("%d @ %d = %d\n", 
                   used_pieces[i], 
                   rod_pieces[i], 
                   used_pieces[i] * rod_values[i]);
            length_used += used_pieces[i] * rod_pieces[i];
        }
    }

    // Calculate remainder, output remainder and value
    int remainder = rod_length - length_used;
    printf("Remainder: %d\n", remainder);
    printf("Value: %d\n", max_value);

    return 0;
}
