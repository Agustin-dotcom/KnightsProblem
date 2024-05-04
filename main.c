/******************************************************************************

                    A knight must perform nxn jumps on a nxn chessboard.
                    Solve it by means of Backtracking.

*******************************************************************************/

/* j means the jump we have taken. j ranges from 0 to 9 where 9 triggers bakctracking and 0 means we haven't decided yet


    8       1
7                2
        k
6                3
    5        4



*/



#include <stdio.h>
#include <stdbool.h>

/******************************************************************************************************
 * This function performs a jump
 *
 * @param *currentLocation: an integer indicating the position we are at (bear in mind that we have passed from a matrix to an array)
 * @param :
 * @param :
 ******************************************************************************************************/
void jump(int typeOfJump,int *currentLocation){
    switch(typeOfJump){
        case 1:
                currentLocation[0] = currentLocation[0] - 2; //-2rows+column
                currentLocation[1] = currentLocation[1] + 1;
            break;
        case 2:
                currentLocation[0] = currentLocation[0] - 1; //-row+2columns
            currentLocation[1] = currentLocation[1] + 2;
            break;
        case 3:
                currentLocation[0] = currentLocation[0] + 1; //+row+2columns
                currentLocation[1] = currentLocation[1] + 2;
            break;
        case 4:
                currentLocation[0] = currentLocation[0] + 2; //+2rows+column
                currentLocation[1] = currentLocation[1] + 1;
            break;
        case 5:
                currentLocation[0] = currentLocation[0] + 2; //+2rows-column
                currentLocation[1] = currentLocation[1] - 1;
            break;
        case 6:
                currentLocation[0] = currentLocation[0] + 1; //+row-2columns
                currentLocation[1] = currentLocation[1] -2;
            break;
        case 7:
                currentLocation[0] = currentLocation[0] -1; //-row-2columns
                currentLocation[1] = currentLocation[1] -2;
            break;
        case 8:
                currentLocation[0] = currentLocation[0] - 2; //-2rows-column
                currentLocation[1] = currentLocation[1] -1;
            break;
    }
}
/******************************************************************************************************
 * This function unjumps when Backtracking is triggered (j == 9)
 *
 * @param
 *
 * Notes: in order to unjump we must update our bool array and the indices and also the moves(solution array)
 ******************************************************************************************************/
void unjump(int typeOfJump,int *currentLocation){
    switch(typeOfJump){
        case 1:
            currentLocation[0] = currentLocation[0]+ 2 ; //+2rows-column
            currentLocation[1] = currentLocation[1] -1;
            break;
        case 2:
            currentLocation[0] = currentLocation[0] + 1; //+row-2columns
            currentLocation[1] = currentLocation[1] -2;
            break;
        case 3:
            currentLocation[0] = currentLocation[0] - 1; //-row-2columns
            currentLocation[1] = currentLocation[1] -2;
            break;
        case 4:
            currentLocation[0] = currentLocation[0] - 2; //-2rows-column
            currentLocation[1] = currentLocation[1] -1;
            break;
        case 5:
            currentLocation[0] = currentLocation[0] - 2; //-2rows+column
            currentLocation[1] = currentLocation[1] +1;
            break;
        case 6:
            currentLocation[0] = currentLocation[0] - 1; //-row+2columns
            currentLocation[1] = currentLocation[1] + 2;
            break;
        case 7:
            currentLocation[0] = currentLocation[0] + 1; //+row+2columns
            currentLocation[1] = currentLocation[1] + 2;
            break;
        case 8:
            currentLocation[0] = currentLocation[0] + 2 ; //+2rows+column
            currentLocation[1] = currentLocation[1]+1;
            break;
    }
}
/******************************************************************************************************
 * This function increases in one the position of the array we are at so that we can try with all possible starting points
 *
 * @param
 *
 * Notes: We must take into account that we have a frame to avoid jumping out of the matrix. This takes a huge importance
 * when we want to point to the next position. Let's solve it in this function
 ******************************************************************************************************/
