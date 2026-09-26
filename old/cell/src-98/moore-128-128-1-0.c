moore_128_128_1_0 (unsigned char *past, unsigned char *futur,
		   unsigned char *transition, int side, int size)
{
  register unsigned char *north;
  register unsigned char *center;
  register unsigned char *south;
  register int index;
  int line;
  int col;

  north = (past + (size - side));
  center = past;
  south = (center + side);
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[127] << 8) | (center[127] << 7) | (south[127] << 6));
  index = (index | (*north++ << 5) | (*center++ << 4) | (*south++ << 3));
  index = (index | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
  *futur++ = transition[index];
/* cols */
  for (col = 126; col--;)
    {
/* set_col_index */
      index =
	(((index << 3) & 0x1ff) | (*north++ << 2) | (*center++ << 1) |
	 *south++);
/* set_futur */
      *futur++ = transition[index];
    }
/* last_col */
/* set_last_col_index */
  index =
    (((index << 3) & 0x1ff) | (north[-128] << 2) | (center[-128] << 1) |
     south[-128]);
/* set_futur */
  *futur++ = transition[index];
  north = past;
  center = (north + side);
  south = (center + side);
  for (line = 126; line--;)
    {
/* conex */
/* first_col */
/* set_first_col_index */
      index = ((north[127] << 8) | (center[127] << 7) | (south[127] << 6));
      index = (index | (*north++ << 5) | (*center++ << 4) | (*south++ << 3));
      index = (index | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
      *futur++ = transition[index];
/* cols */
      for (col = 126; col--;)
	{
/* set_col_index */
	  index =
	    (((index << 3) & 0x1ff) | (*north++ << 2) | (*center++ << 1) |
	     *south++);
/* set_futur */
	  *futur++ = transition[index];
	}
/* last_col */
/* set_last_col_index */
      index =
	(((index << 3) & 0x1ff) | (north[-128] << 2) | (center[-128] << 1) |
	 south[-128]);
/* set_futur */
      *futur++ = transition[index];
    }
  north = (past + (size - (side << 1)));
  center = (north + side);
  south = past;
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[127] << 8) | (center[127] << 7) | (south[127] << 6));
  index = (index | (*north++ << 5) | (*center++ << 4) | (*south++ << 3));
  index = (index | (*north++ << 2) | (*center++ << 1) | *south++);
/* set_futur */
  *futur++ = transition[index];
/* cols */
  for (col = 126; col--;)
    {
/* set_col_index */
      index =
	(((index << 3) & 0x1ff) | (*north++ << 2) | (*center++ << 1) |
	 *south++);
/* set_futur */
      *futur++ = transition[index];
    }
/* last_col */
/* set_last_col_index */
  index =
    (((index << 3) & 0x1ff) | (north[-128] << 2) | (center[-128] << 1) |
     south[-128]);
/* set_futur */
  *futur++ = transition[index];
}
