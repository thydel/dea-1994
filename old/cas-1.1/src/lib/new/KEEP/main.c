main() {
    ConexType* moore_type = ConexType_new("moore", 9);
    ConexType* local_type = ConexType_new("local", 1);
    ConexSpec* moore = ConexSpec_new(ConexList_new(ConexVar_new(moore_type, 1), 0),
				     ConexList_new(ConexVar_new(local, 1), 0),
				     moore_1);
    Simple2D simple = Simple2D_new(Time2D_new(Space2D_new(256, 256, 1), 2),
				   Func_new(moore, 0, life, 0));
    Action* dump = Action_new(DumpNow_dump, DumpNow_new(simple->time, 1));
    Simple_action(simple, dump, 0);
    Action* stat = Action_new(StatNow_stat, StatNow_new(simple->time, 1));
    Simple_action(simple, dump, 1);
    Action* plot = Action_new(Plot_plot, Plot_new(simple->time, 1));
    Simple_action(simple, dump, 0);
}
