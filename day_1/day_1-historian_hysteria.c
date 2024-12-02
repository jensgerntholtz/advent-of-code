// https://adventofcode.com/2024/day/1
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1001

int col1[MAX_SIZE];
int col2[MAX_SIZE];

int getSmallerInt(const void *a, const void *b)
{
  return (*(int *)a - *(int *)b);
}

int main()
{
  /* --------- Start Of File Stuff ------------------ */
  FILE *file = fopen("list.txt", "r");
  if (file == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }

  int index = 0;
  while (fscanf(file, "%d %d", &col1[index], &col2[index]) == 2)
  {
    index++;
    if (index >= MAX_SIZE)
    {
      printf("Reached maximum array size.\n");
      break;
    }
  }

  fclose(file);

  /* --------- End Of File Stuff ------------------ */
  
  int totalDistance = 0;
  int col1Size = sizeof(col1) / sizeof(col1[0]);
  int col2Size = sizeof(col2) / sizeof(col2[0]);

  qsort(col1, col1Size, sizeof(int), getSmallerInt);
  qsort(col2, col2Size, sizeof(int), getSmallerInt);

  for (int index = 0; index < col1Size; index++)
  {
    int distance = abs(col1[index] - col2[index]);

    totalDistance = totalDistance + distance;
  }

  printf("%d\n", totalDistance); // 🎅

  return 0;
}