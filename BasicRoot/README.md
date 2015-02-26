Compile and run main.c in the server directory.

Compile the two programs in the tools directory, place them somewhere accessible to the user running the server executable (normally the same folder).

Run:
chown root voodoo
chmod +s voodoo

to make the suid-setting tool functional.


Run server by with: `./server 1234`, where 1234 is the port you want it to listen on.

The aim is, given the IP and Port of the server, gain root access on the box. It's a fairly easy challenge. 

server is riddled with multiple vulns, command injection being one of them.
