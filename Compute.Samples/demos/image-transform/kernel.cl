
__kernel void transform(__read_only image2d_t src, __write_only image2d_t dest, sampler_t sampler, int width, int height)
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