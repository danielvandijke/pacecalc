all: pacecalc practice

pacecalc:
	cl pacecalc.c 

practice:
	cl practice.c

clean:
	del *.exe
	del *.obj