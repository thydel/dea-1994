von_neumann_64_64_3_0 (unsigned char *past, unsigned char *futur,
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
  index = ((north[63] << 24) | (center[63] << 21) | (south[63] << 18));
  index = (index | (*north++ << 15) | (*center++ << 12) | (*south++ << 9));
  index = (index | (*north++ << 6) | (*center++ << 3) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		((index & 0xe00000) >> 9))];
/* cols */
  for (col = 62; col--;)
    {
/* set_col_index */
      index = ((index << 9) | (*north++ << 6) | (*center++ << 3) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		    ((index & 0xe00000) >> 9))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 9) | (north[-64] << 6) | (center[-64] << 3) | south[-64]);
/* set_futur */
  *futur++ =
    transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		((index & 0xe00000) >> 9))];
  north = past;
  center = (north + side);
  south = (center + side);
  for (line = 62; line--;)
    {
/* conex */
/* first_col */
/* set_first_col_index */
      index = ((north[63] << 24) | (center[63] << 21) | (south[63] << 18));
      index =
	(index | (*north++ << 15) | (*center++ << 12) | (*south++ << 9));
      index = (index | (*north++ << 6) | (*center++ << 3) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		    ((index & 0xe00000) >> 9))];
/* cols */
      for (col = 62; col--;)
	{
/* set_col_index */
	  index =
	    ((index << 9) | (*north++ << 6) | (*center++ << 3) | *south++);
/* set_futur */
	  *futur++ =
	    transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
			((index & 0xe00000) >> 9))];
	}
/* last_col */
/* set_last_col_index */
      index =
	((index << 9) | (north[-64] << 6) | (center[-64] << 3) | south[-64]);
/* set_futur */
      *futur++ =
	transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		    ((index & 0xe00000) >> 9))];
    }
  north = (past + (size - (side << 1)));
  center = (north + side);
  south = past;
/* conex */
/* first_col */
/* set_first_col_index */
  index = ((north[63] << 24) | (center[63] << 21) | (south[63] << 18));
  index = (index | (*north++ << 15) | (*center++ << 12) | (*south++ << 9));
  index = (index | (*north++ << 6) | (*center++ << 3) | *south++);
/* set_futur */
  *futur++ =
    transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		((index & 0xe00000) >> 9))];
/* cols */
  for (col = 62; col--;)
    {
/* set_col_index */
      index = ((index << 9) | (*north++ << 6) | (*center++ << 3) | *south++);
/* set_futur */
      *futur++ =
	transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		    ((index & 0xe00000) >> 9))];
    }
/* last_col */
/* set_last_col_index */
  index =
    ((index << 9) | (north[-64] << 6) | (center[-64] << 3) | south[-64]);
/* set_futur */
  *futur++ =
    transition[(((index & 0x38) >> 3) | ((index & 0x3fe00) >> 6) |
		((index & 0xe00000) >> 9))];
}
