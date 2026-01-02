# Parallel_Blur
Gaussian Blur implemented with openmp on example image. OpenCV used slightly for image reading. 

Instructions: (WSL)
1) replace/upload image to project directory with title "input.jpg"
2) compile code with following script while inside project directory:
g++ -fopenmp tile_parallel.cpp -o blur `pkg-config --cflags --libs opencv4`
3) run program
./blur

Outputs:
1) result image will be in project directory titled "blurred.jpg"
2) runtime of parallel section will be output in terminal in seconds.

Example input image:
<img width="1785" height="886" alt="image" src="https://github.com/user-attachments/assets/252e3aac-66bd-48d9-aa21-fe1221697346" />

Example output image:
<img width="1707" height="789" alt="image" src="https://github.com/user-attachments/assets/805c00cf-aff6-4571-a2a4-fec80feefe25" />




