# Text-Encoder-and-Decoder
A program that encodes an input .txt file by rotating the ASCII bits of each character, and can decode by reversing the rotation.

Example usage in Linux:

user~$: make
user~$: ./encode exampleInput.txt cipher.bin ### Creates an output file called cipher.bin with the encrypted text.
user~$: ./decode cipher.bin output.txt ### Creates an output file called output.txt with the decrypted text, an identical file to the original input, exampleInput.txt.
