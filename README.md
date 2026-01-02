# Parallel_Blur
Gaussian Blur implemented with openmp on example image. OpenCV used slightly for image reading. 

Instructions: (WSL)
run code with following script while inside project directory:
g++ -fopenmp tile_parallel.cpp -o blur `pkg-config --cflags --libs opencv4`

Example input:
<img width="1785" height="886" alt="image" src="https://github.com/user-attachments/assets/252e3aac-66bd-48d9-aa21-fe1221697346" />

Example output:
<img width="1883" height="879" alt="image" src="https://github.com/user-attachments/assets/82d08288-4687-4fc5-a53a-a2af7b8d8c9d" />


