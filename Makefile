all: server client


server: main.o record.o serv.o PR.o 
	g++ -g -O3 -DZACHET -W -Wall   main.o record.o serv.o PR.o -o server
main.o: main.cpp
	g++ -c -g -O3 -DZACHET -W -Wall   main.cpp 
record.o: record.cpp
	g++ -c -g -O3 -DZACHET  -W -Wall  record.cpp
serv.o: serv.cpp
	g++ -c -g -O3 -DZACHET -W -Wall  serv.cpp

client: cli_tcp.o PR.o
	g++  -g -O3 -W -Wall  cli_tcp.o PR.o -o client
cli_tcp.o: cli_tcp.cpp 
	g++ -c -g -O3 -W -Wall  cli_tcp.cpp


PR.o: PR.cpp
	g++ -c -g -O3 -DZACHET -W -Wall   PR.cpp
	
clean:
	rm -f *.o *.out *.exe server client *.txt *.log
