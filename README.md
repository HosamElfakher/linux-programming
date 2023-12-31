# linux-programming
Welcome to the Linux Programming repository! This repository serves as a comprehensive demonstration of Linux programming fundamentals. The repository is organized into directories, meticulously categorized according to the main Linux topics. Each directory contains source files for different sub-topics and a make file to facilitate easy compilation.

Below is an overview of the covered topics presented in a hierarchical tree form:

1- Signals                                                                                 
         1.1- Basic signal functionality                                                   
         1.2- Signal masking                                                               
         1.3- sigaction   
                                                                          
2- Timers
         
3- Process                                                                         
          3.1- fork basics                                                         
          3.2- Orphans process                                                     
          3.3- Zombie process                                                      
          3.4- signal and process 

4- Threads                                                                                
          4.1- thread creation                                                            
          4.2- mutex synchronization                                                       
          4.3- Conditional variables                                                       

5- Schedular policy and priorities                      

6- daemon                      

7- pipe                   
          7.1- pipe basics                                                     
          7.2- Tie pipe to execute shell commands                                                

8- POSIX IPC                   
          8.1- MesQueue  

Compiling the Programs
To successfully compile the programs, please follow these steps:

- Install GCC tool chain and make 
- Navigate to the directory of interest corresponding to the topic you wish to explore.
- Execute the following command: make <program_name>

For example, to compile the source file signal_basics.c under the "Signals" topic, run the command: make signal_basics.c
