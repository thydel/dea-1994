rename Space2D _Space2D
itcl_class Space2D {
	public space

	public xsize 128 {
		if {$xsize > 1024 || $xsize < 32} {
			error "xsize out of bound"
		}
	}
	public ysize 128 {
		if {$ysize > 512 || $ysize < 32} {
			error "ysize out of bound"
		}
	}
	public zsize 1 {
		if {$zsize > 8 || $zsize < 1} {
			error "zsize out of bound"
		}
	}
	public file

	constructor {config} {
		if ![string compare $file ""] {
			_Space2d cmd $this-internal $xsize $ysize $zsize
		} else {
			_Space2d cmd $this-internal $file
		}
		set space [$this-internal]
	}

	method handle {} {return [$this-internal]}
	method zero {} {$this-internal zero}
	method one {{plane 0}} {$this-internal fill $plane 1 1}
	method solid {size plane} {$this-internal fill $plane $size 1}
}

rename Time2D _Time2D
itcl_class Time2D {
	inherit Space2D

	public time

	public cnt 64 {
		if {$cnt > 512 || $cnt < 2} {
			error "cnt out of bound"
		}
	}

	proc constructor {config} {
		_Time2D cmd $this-internal $space $cnt
		set time [$this-internal]
	}
}

rename Dump2D _Dump2D
itcl_class Dump2D {
	inherit Time2D

	public dumper

	public plane 1 {
		if {$plane < 1 || $plane > 8} {
			error "plane out of bound"
		}
	}

	proc constructor {config} {
		_Dump2D cmd $this-internal $time $plane
		set dumper [$this-internal]
	}

	method dump {} {$this-internal dump}
}
