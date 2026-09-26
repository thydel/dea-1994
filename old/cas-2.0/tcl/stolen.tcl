#
# stolen to tk library to add a binding for button 2
#

# The procedure below is invoked when the mouse button is released
# for a button/radiobutton/checkbutton widget.  It restores the
# button's relief and invokes the command as long as the mouse
# hasn't left the button.

proc my_tk_butUp {w b} {
    global tk_priv
    if {$w == $tk_priv(buttonWindow)} {
	$w config -relief $tk_priv(relief)
	if {($w == $tk_priv(window))
		&& ([lindex [$w config -state] 4] != "disabled")} {
	    uplevel #0 [list $w invoke]
	}
	set tk_priv(buttonWindow) ""
    }
}
