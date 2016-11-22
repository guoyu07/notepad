CXX= g++
CFLAGS= -Wall --std=c++11 
CFLAG= -g -Wall -Weffc++ -Wextra -pedantic
LDFLAGS = -lm

run:main.o User.o regularUser.o adminUser.o Note.o Dao.o Manager.o
	${CXX} ${CFLAGS} -o notes main.o User.o regularUser.o adminUser.o Note.o Dao.o Manager.o -o notes.cgi

cli:main_cli.o Board.o Player.o TTTController.o PlayerDao.o
	${CXX} ${CFLAGS} -o ttt main_cli.o Board.o Player.o TTTController.o PlayerDao.o -o ttt.cgi

test:sampleTest.o Board.o Player.o TTTController.o PlayerDao.o
	${CXX} ${CFLAGS} -o ttt sampleTest.o Board.o Player.o TTTController.o PlayerDao.o -o test.cgi

main.o:main.cpp
	${CXX} ${CFLAGS} -c main.cpp

main_cli.o:main_cli.cpp
	${CXX} ${CFLAGS} -c main_cli.cpp

User.o: ./model/Users/User/User.cpp
	${CXX} ${CFLAGS} -c ./model/Users/User/User.cpp ./model/Users/User/User.h

Dao.o: ./model/Dao.cpp
	${CXX} ${CFLAGS} -c ./model/Dao.cpp ./model/Dao.h

Note.o: ./model/Notes/Note.cpp
	${CXX} ${CFLAGS} -c ./model/Notes/Note.cpp ./model/Notes/Note.h

regularUser.o: ./model/Users/regularUser.cpp 
	${CXX} ${CFLAGS} -c ./model/Users/regularUser.cpp ./model/Users/regularUser.h

adminUser.o: ./model/Users/adminUser.cpp 
	${CXX} ${CFLAGS} -c ./model/Users/adminUser.cpp ./model/Users/adminUser.h

Manager.o: ./controller/Manager.cpp
	${CXX} ${CFLAGS} -c ./controller/Manager.cpp ./controller/Manager.h

sampleTest.o:sampleTest.cpp
	${CXX} ${CFLAGS} -c sampleTest.cpp

clean:
	rm -rf *.o
	rm -rf *~
	rm -rf run ttt.cgi test.cgi
