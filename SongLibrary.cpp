

CompactDisc::CompactDisc ()
{
  total = 20;
  current = -1;
  strcpy (artist, "not-available");
  p = new struct song[total];
  for (int i = 0; i < total; i++)
    {
      initSong (&p[i], "not-available", 0, 0.0);
    }
}

CompactDisc::CompactDisc (int num, const char *name)
{
  total = num;
  current = 0;
  strncpy (artist, name, 120);
  artist[120] = '\0';
  p = new struct song[total];
  for (int i = 0; i < total; i++)
    {
      initSong (&p[i], "not-available", 0, 0.0);
    }
}

CompactDisc::CompactDisc (const CompactDisc & from)
{
  total = from.total;
  current = from.current;
  strncpy (artist, from.artist, 120);
  artist[120] = '\0';
  p = new struct song[total];
  for (int i = 0; i < total; ++i)
    {
      initSong (&p[i], from.p[i].title, from.p[i].track, from.p[i].time);
    }
}

CompactDisc::~CompactDisc ()
{
  delete[]p;
}

CompactDisc & CompactDisc::operator= (const CompactDisc & from)
{
  if (this == &from)
    {
      return *this;
    }
  delete[]p;
  total = from.total;
  current = from.current;
  strncpy (artist, from.artist, 120);
  artist[120] = '\0';
  p = new struct song[total];
  for (int i = 0; i < total; ++i)
    {
      initSong (&p[i], from.p[i].title, from.p[i].track, from.p[i].time);
    }
  return *this;
}

int
CompactDisc::setSong (struct song x, int index)
{
  if (index < 0 || index >= total)
    {
      return false;
    }
  initSong (&p[index], x.title, x.track, x.time);
  return true;
}

void
CompactDisc::getSong (struct song *ps)
{
  if (current >= 0)
    {
      *ps = p[current];
    }
  else
    {
      initSong (ps, "not-available", 0, 0.0);
    }
}

song & CompactDisc::getSong (int pos)
{
  return p[pos];
}

int
CompactDisc::operator+= (struct song copy)
{
  if (current == total - 1)
    {
      return false;
    }
  ++current;
  initSong (&p[current], copy.title, copy.track, copy.time);
  return true;
}

int
CompactDisc::getTotal ()
{
  return total;
}

// getCurrent function
int
CompactDisc::getCurrent ()
{
  return current - 1;
}

// getArtist function
const char *
CompactDisc::getArtist ()
{
  return artist;
}
