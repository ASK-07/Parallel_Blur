# Parallel_Blur
Gaussian Blur implemented with openmp on example image. OpenCV used slightly for image reading. 

Instructions: (WSL)
run code with following script while inside project directory:
g++ -fopenmp tile_parallel.cpp -o blur `pkg-config --cflags --libs opencv4`

Example input:
<img width="1785" height="886" alt="image" src="https://github.com/user-attachments/assets/252e3aac-66bd-48d9-aa21-fe1221697346" />

Example output:
<img width="1328" height="864" alt="image" src="https://github.com/user-attachments/assets/68a92a1a-ff52-4e25-bd5d-db9ad906ae43" />



