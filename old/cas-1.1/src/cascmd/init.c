char* cmd_name = "casbin";

init(void* interp) {
    Conex_init(interp);
    Func_init(interp);
    Frame_init(interp);
    conexlib_init();
    rule_init();
    extract_init();
    Space_init();
    Time_init();
    Simple_init();
    Dump_init();
}
