This is Cody Skala (cws26) and here is my Algorithms Project 1.
Everything is included that needs to be and has been tested on a lab machine with Linux.
If anything is missing, please let me know so I may correct it accordingly.
----------------------------------------------------------------------------------------
To execute part 1 of the project (rsa number generation), navigate to the Project1Part1
folder and type: make clean
Next, to compile and regenerate the files, type: make all
Finally to run, type: ./rsa435
This should run in about 5 to 10 minutes at most.
Also take note, the requirements indicate p and q to be 512 bits, that is 154 decimal
digits. To be safe, my numbers should be at least this size.
Another note: e*d should not equal (p-1)(q-1) but (e*d)%[(p-1)(q-1)] should be 1
----------------------------------------------------------------------------------------
To execute part 1 of the project (signing and verifying), navigate to the Project1Part2
folder and type: make all
To run, type ./sign s someFilename.extension
             ./sign v someFilename.extension.signed
The first will sign a given file and the second will verify it has not been altered.
After running the verification, the last line should indicate if the file has changed.
Important note: In order for the Makefile and the BigInteger library to work properly,
Project1Part1 and Project1Part2 MUST have the same root folder.
This is because Project1Part2 looks to parent folder and then looks for Project1Part1
----------------------------------------------------------------------------------------
Overall, this was a fun project and learned a lot about digital signatures and look
forward to working with more algoritm projects as the semester goes along.