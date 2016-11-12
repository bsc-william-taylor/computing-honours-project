
__kernel void vector_add(__global const float* a, __global const float* b, __global float* result)
{
  int gid = get_global_id(0);
  result[gid] = a[gid] + b[gid];
}

__kernel void vector_sub(__global const float* a, __global const float* b, __global float* result)
{
  int gid = get_global_id(0);
  result[gid] = a[gid] - b[gid];
}

__kernel void grayscale(__read_only image2d_t src, __write_only image2d_t dest, sampler_t sampler, int width, int height)
{
  int2 pixel = (int2)(get_global_id(0), get_global_id(1));
  float4 colour = read_imagef(src, sampler, pixel);

  float total = 0.0f;

  for(int i = 0; i < 3; i++)
  {
    total += colour[i];
  }

  total /= 3.0f;
  total = clamp(total, 0.0f, 1.0f);

  float4 outColour = (float4)(total, total, total, 1.0);
  write_imagef(dest, pixel, outColour);
}

__kernel void gaussian_filter(__read_only image2d_t src, __write_only image2d_t dest, sampler_t sampler, int width, int height)
{
  int2 startImageCoord = (int2)(get_global_id(0) - 1, get_global_id(1) - 1);
  int2 endImageCoord = (int2)(get_global_id(0) + 1, get_global_id(1) + 1);
  int2 outImageCoord = (int2)(get_global_id(0), get_global_id(1));

  float kernelWeights[9] =
  {
    1.0f, 2.0f, 1.0f,
    2.0f, 4.0f, 2.0f,
    1.0f, 2.0f, 1.0f
  };

  if(outImageCoord.x < width && outImageCoord.y < height)
  {
    int weight;
    float4 outColor = (float4)(0.0f, 0.0f, 0.0f, 0.0f);

    for(int y = startImageCoord.y; y <= endImageCoord.y; y++)
    {
      for(int x = startImageCoord.x; x <= endImageCoord.x; x++)
      {
        outColor += (read_imagef(src, sampler, (int2)(x, y)) * (kernelWeights[weight] / 9.0f));
        weight+=1;
      }
    }

    write_imagef(dest, outImageCoord, outColor);
  }
}
