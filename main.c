#include <stdio.h>

#define MAX 10
#define INF 9999

int graph[MAX][MAX];
int dist[MAX];
int visited[MAX];
int parent[MAX];

char location[MAX][30];
int n;
int source;
int graphEntered = 0;
int algorithmDone = 0;


// Enter campus graph
void enterGraph()
{
    int i, j;

    printf("\nEnter number of locations: ");
    scanf("%d", &n);

    printf("\nEnter location names:\n");

    for (i = 0; i < n; i++)
    {
        printf("Location %d: ", i + 1);
        scanf(" %[^\n]", location[i]);
    }

    printf("\nEnter distance between locations.\n");
    printf("Enter -1 if there is no direct road.\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            printf("Distance between %s and %s: ",
                   location[i], location[j]);

            scanf("%d", &graph[i][j]);

            if (graph[i][j] == -1)
            {
                graph[i][j] = INF;
            }

            // Campus roads are undirected
            graph[j][i] = graph[i][j];
        }

        graph[i][i] = 0;
    }

    graphEntered = 1;
    algorithmDone = 0;

    printf("\nCampus graph entered successfully!\n");
}


// Display adjacency matrix
void displayMatrix()
{
    int i, j;

    if (!graphEntered)
    {
        printf("\nPlease enter the graph first.\n");
        return;
    }

    printf("\n========== ADJACENCY MATRIX ==========\n\n");

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }

        printf("\n");
    }
}


// Select source
void selectSource()
{
    int i;

    if (!graphEntered)
    {
        printf("\nPlease enter the graph first.\n");
        return;
    }

    printf("\nCampus Locations:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, location[i]);
    }

    printf("\nEnter source location number: ");
    scanf("%d", &source);

    source--;

    if (source < 0 || source >= n)
    {
        printf("Invalid location!\n");
        source = -1;
        return;
    }

    algorithmDone = 0;

    printf("Source selected: %s\n", location[source]);
}


// Dijkstra's Algorithm
void dijkstra()
{
    int i, j;
    int min, u;

    if (!graphEntered)
    {
        printf("\nPlease enter the graph first.\n");
        return;
    }

    if (source < 0)
    {
        printf("\nPlease select a source first.\n");
        return;
    }

    // Initialize arrays
    for (i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    // Distance from source to itself
    dist[source] = 0;

    // Main Dijkstra loop
    for (i = 0; i < n; i++)
    {
        min = INF;
        u = -1;

        // Find unvisited vertex with minimum distance
        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        // No more reachable vertices
        if (u == -1)
            break;

        visited[u] = 1;

        // Update distances of neighbours
        for (j = 0; j < n; j++)
        {
            if (visited[j] == 0 &&
                graph[u][j] != INF &&
                dist[u] + graph[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph[u][j];

                // Store previous vertex
                parent[j] = u;
            }
        }
    }

    algorithmDone = 1;

    printf("\nDijkstra's Algorithm completed successfully!\n");
}


// Display path
void displayPath(int destination)
{
    int path[MAX];
    int count = 0;
    int current = destination;
    int i;

    // Store path in reverse order
    while (current != -1)
    {
        path[count] = current;
        count++;
        current = parent[current];
    }

    // Print path in correct order
    for (i = count - 1; i >= 0; i--)
    {
        printf("%s", location[path[i]]);

        if (i != 0)
            printf(" -> ");
    }
}


// Display shortest paths
void displayShortestPaths()
{
    int i;

    if (!algorithmDone)
    {
        printf("\nPlease run Dijkstra's Algorithm first.\n");
        return;
    }

    printf("\n========== SHORTEST PATHS ==========\n");

    printf("\nSource: %s\n\n", location[source]);

    for (i = 0; i < n; i++)
    {
        printf("Destination: %s\n", location[i]);

        if (dist[i] == INF)
        {
            printf("Distance: No path\n");
            printf("Path: No path\n");
        }
        else
        {
            printf("Distance: %d\n", dist[i]);

            printf("Path: ");
            displayPath(i);
            printf("\n");
        }

        printf("\n");
    }
}


// Display distances
void displayDistances()
{
    int i;

    if (!algorithmDone)
    {
        printf("\nPlease run Dijkstra's Algorithm first.\n");
        return;
    }

    printf("\n========== DISTANCES ==========\n");

    for (i = 0; i < n; i++)
    {
        if (dist[i] == INF)
            printf("%s : No path\n", location[i]);
        else
            printf("%s : %d\n", location[i], dist[i]);
    }
}


// Main function
int main()
{
    int choice;

    source = -1;

    do
    {
        printf("\n\n====================================\n");
        printf("   CAMPUS SHORTEST ROUTE FINDER\n");
        printf("       DIJKSTRA'S ALGORITHM\n");
        printf("====================================\n");

        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                selectSource();
                break;

            case 4:
                dijkstra();
                break;

            case 5:
                displayShortestPaths();
                break;

            case 6:
                displayDistances();
                break;

            case 7:
                printf("\nProgram exited successfully.\n");
                break;

            default:
                printf("\nInvalid choice! Enter 1 to 7.\n");
        }

    } while (choice != 7);

    return 0;
}
