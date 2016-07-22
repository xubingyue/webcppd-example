PRO=helloworld

all: run
	
run:$(PRO)
	@for i in $^ ;do cd $$i && make ; cd ..;  done;

clean:$(PRO)
	@for i in $^ ;do cd $$i && make clean ; cd ..; done;