/*
   Implementation of Langton's ant In C.
   https://en.wikipedia.org/wiki/Langton%27s_ant
   This program takes the size of square grid,orientation and steps.
   The output is saved as PBM image
 */
/* Here white area in grid is represented by 0 and black by 1 */
/* Project by Dinabandhu Khatiwada */
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int i,j,steps=0,moves;                  // initializing necessary values
    int up=0,down=1,right=2,left=3;
    int temp,orientation;
    int dir = 0;
    int co;
    FILE *photo;
    int width;
    printf("Enter size in pixels\n");
    scanf("%d",&width);
    printf("Enter number of steps and orientation(up=0,down=1,right=2,left=3)\n");
    scanf("%d%d",&moves,&orientation);       // white grid is the oputut if orientation is out of range
    int a[width][width],x=width/2,y=width/2; // The ant starts from middle of the grid
    dir = orientation;                       // setting user given orientation of ant
    for(i=0;i<width;i++)
    {   
        for(j=0;j<width;j++)
        {   
            a[i][j] = 0;   // setting the entire grid to white 
        }
    }
    printf("\n");
    while(x<width && y<width && steps<moves) // while ant is within bounds of grid
    {      
        if(a[x][y] == 0)                     // 0 = white so move clockwise
        {
            a[x][y] = 1 ;                    // flips colour to black
            co = dir ;                       // gets the orientation of the ant
            switch(co)
            {
                case 0:  //ant is oriented upwards
                    ++x ;
                    dir = 2;    //move right
                    break;    
                case 1:  //ant is oriented down
                    --x;
                    dir = 3;    //move left
                    break ;
                case 2: //ant is oriented right
                    ++y ;   
                    dir = 1;    //move down
                    break; 
                case 3: //ant is oriented left
                    --y;        //move up
                    dir = 0; 
                default:
                    printf("");
            }
        }
        else if(a[x][y] == 1) // 1 = black so move anti-clockwise
        {
            a[x][y] = 0 ; //flips the colour to white
            co = dir ;  // gets the direction
            switch(co)
            {
                case 0 : //ant is oriented up
                    --x;     //move left  
                    dir = 3; // point ant leftwards 
                    break;
                case 1: //ant is oriented down
                    ++x;     //move right
                    dir = 2;  
                    break;
                case 2: //ant is oriented right
                    --y;      //move up
                    dir = 0;  
                    break;          
                case 3: //ant is oriented left
                    ++y;      //move down
                    dir = 1;
                default:        
                    printf("");
            }
        }
        steps ++;
    } 
    printf("\n %d steps taken\n",steps);
    printf("Writing to file\n");            // PBM = Portable Bit Map
    photo = fopen("output.pbm","w");        // opening file and writing in ASCII format
    fprintf(photo,"P1\n");                  // P1 is the magic number for PBM file in ASCII
    fprintf(photo,"%d %d\n",width,width);   // width, height is necessary for PBM image
    for(i=0;i<width;i++)
    {
        for(j=0;j<width;j++)
        { 
            temp = a[i][j];
            fprintf(photo,"%d",temp);     // writing to PBM image from the array
        }
        fprintf(photo,"\n");
    }
    fprintf(photo,"\n");
    fclose(photo);
    printf("\n");
    return 0;
}

