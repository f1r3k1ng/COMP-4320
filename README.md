# COMP-4320
## Introduction to Networks
#### Instructor: Alvin Lim
#### Grade Received: A
### Project Specification

The goal of this project is to create a simple FTP application where a client machine can send a file to a server machine. There were some additional requirements for this project, the first was to create a function called gremlin that would either alter packets or sometimes drop packets altogether. This was used to simulate packet loss and packet corruption. The frequency of packet modification, the extent of packet modification, and if the packet is lost completely are all determined by user input via CLI arguments. The other main requirement is how the server would handle receiving normal and abnormal packets. The server had the responsibility of outputting to stdout if a packet was missing and for checking the integrity of each packet to see if the packet was modified by the gremlin function. To accomplish both of these we implemented to values into a packet header a sequence number and a checksum. The sequence number was created on the client side and then checked when the packet arrived to the server to ensure packets were in order and there was no packet loss. Then for the checksum we put every packet through an algorithm that would compute a unique value associated with the packet and then the same checksum algorithm was run on the server side to ensure that the packet was not modified. Lastly the server had to write every packet to an output file, the only somewhat odd thing here is that we were told to still write corrupted packets to the file. We were able to successfully meet all of the requirements of this project.

### Instructions for running the FTP application

This project is intended for use on Linux machines

Clone the repository and put the server folder on you server machine and the client folder on your client machine.  
(It might me easier to just clone the repo on both machines)

1. Ensure that the IP address within _client.cpp_ is set to the IP address of machine that the _server.cpp_ application will be running on.
   - In order to find your IP on a linux machine run `ip addr` from the CLI.
2. Ensure that the file you want to transfer to the server is in your current working directory.  
   (We have provided our test file _Testfile_, it should be noted that this file has unix line endings)  
3. If you copy a file from Windows to Linux run the following command: `dos2unix filename`	
4. On the client run the following command:
   <pre>
   g++ client.cpp -o <i>output_filename</i>
   </pre> 
   (We have supplied _output_ which is our output file.)
5. On the server run the following command:
   <pre>
   g++ server.cpp -o <i>output_filename</i> 
   </pre>
   (We have supplied _server_ which is our output file.)
6. On the server run the command `./output_filename` (Or if using our output file run `./server`)  
   Make sure the server is running before starting the client.
7. On the client run the following command: 
   <pre>
   ./<i>output_filename</i> PUT <i>filename_to_transfer</i> <i>damage_probability</i> <i>corruption_probability</i>
   </pre>
   For our testing we used the command `./output PUT Testfile .3 .2`  
   - For *damage_probability* and *corruption_probability* a decimal value <1 and >0 is expected.

### Improvements that could be made
- Implement arguments as optional so that if no arguments are given a default set of arguments is loaded.
- Add IP address as an argument so that it does not have to be changed within the code itself.
- Implement a form of either go-back-n or selective repeat to ensure retransmission of corrupted and lost packets.
- Create a makefile to make running the application easier and more standard.

**-f1r3k1ng**