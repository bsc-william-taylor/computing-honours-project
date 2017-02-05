

__kernel void grayscale(__read_only image2d_t src, __write_only image2d_t dest, sampler_t sampler)
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
  write_imagef(dest, pixel, (float4)(total, total, total, 1.0));
}