void increaseInOneLocation(int * currentLocation,int n){
    if(currentLocation[1] + 1 == n+4-2){
        currentLocation[1] = 2;
        if(currentLocation[0] + 1 == n+4-2)
            return;//we are not interested in this case
        else
            currentLocation[0] = currentLocation[0] + 1;
    }else
        currentLocation[1] = currentLocation[1] + 1;

}
void printSOfI(int *S,int n){
    printf("(");
    for (int i = 0; i < n * n; ++i) {
        printf("%d,",S[i]);
    }
    printf(")\n");
}
void printWeHaveAlreadyBeen(int n,bool matrix[n+4][n+4]){
    for (int i = 0; i <n+4; ++i) {
        for (int j = 0; j < n + 4; ++j) {
            if(matrix[i][j]){
                printf("T ");
            }else{
                printf("F ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int n = 3;
    int i = 0;
    //int temp;
    //int paintItAsDeadNode;
    //printf("Introduce n:");
    //scanf("%d",&n);
    /********************************* Just intialization *********************************************/
    int S[n*n]; //solution array
    for (int i = 0; i < n * n; ++i) {
        S[i] = 0;
    }
    int currentLocation[2] = {2,2};

    bool weAlreadyWentThroughThisCell[n+4][n+4];
    for (int i = 0; i < n +4; ++i) {
        for (int j = 0; j < n + 4; ++j) {
            weAlreadyWentThroughThisCell[i][j] = false;
        }
    }
    for (int i = 0; i < n + 4; ++i) {
        weAlreadyWentThroughThisCell[0][i]=true;
        weAlreadyWentThroughThisCell[1][i]=true;
        weAlreadyWentThroughThisCell[n+4-1][i]=true;
        weAlreadyWentThroughThisCell[n+4-2][i]=true;
        weAlreadyWentThroughThisCell[i][0]=true;
        weAlreadyWentThroughThisCell[i][1]=true;
        weAlreadyWentThroughThisCell[i][n+4-1]=true;
        weAlreadyWentThroughThisCell[i][n+4-2]=true;
    }
    weAlreadyWentThroughThisCell[currentLocation[0]][currentLocation[1]] = true;
    while(i<n*n){ // O(9^(n^2)) since we can choose from 0 to 9 and then we can make this selection n^2 times
            S[i]++;
            printSOfI(S,n);
            jump(S[i],currentLocation);
            if(weAlreadyWentThroughThisCell[currentLocation[0]][currentLocation[1]])
                unjump(S[i],currentLocation);
            else{
                weAlreadyWentThroughThisCell[currentLocation[0]][currentLocation[1]] = true;
                i++;
            }
            printf("(%d,%d)\n",currentLocation[0],currentLocation[1]);
            printWeHaveAlreadyBeen(n,weAlreadyWentThroughThisCell);
            if(S[i] == 9){
                //none of the previous jumps are valid
                if(i==0 && currentLocation[0] == n+4-3 && currentLocation[1] == n+4-3){
                    printf("We could not find any solution with nxn jumps... We are very sorry.");
                    return 0;
                }else if(i==0){

                    weAlreadyWentThroughThisCell[currentLocation[0]][currentLocation[1]] = false;
                    increaseInOneLocation(currentLocation,n); //O(1)
                    weAlreadyWentThroughThisCell[currentLocation[0]][currentLocation[1]] = true;
                    i=0;
                    S[i] = 0;
                }else{
                    weAlreadyWentThroughThisCell[currentLocation[0]][currentLocation[1]] = false;
                    unjump(S[i-1],currentLocation);
                    S[i] = 0;
                    i--;
                }
            }
    }

    //weAlreadyWentThroughThisCell[0]=true;//we start on 1st row 1st column
    /********************************* Just intialization *********************************************/
//    for(int i=0;i<n*n;i++){//we need nxn jumps
//        for (int j = 1; j < 10 ; j++) {
//            if(j == paintItAsDeadNode)
//                continue;
//            if(j==9){ //B.T.
//                weAlreadyWentThroughThisCell[currentLocation] = false;
//                unjump(S[i],&currentLocation,n);
//                paintItAsDeadNode = S[i];
//                S[i] = 0;
//                i-2;
//                break;
//            }else{ // Live Node
//                temp = currentLocation;
//                jump(j,&currentLocation,n);
//                if(currentLocation>=0 && currentLocation < n*n &&
//                   row(currentLocation,n) != row(temp,n) &&
//                   column(currentLocation,n) != column(temp,n) && !weAlreadyWentThroughThisCell[currentLocation]){
//                    weAlreadyWentThroughThisCell[currentLocation] = true;
//                    S[i] = j;
//                    break;
//                }else{ // Dead node
//                    if(temp!=currentLocation)
//                        unjump(j,&currentLocation,n);
//                }
//            }
//        }
//    }

    printSOfI(S,n);
    return 0;
}