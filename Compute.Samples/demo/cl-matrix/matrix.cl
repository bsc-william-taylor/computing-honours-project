
__kernel void mul(__global float* A, __global float* B, __global float* C)
{
    const int columns = 4;
    const int rows = 4;
    
    int i = get_global_id(0);
    int j = get_global_id(1);
    
    if(i < columns && j < rows) 
    {
        float tmp = 0.0;
        
        for(int k = 0;k<columns;++k) 
        {
            tmp += A[i*rows+k] * B[i*rows+j];
        }

        C[i*rows+j] = tmp;
    }
}