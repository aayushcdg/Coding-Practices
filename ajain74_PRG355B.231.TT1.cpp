/*
   program:         ajain74_PRG355B.231.TT1.cpp
   student:         Aayush Jain
   student number:  125609214
   date:            march 24, 2023
   purpose:         solution to PRG355B Midterm Test
*/

StringTwister::StringTwister ()
{				//Default constructor assigning
  int i = 0;			// not-available to all the strings
  while (i < 10)
    {
      strcpy (list[i], "not-available");
      i++;
    }

  flip = 0;
  total = 10;
  pos = 0;
}

StringTwister::StringTwister (int n, const char *s)
{				// Constructor that initializes
  int i = 0;			//the first n strings to s and
  //the rest to "not-available"
  while (i < n)
    {
      strcpy (list[i], s);
      i++;
    }

  while (i < 10)
    {
      strcpy (list[i], "not-available");
      i++;
    }

  flip = 0;
  total = 10 - n;		// 0 < n < 10
  pos = n;
}

int
StringTwister::operator<< (const char *s)
{				// Adds a string s to the
  switch (total)
    {				//list and returns 1 if
    case 0:			//successful, otherwise
      cout << "sorry, cannot add string..." << endl;	//returns 0
      return 0;
    default:
      if (flip == 0)
	{			// If the last operation performed
	  for (int i = pos; i > 0; i--)
	    {			//was adding to the front of the
	      strcpy (list[i], list[i - 1]);	//list, shift all strings right by
	    }			//one and add s to the front
	  strcpy (list[0], s);
	  flip = 1;
	}
      else
	{
	  strcpy (list[pos], s);
	  flip = 0;
	}
      total--;			//Decrement the total number of empty
      pos++;			//spots and increment the position at
      return 1;			//which to add the next string
    }
}

ostream & operator<< (ostream & os, const StringTwister & rhs)
{				// Outputs the list of
  for (int i = 0; i < 10; i++)
    {				//strings
      os << rhs.list[i] << endl;
    }
  return os;
}
