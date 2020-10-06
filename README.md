# ISP_DZ1 (Onegin/Hamlet sorting)

Sorts text file lines by the beginning (ignoring whitespaces and punctuation marks), then by the beginning of reversed lines (with same ignoring), then writes these results in out/res.txt alongside with original text.  

## Build && run
On linux, you can build using CMake
    
    cmake -S ./ -B out && cmake --build out
    
Run generated executable (filepath is optional argument)
   
    out/executable [filepath]

Run unit tests
   
    out/tests

   
## Documentation
You can find documentation at https://arti1208.github.io/ISP_DZ1/html/
