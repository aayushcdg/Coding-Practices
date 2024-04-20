#include<iostream>
#include<cstring>
#include<cstdio>

typedef unsigned int ui;
typedef unsigned long ul;

class MazeSolver
{
private:            // PRIVATE member data
  char maze[1226];
  char path[71];
  ui columnWidth;

public:            // PUBLIC member functions
    MazeSolver (const char *);    // parameter constructor
  ui findTreasure ();
  const char *findPath ();
  ui countBlanks ();
  void showMaze ();
  friend void operator<< (MazeSolver &, char);
};

using namespace std;

MazeSolver::MazeSolver (const char *s)
{
  ul columnWidth = strcspn (s, "\n");
  strcpy (maze, s);
  path[0] = '\0';
}

ui
MazeSolver::findTreasure ()
{
  for (int i = 0; maze[i] != '\0'; i++)
    {
      if (maze[i] == '#')
    return i;
    }
  return -1;
}

const char *
MazeSolver::findPath ()
{
  ul length = strlen (maze);
  int index = findTreasure ();
  int end = 0;
  while (maze[end] != '\0')
    end++;

  while (index != 0)
    {
      if (maze[index - 1] == ' ')
    {
      path[strlen (path)] = 'E';
      index--;
    }
      else if (maze[index - columnWidth] == ' ')
    {
      path[strlen (path)] = 'S';
      index -= columnWidth;
    }
    }
  ul len = strlen (path);
  for (int i = 0; i < len / 2; i++)
    {
      char temp = path[i];
      path[i] = path[len - i - 1];
      path[len - i - 1] = temp;
    }
  return path;
}

ui
MazeSolver::countBlanks ()
{
  int count = 0;
  for (int i = 0; maze[i] != '\0'; i++)
    {
      if (maze[i] == ' ')
    count++;
    }
  return count;
}

void
MazeSolver::showMaze ()
{
  for (int i = 0; maze[i] != '\0'; i++)
    {
      if (maze[i] == '\n')
    cout << maze[i];
      else
    cout << maze[i];
    }
}

void
operator<< (MazeSolver & p, char dir)
{
  int index = 0;
  while (p.maze[index] != '#')
    {
      index++;
    }


  if (dir == 'N' && p.maze[index - p.columnWidth] == ' ')
    {
      p.maze[index - p.columnWidth] = '#';
      p.maze[index] = ' ';
    }
  else if (dir == 'E' && p.maze[index + 1] == ' ')
    {
      p.maze[index + 1] = '#';
      p.maze[index] = ' ';
    }
  else if (dir == 'S' && p.maze[index + p.columnWidth] == ' ')
    {
      p.maze[index + p.columnWidth] = '#';
      p.maze[index] = ' ';
    }
  else if (dir == 'W' && p.maze[index - 1] == ' ')
    {
      p.maze[index - 1] = '#';
      p.maze[index] = ' ';
    }
}


#define MOVES 4

int
main ()
{

  char maze1[211] = { "-------------------+\n"
      "@                  |\n"
      "| | --+ | | -------+\n"
      "| |   | | |      # |\n"
      "| +-+ | | +-+ | ---+\n"
      "|   | | |   | |    |\n"
      "| | | +-+ | +-+----+\n"
      "| | |   | |        |\n"
      "| | |   | |        |\n" "+-+-+---+-+--------+\n"
  };

  char maze2[760] = { "-------------------------------+\n"
      "@                              |\n"
      "| --+ --+ --+ | --------+ | |  |\n"
      "|   |   |   | |         | | |  |\n"
      "| --+---+-+ | +-+ | | | +-+ |  |\n"
      "|         | |   | | | |   | |  |\n"
      "| ------+ | | | | | | | | +-+  |\n"
      "|       | | |#| | | | | |   |  |\n"
      "| ------+ +-+ | +-+-+-+ +-+ +--+\n"
      "|       |   | |       |   |    |\n"
      "| --+ --+ --+ +-----+ +-+ +-+  |\n"
      "|   |   |   |       |   |   |  |\n"
      "| --+ | | --+-+ | --+ | | | |  |\n"
      "|   | | |     | |   | | | | |  |\n"
      "| | +-+ | | | +-+ --+ | +-+ |  |\n"
      "| |   | | | |   |   | |   | |  |\n"
      "| | --+-+ +-+---+ --+-+ | +-+--+\n"
      "| |     |       |     | |      |\n"
      "| +---+ | ------+-+ --+ | --+  |\n"
      "|     | |         |   | |   |  |\n"
      "| ----+ +-+ | --+ +-+ | | --+--+\n"
      "|     |   | |   |   | | |      |\n"
      "+-----+---+-+---+---+-+-+------+\n"
  };

  char studentPath[41];

  ui i, k, nums[MOVES] = { 6, 2, 2, 7 };
  char dirs[MOVES] = { 'W', 'N', 'W', 'S' };

  MazeSolver m1 (maze1), m2 (maze2);

  printf ("original m1 maze...\n");
  m1.showMaze ();
  printf ("original m1 path...%s\n", m1.findPath ());
  printf ("original m1 blanks...%u\n", m1.countBlanks ());

  printf ("===========================================\n");

  for (k = 0; k < MOVES; k++)
    for (i = 0; i < nums[k]; i++)
      m1 << dirs[k];

  strcpy (studentPath, m1.findPath ());
  m1.showMaze ();
  printf ("maze1 path:   %s\n", studentPath);
  printf ("maze1 blanks: %u\n", m1.countBlanks ());

  printf ("===========================================\n");
  m1.showMaze ();
  m1 << 'N';            // this should move the altered m1 maze's '#' up 1 unit (north)
  m1 << 'W';            // this should move the '#' 1 unit to the left (West)
  strcpy (studentPath, m1.findPath ());
  m1.showMaze ();
  printf ("maze1 path:   %s\n", studentPath);
  printf ("maze1 blanks: %u\n", m1.countBlanks ());

  printf ("===========================================\n");
  strcpy (studentPath, m2.findPath ());
  m2.showMaze ();
  printf ("maze2 path:   %s\n", studentPath);
  printf ("maze2 blanks: %u\n", m2.countBlanks ());

  return 0;
}
