#include "Table.h"

/*
test data:
(7,12)
{1 2 3 4 5 6 7}
(1,2,2) 
(1,4,1) 
(2,4,3) 
(2,5,10)
(3,1,4)  
(3,6,5)  
(4,3,2)
(4,5,2)
(4,6,8)
(4,7,4)
(5,7,6)
(7,6,1)
actually result
1
1-->2
1-->4-->3
1-->4
1-->4-->5
1-->4-->7-->6
1-->4-->7
*/
int main(int argc, char **argv)
{
    Table T;
    Table_Init(1,T);
    Dijkstra(T);
    Print_Table(T,1);
    printf("\n");
    Print_Table(T,2);
    printf("\n");
    Print_Table(T,3);
    printf("\n");
    Print_Table(T,4);
    printf("\n");
    Print_Table(T,5);
    printf("\n");
    Print_Table(T,6);
    printf("\n");
    Print_Table(T,7);
    printf("\n");
    return 0;
}