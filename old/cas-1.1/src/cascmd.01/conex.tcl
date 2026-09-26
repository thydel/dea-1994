set moore [ConexType moore 9]
set vn [ConexType vn 5]
set local [ConexType local 1]

set moore_1 [ConexList [ConexVarList [ConexVar $moore 1]]]
set moore_2 [ConexList [ConexVarList [ConexVar $moore 2]]]
set vn_1 [ConexList [ConexVarList [ConexVar $vn 1]]]
set vn_3 [ConexList [ConexVarList [ConexVar $vn 3]]]
set local_1 [ConexList [ConexVarList [ConexVar $local 1]]]
set local_2 [ConexList [ConexVarList [ConexVar $local 2]]]
set local_3 [ConexList [ConexVarList [ConexVar $local 3]]]

set moore_1_moore_1 [ConexList [ConexVarList [ConexVar $moore 1] [ConexVar $moore 1]]]
set vn_1_vn_1 [ConexList [ConexVarList [ConexVar $vn 1] [ConexVar $vn 1]]]
set local_1_local_1 [ConexList [ConexVarList [ConexVar $local 1] [ConexVar $local 1]]]

set Moore_1 [ConexSpec $moore_1 $local_1 moore_1]
set Moore_2 [ConexSpec $moore_2 $local_2 moore_2]
set VN_1 [ConexSpec $vn_1 $local_1 vn_1]