simple sockets
==============

This repository exists to store and record my "scratchwork" after reading through some of the beginning sections of Beej's Guide to Network Programming. [ https://beej.us/guide/bgnet/html/ ]

To run the server: ``make server``

To run the client: ``make client``

SUNDRY NOTES:
- The server and client must run simultaneously, so each should be run in its own terminal session.
- The client-server connection is hardcoded to occur via local port 8080, so this port should be available.
- The files in the directory called "old-way" are a more primitive client/server that use older methods as described in Beej's Guide.
