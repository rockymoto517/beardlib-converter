# How to use

Make sure that the output folder hasn't been created, the tool will create the folder for you

1. Extract the folder somewhere and open it    
2. Click on the explorer bar inside the folder window, type in cmd, and press enter
3. Drag and drop a customOST song into the Converter folder
4. Write into the command line: Converter folder_name output_folder_name

## CMake

1. Create a build directory
2. cmake ../ and build
3. Move the executable to the parent folder

### To convert an entire folder

1. Create a new folder and drop the songs you want to convert inside there
2. Write: Converter -r folder_with_multiple_folders output_folder_name

#### Troubleshooting
You'll get assertion errors if the track.txt is written in improper json, so if you get an error, try validating the json
