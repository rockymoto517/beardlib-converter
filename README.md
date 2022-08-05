# How to use

Make sure that the output folder hasn't been created, the tool will create the folder for you

1. Extract the folder somewhere and open it    
2. Click on the explorer bar inside the folder window, type in cmd, and press enter
3. Drag and drop a customOST song into the Converter folder
4. Write into the command line: Converter folder_name output_folder_name

## CMake

1. Create a build directory
2. cd into it
3. cmake ../ && make (if you're using mingw, use cmake ../ -G "MinGW Makefiles" && make)
4. Move the executable to the parent folder

### To convert an entire folder

1. Create a new folder and drop the songs you want to convert inside there
2. I've included a recursive_tests folder to use. 
3. Write: Converter -r recursive_tests output_folder

#### Troubleshooting
You'll get errors if the track.txt is written in improper json.
The program may not be able to find all folders when doing a recursive conversion if the folder names have spaces or special characters.