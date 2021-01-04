# COMP-4320
## Introduction to Networks
#### Instructor: Alvin Lim

### Instructions for running the FTP application

Run `unzip Project1.zip` from the linux CLI

1. Ensure that the IP address within _client.cpp_ is set to the IP address that _server.cpp_ is going to be running on
	In order to find your IP on a linux machine run `ip a` from the CLI
2. Ensure that the file you want to transfer to the server is in your current directory 
	(We have provided our test file _Testfile_, it should be noted that this file has unix line endings)
3. If you copy a file from windows to linux that make to run  `dos2unix filename`	
4. On the client <pre>run g++ client.cpp -o <b>output_filename<b><pre> (We have supplied output which is our output file)
5. On the server `run g++ server.cpp -o`*`output_filename`* (We have supplied server which is our output file)
6. On the server run the command `./output_filename` (Or if using our output file run `./server`)
	Make sure the server is running before starting the client
7. On the client run the command `./`*`output_filename`*`PUT`*`filename_to_transfer`*_`damage_probability`_*`corruption_probability`*
	For out testing we used the command `./output PUT Testfile .3 .2`
	Also note that for both *damage_probability* and *corruption_probability* a decimal value of less than 1 and greater than 0 is expected
