# LSB Image Steganography using command line application :
## Description :
LSB steganography is the process of hiding information in the least significant bit of files such as images. Changing the LSB value of the 
individual byte brings about no noticeable effect on the total value of the byte. This principle can be used to hide secret text information
inside image files.

The application can be used to embed messages to .bmp files and also decode embedded messages to txt files. BMP files have been used because 
of their relatively larger size and the capacity to hold more information.

## Features :
- Encode secret messages : The app performs bit manipulation and embeds secret data from files like .txt files into image pixel data.
As the data bits are embedded in the LSB, it will be very difficult to detect the presence of any embedded secret info from looking at the modified image file. The modified image file is visually identical to the unmodified file. 
- Decode : The LSB data from pixel array is extracted to reconstruct the secret message into a .txt file. 
- These features can be used to exchange secret information between two parties using an image file in the BMP format
- The image is also signed by the application with a magic string. This is used to check if there is any data embedded in the application during 
the decoding process.

## How to Use :
This is a command line application that perform operations based on the command line argument passed. Instructions of use are:

Download source code, navigate to the specific directory and compile to an executable file (E.g: lsb.exe) 

### To Embed Information :
run the command in the terminal : ./lsb -e \<image_file_path\> \<secret_file_path\>.

the -e flag is used to indicate encode operation. 

Errors can be thrown under the following conditions :
- Using invalid path for image file or secret file.
- If image file is not a BMP file.
- If size of .bmp image file is too small to hold the secret information
- If file streams cannot be opened due to some issues on the side of the system 

### To Decode Information :
run the command in the terminal : ./lsb -d \<image_file_path> \<output_file_path\>.

the -d flag is used to indicate decode operation. 

the output_file_path is optional. If no path name is given an output file with a default name is created(output.txt).

Errors can be thrown under the following conditions :
- Using invalid path for image file.
- If image file is not a BMP file.
- If application signature cannot be found embedded inside the image file.
- If file streams cannot be opened due to some issues on the side of the system 

