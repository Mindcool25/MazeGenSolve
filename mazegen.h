#include <time.h>
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Maze
{
	public:
		const int maze_size_x = 50;
    const int maze_size_y = 40;
    void genMaze();
    void printMaze();
    void solveMaze();
    bool recurseSolve(int, int);
    friend ostream& operator << (ostream &out, Maze &m);


	private:
		vector<vector<int>>maze;
		list<pair<int,int>>drillers;
    void genStart();
    void genEnd();
    int start[2];
    int end[2]; 
};

void Maze::solveMaze()
{
  if(recurseSolve(start[0], start[1]))
    cout << "Solved maze!" << endl;
  else
    cout << "Could not solve." << endl;
}

bool Maze::recurseSolve(int currR, int currC)
{
    // Base case
  if(currR == end[0] && currC == end[1]){
    cout << "Got to end" << endl;
    return true;
  }
  //if((maze[currR][currC] == 1 || maze[currR][currC] == 2) && currR < maze_size_y && currC < maze_size_x && currR > 0 && currC > 0){
  if(currR < maze_size_y && currC < maze_size_x && currR > 0 && currC > 0 )
  {
    if (maze[currR][currC] == 1 || maze[currR][currC] == 2)
    {
  //cout << "Empty spot currently" << endl;
      if(maze[currR][currC] == 1)
      {
        //cout << "Setting spot" << endl;
        maze[currR][currC] = 4;
      }
    // Below                      Above                      Right                      Left
    if(recurseSolve(currR - 1, currC) || recurseSolve(currR + 1, currC) || recurseSolve(currR, currC + 1) || recurseSolve(currR, currC - 1))
    {
      
      return true;
    }// End if
    else{
      if(maze[currR][currC] != 2)
        maze[currR][currC] = 1;
      //cout << "else" << endl;
      return false;
    }// End else
  }// End if
 }
  return false;
}

void Maze::genStart()
{
  // Setting the start of the maze
  for(int j = maze_size_y-1; j > 1; j--)
  {
    for(int i = 1; i < maze_size_x; i++)
    {
      if(maze[j][i] == 1)
      {
        maze[maze_size_y-1][i] = 2;
        start[0] = j;
        start[1] = i;
        return;
      }
    }
  
  }
}

void Maze::genEnd()
{
  // Setting the end of the maze
  for(int j = 1; j < maze_size_y - 1; j++)
  {
    for(int i = 1; i < maze_size_x; i++)
    {
      if(maze[j][i] == 1)
      {
        maze[j][i] = 3;
        end[0] = j;
        end[1] = i;
        return;
      }
    }
  }
}

void Maze::genMaze()
{ 
   srand(time(0)); 

   maze.resize(maze_size_y); 
   for (int y=0;y<maze_size_y;y++) 
           maze[y].resize(maze_size_x); 

   for (int x=0;x<maze_size_x;x++) 
           for (int y=0;y<maze_size_y;y++) 
                   maze[y][x]=false; 

   drillers.push_back(make_pair(maze_size_x/2,maze_size_y/2)); 
   while(drillers.size()>0) 
   { 
     list<pair<int, int>>::iterator m,_m,temp;
     m=drillers.begin();
     _m=drillers.end();
     while (m!=_m){
       bool remove_driller=false;
       switch(rand()%4){
       case 0:
         (*m).second-=2;
         if ((*m).second<0 || maze[(*m).second][(*m).first] == 1){
           remove_driller=true;
           break;
         }
         maze[(*m).second+1][(*m).first]=1;
         break;
       case 1:
         (*m).second+=2;
         if ((*m).second>=maze_size_y || maze[(*m).second][(*m).first] == 1){
           remove_driller=true;
           break;
         }
         maze[(*m).second-1][(*m).first]= 1;
         break;
       case 2:
         (*m).first-=2;
         if ((*m).first<0 || maze[(*m).second][(*m).first]){
           remove_driller=true;
           break;
         }
         maze[(*m).second][(*m).first+1]=true;
         break;
       case 3:
         (*m).first+=2;
         if ((*m).first>=maze_size_x || maze[(*m).second][(*m).first]){
           remove_driller=true;
           break;
         }
         maze[(*m).second][(*m).first-1]=true;
         break;
       }
       if (remove_driller)
         m = drillers.erase(m);
       else{
         drillers.push_back(make_pair((*m).first,(*m).second));
         // uncomment the line below to make the maze easier
         // if (rand()%2)
         drillers.push_back(make_pair((*m).first,(*m).second));
         maze[(*m).second][(*m).first]=true;
         m++;
       }
     }
   }

   // Done
   genStart();
   cout << start[0] << ":" << start[1] << endl;
   genEnd();
   cout << end[0] << ":E:" << end[1] << endl;
  }

ostream& operator << (ostream &out, Maze &m)
{
   for (int y=0;y<m.maze_size_y;y++){
     for (int x=0;x < m.maze_size_x;x++){
       if (m.maze[y][x]==1)
         out << " ";
       else if (m.maze[y][x] == 0)
         out << "█";
       else if (m.maze[y][x] == 2)
         out << "S";
       else if (m.maze[y][x] == 3)
         out << "E";
       else
         out << ".";
     }
    out << "\n";
   }
  return out;
}

// WHAT HAS BEEN DONE:
// Maze generation has been finished and works really well.
// Sample output:
// ##########
// #########.
// #########.
// ###.......
// #####.#.#.
// #.#...#.#.
// #.#.###.#.
// #...#...#.
// #.###.#.#.
// #...#.#.#.
//
// TODO: I need to do some final touches to the maze class, such as overload print function
// for ease of use. I also need to implament the solving algorithm afterwards. Shouldn't be too bad.
//
// NOTE: Main function is currently not doing anything other than creating the object
// and running genMaze();
