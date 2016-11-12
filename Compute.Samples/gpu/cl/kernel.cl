
__kernel void vector_add(
  __global const float* a,
  __global const float* b,
  __global float* result)
{
  int gid = get_global_id(0);
  result[gid] = a[gid] + b[gid];
}

__kernel void gaussian_filter(
    __read_only image2d_t src,
    __write_only image2d_t dest,
    sampler_t sampler,
    int width, int height)
{
  float kernelWeights[9] =
  {
    1.0f, 2.0f, 1.0f,
    2.0f, 4.0f, 2.0f,
    1.0f, 2.0f, 1.0f
  };

  int2 startImageCoord = (int2)(get_global_id(0) - 1, get_global_id(1) - 1);
  int2 endImageCoord = (int2)(get_global_id(0) + 1, get_global_id(1) + 1);
  int2 outImageCoord = (int2)(get_global_id(0), get_global_id(1));

  if(outImageCoord.x < width && outImageCoord.y < height)
  {
    int weight = 0;
    float4 outColor = (float4)(0.0f, 0.0f, 0.0f, 0.0f);

    for(int y = startImageCoord.y; y <= endImageCoord.y; y++)
    {
      for(int x = startImageCoord.x; x <= endImageCoord.x; x++)
      {
        outColor += (read_imagef(src, sampler, (int2)(x, y)) * (kernelWeights[weight] / 16.0f));
        weight++;
      }
    }

    write_imagef(dest, outImageCoord, outColor);
  }
}
