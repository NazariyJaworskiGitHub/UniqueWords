by Nazariy Jaworski (c)
nazariyjaworski@gmail.com 
---------------------------------------------------------------------------------------------------

### How to use
- Windows
md build
cd build
cmake -G "MinGW Makefiles" ../
mingw32-make
./UniqueWords ../input.txt

- Linux
mkdir build
cd build
cmake ..
make
./UniqueWords ../input.txt
---------------------------------------------------------------------------------------------------

### How does it work
The input text is guaranteed to contain only 'a'..'z' and space characters in ASCII encoding.

Algorithm for counting distinct words in a file using the divide-and-conquer approach:
- Input: Read the file name from command-line arguments.
- Check File: Verify if the file exists and is accessible.
- Determine Threads: Get the number of available CPU threads for parallel processing.
- Divide File: Split the file into equal-sized chunks based on the number of threads.
- Process Chunks: For each chunk:
    - Seek to the start of the chunk.
    - Adjust the start position to skip any characters before the first whitespace.
    - Read words until reaching the end of the chunk, inserting them into a local unordered_set.
- Merge Results: Combine the sets of distinct words from each chunk into a final set:
    - Use parallel processing to merge sets in pairs.
- Output Result: Print the total count of distinct words from the final set.
- End: Terminate the program.

The algorithm utilizes parallel processing to handle large files.

Time Complexity:
- Chunking: 𝑂(p), where 𝑛 is the number of threads avaliable threads. Ususally p is small relative to further steps and can be neglected.
- Processing Chunks: Each chunk is processed independently, resulting in 𝑂(𝑛) as each word is read and inserted into a set.
- Merging Sets: The merging operation, involving union of sets, is also 𝑂(𝑚) for each set, where 𝑚 is the number of unique words. The overall merging complexity is amortized based on the number of chunks and can be expressed as O(𝑚+𝑘log𝑘), but usually 𝑘<<𝑚 which leads to 𝑂(𝑚) complexity.
- Overall, the expected time complexity is 𝑂(𝑛+𝑚).
#TODO needs confirmation
---------------------------------------------------------------------------------------------------

#TODO
Z Bar-Yossef, TS Jayram, R Kumar, D Sivakumar, L Trevisan, Counting Distinct Elements in a Data Stream, 2002
https://citeseerx.ist.psu.edu/document?repid=rep1&type=pdf&doi=e3497952347101a3535434bc35d378224cf87bcc

S Chakraborty, NV Vinodchandran, KS Mee, Distinct Elements in Streams: An Algorithm for the (Text) Book, 2023
https://arxiv.org/pdf/2301.10191