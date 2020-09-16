CC = Login.o Register.o ClientSocket.o ContactModule.o ReceiveModule.o WriteModule.o

all:$(CC)

Login.o:Login.c
	gcc -c Login.c -o ../obj/Login.o 

Register.o:Register.c 
	gcc -c Register.c -o ../obj/Register.o 

ClientSocket.o:ClientSocket.c 
	gcc -c ClientSocket.c -o ../obj/ClientSocket.o

ContactModule.o:ContactModule.c 
	gcc -c ContactModule.c -o ../obj/ContactModule.o

ReceiveModule.o:ReceiveModule.c 
	gcc -c ReceiveModule.c -o ../obj/ReceiveModule.o

WriteModule.o:WriteModule.c 
	gcc -c WriteModule.c -o ../obj/WriteModule.o

libloginmodule.a:$(CC)
	ar rv libloginmodule.a $(CC)

clean:
	rm ../obj/*.o libloginmodule.a