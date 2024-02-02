#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 25

int matrix[MAX_SIZE][MAX_SIZE], visited_cities[MAX_SIZE], limit, cost = 0;

int tsp(int c)
{
    int count, nearest_city = -1;
    int minimum = 999, temp;
    
    for (count = 0; count < limit; count++)
    {
        if ((matrix[c][count] != 0) && (visited_cities[count] == 0))
        {
            if (matrix[c][count] < minimum)
            {
                minimum = matrix[c][count];
                nearest_city = count;
            }
        }
    }
    
    if (nearest_city != -1)
    {
        cost += minimum;
        visited_cities[nearest_city] = 1; 
    }
    
    return nearest_city;
}

void minimum_cost(int city)
{
    int nearest_city;
    
    printf("%d ", city + 1);
    
    nearest_city = tsp(city);
    
    if (nearest_city == -1)
    {
        printf("1");
        return;
    }
    
    minimum_cost(nearest_city);
}

void readMatrixFromCSV(const char* filename)
{
	FILE* file = fopen(filename, "r");
	
	if (file == NULL) 
	{
		printf("Error opening file.\n");
		exit(1);
	}
	
	char line[MAX_SIZE * 4]; 
	
	int row = 0;
	
	while (fgets(line, sizeof(line), file) != NULL && row < MAX_SIZE)
	{
		char* token;
		int col = 0;
		
		token = strtok(line, ",");
		
		while (token != NULL && col < MAX_SIZE)
		{
			matrix[row][col] = atoi(token);
			col++;
			
			token = strtok(NULL, ",");
		}
		
		row++;
	}
	
	fclose(file);
}

int main()
{
    int i, j;
    
    printf("Enter Total Number of Cities:\t");
    scanf("%d", &limit);
    
    char filename[100];
    printf("Enter the CSV file name: ");
    scanf("%s", filename);
    
    readMatrixFromCSV(filename);
    
    printf("\nEntered Cost Matrix\n");
    
    for (i = 0; i < limit; i++)
    {
        printf("\n");
        
        for (j = 0; j < limit; j++)
        {
            printf("%d ", matrix[i][j]);
        }
    }
    
    printf("\n\nPath:\t");
    
    visited_cities[0] = 1; // Mark the starting city as visited
    minimum_cost(0);
    
    printf("\n\nMinimum Cost: \t");
    printf("%d\n", cost + matrix[limit - 1][0]); // Add the cost of returning to the starting city
    
    return 0;
}