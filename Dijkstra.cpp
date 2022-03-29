#include<stdio.h>
#include<vector>
#include<math.h>

using namespace std ;
struct Cell
{
    int x,y, cost ;
    double heuristic, total;
}tempU,tempV;

struct myqueue
{
    int cell_x,cell_y;
    double key ;
    bool flag ;
}Q[100][100];


vector<Cell> g[100][100] ;
int row,col;
int dis[100][100];
double heu[100][100],tot[100][100];
myqueue par[100][100] ;

myqueue pop()
{
    double min = 1000000.0 ;
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

void AStar(){
    while(!isEmpty()){
        myqueue u = pop();
        for(int i = 0 ; i < g[u.cell_x][u.cell_y].size() ; i++){
            Cell t = g[u.cell_x][u.cell_y][i];
            myqueue v = Q[t.x][t.y];
            int w = t.cost;

            if(dis[v.cell_x][v.cell_y] > dis[u.cell_x][u.cell_y] + w){
                dis[v.cell_x][v.cell_y] = dis[u.cell_x][u.cell_y] + w;
                tot[v.cell_x][v.cell_y] = dis[v.cell_x][v.cell_y] + heu[v.cell_x][v.cell_y];
                par[v.cell_x][v.cell_y] = u;
                Q[v.cell_x][v.cell_y].key = tot[v.cell_x][v.cell_y];
            }
        }
    }
}

void printPath(int start_x,int start_y,myqueue q)
{
    int curr_x = q.cell_x;
    int curr_y = q.cell_y;
    printf("%d,%d   ", curr_x,curr_y) ;
    if(curr_x == start_x && curr_y == start_y){
        return;
    }
    printPath(start_x,start_y,par[curr_x][curr_y]);

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
            if(i-1>=0  && cost_matrix[i-1][j] >= 0){
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
            if(i+1<row && cost_matrix[i+1][j] >= 0){
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
            if(j-1>=0 && cost_matrix[i][j-1] >= 0){
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
            if(j+1<col && cost_matrix[i][j+1] >= 0 ){
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
            if(cost_matrix[i][j] != -1){
                dis[i][j] = 99999 ;
            }else{
                dis[i][j] = -1;
            }

            //par[i][j] = NULL ;
        }
    }


    int startX,startY;
    printf("Enter starting location startX,startY  : ");
    scanf("%d %d", &startX, &startY);
    dis[startX][startY] = 0 ;

    int endX,endY;
    printf("Enter ending location endX,endY  : ");
    scanf("%d %d", &endX, &endY);

    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            if(cost_matrix[i][j] != -1){
                Q[i][j].cell_x = i;
                Q[i][j].cell_y = j;
                Q[i][j].key = dis[i][j];
                Q[i][j].flag = true;
            }
        }
    }


    Dijkstra() ;
    printf("\nAll minimum cost G(x,y)\n");
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            printf("%d      ", dis[i][j]) ;
        }
        printf("\n");
    }
    printPath(startX,startY,Q[endX][endY]);


    //Calculating all heuristic costs
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            if(cost_matrix[i][j] != -1){
                heu[i][j] = sqrt( pow(1.00*(endX-i),2) + pow(1.00*(endY-j),2) );
            }else{
                heu[i][j] = -1.0;
            }
        }
    }

    //printing all heuristic costs
    printf("\nAll heuristic H(x,y)\n") ;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            printf("%0.3f      ", heu[i][j]) ;
        }
        printf("\n");
    }


    //finding total cost F(x,y)
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            tot[i][j] = dis[i][j] + heu[i][j];
        }
    }
    printf("\nAll total F(x,y)\n") ;
    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            printf("%0.3f      ", tot[i][j]) ;
        }
        printf("\n");
    }


    for(int i = 0 ; i < row ; i++){
        for(int j = 0 ; j < col ; j++){
            if(cost_matrix[i][j] != -1){
                Q[i][j].key = tot[i][j];
                Q[i][j].flag = true;
            }
        }
    }

    AStar() ;

    printPath(startX,startY,Q[endX][endY]);

    return 0 ;
}
