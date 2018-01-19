# Copyright (C) 2011 Vincent Danjean <Vincent.Danjean@imag.fr>
#
# This Makefile try to recompile the nachos *with* -DCHANGED
#
# All NachOS flavors listed in USER_FLAVORS are compiled
# See Makefile.define-user to add/remove flavors to this list
#
# All NachOS user programs are compiled. By default, there is one
# program per C source file in test/ directory.
# See Makefile.define-user to add/remove NachOS user programs

AUTOLOAD_USERPROGS=all
AUTOLOAD_KERNELS=$(USER_FLAVORS)

AUTOLOAD_CPPFLAGS=-DCHANGED

include ../Makefile.rules-nachos

# Etape2: in/out
test:
	./nachos-userprog -rs 3 -x ./testEtape2

# testMultithreading
test1:
	./nachos-userprog -rs 3 -x ./testMultithreading

# testSemThreads
test2:
	./nachos-userprog -rs 3 -x ./testSemThreads

# fork mono multithread
test3:
	./nachos-userprog -rs 3 -x ./testForkExec2

# multi
test4:
	./nachos-userprog -rs 3 -x ./testForkExec4

# Anneau
testa:
	./nachos-network -m 0 -o 1

testb:
	./nachos-network -m 1 -o 2

testc:
	./nachos-network -m 2 -o 0

