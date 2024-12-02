#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main() {
    FILE *file = fopen("list2.txt", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int rows = 1000;
    int **matrix = malloc(rows * sizeof(int*));
    if (matrix == NULL) {
        perror("Memory allocation failed");
        return 1;
    }

    int row = 0;
    char line[1024];


    while (fgets(line, sizeof(line), file) != NULL && row < rows) {
      int col = 0;
      // decreasing malloc from 50 to 8 solves the puzzle
      int *row_data = malloc(8 * sizeof(int));
      if (row_data == NULL) {
          perror("Memory allocation failed");
          return 1;
      }

      char *token = strtok(line, " \t\n");
      while (token != NULL) {
          row_data[col++] = atoi(token);
          token = strtok(NULL, " \t\n");
      }

      row_data = realloc(row_data, col * sizeof(int));
      matrix[row] = row_data;
      row++;
    }

    fclose(file);

    int safeTotal = 0;
    for (int report = 0; report < row; report++) {
      bool isIncreasing = false;
      bool safe = true;

      for (int level = 1; matrix[report][level] != 0; level++) {
        int levelBefore = matrix[report][level - 1];
        int levelCurrent = matrix[report][level];
        int difference = abs(levelBefore - levelCurrent);

        if (difference < 1 || difference > 3) {
          safe = false;
          break;
        }

        if (level == 1) {
          if (levelBefore - levelCurrent < 0) {
            isIncreasing = true;
          }
        } else {
          bool currIncreasing = levelBefore - levelCurrent < 0;

          if (isIncreasing != currIncreasing) {
            safe = false;
            break;
          }
        }
      }

      if (safe) {
        safeTotal++;
      }
    }
    printf("%d\n", safeTotal);

    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
