#include<stdio.h>
#include<vector>

using namespace std ;
struct Cell
{
    int x,y, cost ;
}tempU,tempV;

struct myqueue
{
    int cell_x,cell_y, key ;
    bool flag ;
}Q[100][100];


vector<Cell> g[100][100] ;
int row,col;
int dis[100][100];
myqueue par[100][100] ;

myqueue pop()
{
    int min = 1000000 ;
    int x_index ;
    int y_index ;

    for(int i = 0 ; i < row ; i++)
    {
        for(int j = 0 ; j < col ; j++){
            if(Q[i][j].key < min && Q[i][j].flag == true){
                min = Q[i][j].key ;
                x_index = i ;
                y_index = j;
            }
        }

    }
    Q[x_index][y_index].flag = false ;
    return Q[x_index][y_index];
}

bool isEmpty(){
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            if(Q[i][j].flag == true)
                return false ;
        }
    }
    return true ;
}

void Dijkstra(){
    while(!isEmpty()){
        myqueue u = pop();
        for(int i = 0 ; i < g[u.cell_x][u.cell_y].size() ; i++){
            Cell t = g[u.cell_x][u.cell_y][i];
            myqueue v = Q[t.x][t.y];
            int w = t.cost;

            if(dis[v.cell_x][v.cell_y] > dis[u.cell_x][u.cell_y] + w){
                dis[v.cell_x][v.cell_y] = dis[u.cell_x][u.cell_y] + w;
                par[v.cell_x][v.cell_y] = u;
                Q[v.cell_x][v.cell_y].key = dis[v.cell_x][v.cell_y];
            }
        }
    }
}


int main()
{
    int cost_matrix[6][6] = {
                {10, 4, -1, 5, 5, 6},
                {1, 20, -1, 6, 6, 6},
                {7, 18, -1, 12, 12, 7},
                {28, 7, -1, 8, 10, 27},
                {30, 5, 5, 7, 7, 10},
                {25, 25, -1, 8, 8, 8}

        };

    printf("enter number of row,column : ");
    scanf("%d %d", &row, &col) ;
    for(int i = 0 ; i < row ; i++)
    {
        for(int j = 0 ; j < row ; j++)
        {

            //add up neighbor
            if(i-1>=0  && cost_matrix[i-1][j] != -1){
                tempV.x = i-1;
                tempV.y = j;
                tempV.cost = cost_matrix[i-1][j];
                g[i][j].push_back(tempV);

                tempU.x = i;
                tempU.y = j;
                tempU.cost = cost_matrix[i][j];
                g[i-1][j].push_back(tempU);
            }

            //add down neighbor
            if(i+1<row && cost_matrix[i+1][j] !=- 1){
                tempV.x = i+1;
                tempV.y = j;
                tempV.cost = cost_matrix[i+1][j];
                g[i][j].push_back(tempV);

                tempU.x = i;
                tempU.y = j;
                tempU.cost = cost_matrix[i][j];
                g[i+1][j].push_back(tempU);
            }
            //add left neighbor
            if(j-1>=0 && cost_matrix[i][j-1] != -1){
                tempV.x = i;
                tempV.y = j-1;
                tempV.cost = cost_matrix[i][j-1];
                g[i][j].push_back(tempV);

                tempU.x = i;
                tempU.y = j;
                tempU.cost = cost_matrix[i][j];
                g[i][j-1].push_back(tempU);
            }
            //add right neighbor
            if(j+1<col && cost_matrix[i][j+1] != -1 ){
                tempV.x = i;
                tempV.y = j+1;
                tempV.cost = cost_matrix[i][j+1];
                g[i][j].push_back(tempV);

                tempU.x = i;
                tempU.y = j;
                tempU.cost = cost_matrix[i][j];
                g[i][j+1].push_back(tempU);
            }
        }
    }

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            dis[i][j] = 99999 ;
            //par[i][j] = NULL ;
        }
    }


    int startX,stratY;
    printf("Enter starting location startX,startY  : ");
    scanf("%d %d", &startX, &stratY);
    dis[startX][stratY] = 0 ;

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            Q[i][j].cell_x = i;
            Q[i][j].cell_y = j;
            Q[i][j].key = dis[i][j];
            Q[i][j].flag = true;
        }
    }


    Dijkstra() ;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            printf("%d      ", dis[i][j]) ;
        }
        printf("\n");
    }

    return 0 ;
}
