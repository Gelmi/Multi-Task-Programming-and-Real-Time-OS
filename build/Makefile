CC=g++
CC_TEST=arm-linux-g++
CFLAGS=-Wall -Wextra

all: clear td1a td2a td2a td2b td2c td2d td2e td3a td3b td3c td3d td4b

clear:
	rm td*

td1a: $(SRC)
	$(CC) -o $@ ../src/td1a.cpp ../src/timespec.cpp $(CFLAGS)

td1b: $(SRC)
	$(CC) -o $@ ../src/td1b.cpp ../src/timespec.cpp ../src/chrono.cpp $(CFLAGS)

td2a: $(SRC)
	$(CC) -o $@ ../src/td2a.cpp $(CFLAGS)

td2b: $(SRC)
	$(CC) -o $@ ../src/td2b.cpp ../src/timer.cpp ../src/timespec.cpp $(CFLAGS)

td2c: $(SRC)
	$(CC) -o $@ ../src/td2c.cpp ../src/chrono.cpp ../src/timespec.cpp ../src/looper.cpp $(CFLAGS)

td2d: $(SRC)
	$(CC) -o $@ ../src/td2d.cpp ../src/chrono.cpp ../src/timespec.cpp ../src/looper.cpp ../src/calibrator.cpp ../src/timer.cpp $(CFLAGS)

td2e: $(SRC)
	$(CC) -o $@ ../src/td2e.cpp ../src/cpuloop.cpp ../src/chrono.cpp ../src/timespec.cpp ../src/looper.cpp ../src/calibrator.cpp ../src/timer.cpp $(CFLAGS)

td3a: $(SRC)
	$(CC) -o $@ ../src/td3a.cpp $(CFLAGS)

td3b: $(SRC)
	$(CC) -o $@ ../src/td3b.cpp ../src/mutex.cpp ../src/timespec.cpp $(CFLAGS)

td3c: $(SRC)
	$(CC) -o $@ ../src/td3c.cpp ../src/thread.cpp ../src/chrono.cpp ../src/mutex.cpp ../src/timespec.cpp $(CFLAGS)

td3d: $(SRC)
	$(CC) -o $@ ../src/td3d.cpp ../src/counter.cpp ../src/thread.cpp ../src/chrono.cpp ../src/mutex.cpp ../src/timespec.cpp $(CFLAGS)

td3e: $(SRC)
	$(CC) -o $@ ../src/td3e.cpp ../src/thread.cpp ../src/cpuloop.cpp ../src/calibrator.cpp ../src/mutex.cpp $(CFLAGS)

td4a: $(SRC)
	$(CC) -o $@ ../src/monitor.cpp ../src/mutex.cpp ../src/timespec.cpp $(CFLAGS)

td4b: $(SRC)
	$(CC) -o $@ ../src/td4b.cpp ../src/semaphore.cpp ../src/thread.cpp ../src/mutex.cpp ../src/monitor.cpp ../src/timespec.cpp ../src/chrono.cpp $(CFLAGS)
