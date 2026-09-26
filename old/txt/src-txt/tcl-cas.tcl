# func
proc func {func} {simple.func set [$func]}
# time
proc first {} {simple.time first}
proc last {} {simple.time last}
proc next {} {simple.time next}
proc prev {} {simple.time prev}
proc point {} {simple.time point}
proc goto {point} {simple.time point $point}
proc mark {} {simple.time mark}
proc swap {} {simple.time swap}
proc step {} {simple.time step}
proc stamp {} {simple.time stamp}
# space
proc zero {} {simple.time.now zero}
proc one {{plane 0}} \
  {simple.time.now fill $plane 1 1}
proc solid {{size 16} {plane 0}} \
  {simple.time.now fill $plane $size 1}
proc rand {{rand 2} {plane 0}} \
  {simple.time.now fill $plane 0 $rand}
proc brand {{bloc 0} {rand 2} {plane 0}} {
  simple.time.now fill $plane $bloc $rand}
proc extract {{plane 0} {flip 1}} \
  {simple.time.now extract $plane $flip}
proc save \
  {{file plane.pbm} {plane 0} {flip 0}} {
  simple.time.now write $plane $flip $file
  extract $plane}

# simple
proc apply {} {simple apply}
# dump
proc view {} {dump dump}
# gen
proc repeat {{cnt 1} body} \
  {loop i 0 $cnt {uplevel $body}}

# proc
proc store {} {apply; next; swap; step; stamp}
proc sync {} {extract; view}

proc tofirst {body} \
  {while {![simple.time firstp]} \
  {uplevel $body}}
proc tolast {body} \
  {while {![simple.time lastp]} \
  {uplevel $body}}
proc run {{cnt 1}} \
  {loop i 0 $cnt {apply; swap}; sync}
proc record \
  {{view 1} {run 1}} \
  {tolast {store; repeat $view {run $run}}}
proc forw {{skip 1}} {
  for {set i [simple.time point]; \
  set cnt [last; simple.time point]} \
  {$i <= $cnt} {incr i $skip} {
    simple.time point $i
    view
  }
  if {$i > $cnt} { last; view }
}
proc back {{skip 1}} {
  for {set i [simple.time point]} \
  {$i >= 0} {incr i -$skip} \
  {simple.time point $i; view}
  if {$i < 0} { first; view }
}

proc cycle {{skip 1}} {forw $skip; back $skip}
proc cont {} {last; swap; first; swap; sync}

proc seq {{view_timer 1} {store_timer 1}} {
  set store 1
  set view $view_timer
  while {![simple.time lastp]} {
    apply
    if {$store && ![incr store -1]} {
      set store $store_timer
      next
    }
    swap; step; stamp
    if {$view && ![incr view -1]} {
      set view $view_timer
      extract
      view
    }
  }
  extract; view
}

view
