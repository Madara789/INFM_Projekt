# SUBSCALE algorithm for GPUs

This implementation of the SUBSCALE algorithm was created as part of a master thesis at Hochschule Offenburg. As part of the team project in the Master of Computer Science, this code was extended by a distributed calculation. 

## Compilation

In all cases cuda is needed for compiling the code. Execution is possible without.

### cMake

When compiling with cMake, a Makefile is used. The following make instructions can be used to compile the code.

```
make init   // downloads all sub directories
make install-dependencies   // installs all dependencies [gRPC, nlohmann-json, mlpack]
make build  // builds cmake changes
make compile    // compiles the code 
```

When the packages (gRPC, nlohmann-json, mlpack) are locally installed, they can be linked in the CMakeLists. Then the following make instructions are necessary.

```
make build  // builds cmake changes
make compile    // compiles the code 
```

### Visual Studio

will be added soon

## Configuration
When the application is started, the path to a config file has to be passed as a command line argument. The config file allows the user to specify various parameters for the application. The file `config.json` is an example for a config file. 

A parameter that currently can't be altered inside of a config file, is the maximum size of files that are read or written from/to system memory. This is set to 50MB, however if the use of larger files is required, the size can be increased inside of the class `CsvDataHandler`.

## Executing

To start the calculation, the following make instruction can be made.

```
make start-subscale // executes the code in sequentiell // parallel on one machine
```

For the distributed execution there are some additional make instructions.

```
make start-server // starts the server for distributed execution
make start-client // starts the client for distributed execution
```