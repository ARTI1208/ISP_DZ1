# ISP_DZ1 (Onegin/Hamlet sorting)

Sorts text file lines by the beginning (ignoring whitespaces and punctuation marks), then by the beginning of reversed lines (with same ignoring), then writes these results in out/res.txt alongside with original text.  

## Build && run
On linux, you can build using CMake
    
    cmake -S ./ -B out && cmake --build out
    
or by gcc 
    
    g++ -Wall -Wextra -o out/executable src/*.cpp
    
and run generated executable
   
    out/executable 

   
## Documentation
You can find documentation at https://arti1208.github.io/ISP_DZ1/html/
