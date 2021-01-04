# COMP-4320
## Introduction to Networks
#### Instructor: Alvin Lim

### Instructions for running the FTP application

This project is intended for use on Linux machines

Run `unzip Project1.zip` from the linux CLI

1. Ensure that the IP address within _client.cpp_ is set to the IP address of machine that the _server.cpp_ application will be running on.
   - In order to find your IP on a linux machine run `ip addr` from the CLI.
2. Ensure that the file you want to transfer to the server is in your current working directory.  
   (We have provided our test file _Testfile_, it should be noted that this file has unix line endings)  
3. If you copy a file from Windows to Linux run the following command to ensure correct line endings `dos2unix filename`	
4. On the client run the following command:
   <pre>
   g++ client.cpp -o <i>output_filename</i>
   </pre> 
   (We have supplied _output_ which is our output file.)
5. On the server run the following command:
   <pre>
   g++ server.cpp -o <i>output_filename</i> 
   </pre>
   (We have supplied server which is our output file.)
6. On the server run the command `./output_filename` (Or if using our output file run `./server`)  
   Make sure the server is running before starting the client.
7. On the client run the following command: 
   <pre>
   ./output_filename PUT <i>filename_to_transfer</i> <i>damage_probability</i> <i>corruption_probability</i>
   </pre>
   For our testing we used the command `./output PUT Testfile .3 .2`  
   Note that for both *damage_probability* and *corruption_probability* a decimal value of less than 1 and greater than 0 is expected.
