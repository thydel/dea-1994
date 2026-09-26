bind(ConexInfo* conex) {
    int size;
    $$(void $(bind_name())(StateVect* rule_vect, int (*func)()) {
	int index;
	$(size = public << conex_cnt[conex] + 1 + private;)
	    for (index = 0; index < $(size); ++index) {
		$(for (i = 0; i < conex->cnt; ++i) {
		    $$($(conex->name[i]) =
		       (index & $(mask(public)) << $(public * (conex->cnt - i))) >> $(public * (conex->cnt - i));)
		    }
		  rule_vect->ptr[index] = func();
		  )
		}
    }
       )
    }
