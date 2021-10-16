webserver: server.c
	gcc -o server server.c 
	-fdiagnostics-color=always 
	-L/home/ramy/dev/uv_server/libuv/.libs/
	-I/home/ramy/dev/uv_server/libuv/include
	-lstdc++
	-luv
				