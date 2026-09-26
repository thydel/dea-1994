# moore and vn are standard Moore and von Neumann neighborhood
set moore [ConexType moore 9]
set vn [ConexType vn 5]
# local mean only in center cell
set local [ConexType local 1]

# one and four state Moore
set moore_1 [ConexList [ConexVarList [ConexVar $moore 1]]]
set moore_2 [ConexList [ConexVarList [ConexVar $moore 2]]]
# von Neumann neighborhood allows 8 states per cells
set vn_3 [ConexList [ConexVarList [ConexVar $vn 3]]]
# local bits are cheap
set local_4 [ConexList [ConexVarList [ConexVar $local 4]]]

# these means one rule per planes
set moore_1_moore_1 \
	[ConexList [ConexVarList [ConexVar $moore 1] [ConexVar $moore 1]]]

# the thirds arg is the name of an application function
set Moore_1 [ConexSpec $moore_1 $local_1 moore_1]
set Moore_2 [ConexSpec $moore_2 $local_2 moore_2]
set VN_1 [ConexSpec $vn_1 $local_1 vn_1]
