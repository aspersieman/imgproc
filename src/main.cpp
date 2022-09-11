#include "Image.h"

int main(int argc, char** argv) {
  // TEST 1
  // Test creating, copying and writing new images
  Image test1("test/test.jpg");
  test1.write("build/test_result_1.png");
  Image copy = test1;
  for(int i = 0; i < copy.w * copy.channels; ++i) {
    copy.data[i] = 255;
  }
  copy.write("build/test_result_1_copy.png");
  Image blank(100, 100, 3);
  blank.write("build/test_blank.jpg");

  // // TEST 2
  // // grayscale
  Image gray_avg = test1;
  gray_avg.grayscale_avg();
  gray_avg.write("build/test_gray_avg.png");

  Image gray_lum = test1;
  gray_lum.grayscale_avg();
  gray_lum.write("build/test_gray_lum.png");

  // // TEST 3
  // // Test colour mask
  Image colour_mask = test1;
  gray_lum.colour_mask(0, 0, 1);
  gray_lum.write("build/test_colour_mask_blue.png");

  // TEST 4
  // Test diffmap
  Image test2("test/test.jpg");
  Image test3("test/test2.jpg");
  Image diff = test2;
  diff.diffmap(test3);
  diff.write("build/test_diffmap_against_test2.png");
  // Test diffmap_scale
  Image test4("test/test.jpg");
  // Change arbitrary pixels to test if difference can be found
  test4.data[100] += 1;
  test4.data[101] += 1;
  test4.data[102] += 1;
  test4.data[200] += 1;
  test4.data[201] += 1;
  test4.data[202] += 1;
  test4.data[300] += 1;
  test4.data[301] += 1;
  test4.data[302] += 1;
  test4.write("build/test_diffmap_scale_changed.png");
  Image diff2 = test1;
  diff2.diffmap_scale(test4);
  diff2.write("build/test_diffmap_scale_against_test2.png");
  
  // TEST 5
  // Convolve clamp to 0
  // Emboss
  Image test5("test/test.jpg");
  double ker_emboss[] = {
    -2 / 9.0, -1 / 9.0, 0,
    -1 / 9.0, 1 / 9.0, 1 / 9.0,
    0, 1 / 9.0, 2 / 9.0
  };
  test5.std_convolve_clamp_to_0(0, 3, 3, ker_emboss, 1, 1);
  test5.std_convolve_clamp_to_0(1, 3, 3, ker_emboss, 1, 1);
  test5.std_convolve_clamp_to_0(2, 3, 3, ker_emboss, 1, 1);
  test5.write("build/test_convolve_to_0_emboss.png");

  // Gaussian blur
  Image test6("test/test.jpg");
  double ker_gauss[] = {
    1 / 16.0, 2 / 16.0, 1 / 16.0,
    2 / 16.0, 4 / 16.0, 2 / 16.0,
    1 / 16.0, 2 / 16.0, 1 / 16.0
  };
  test6.std_convolve_clamp_to_0(0, 3, 3, ker_gauss, 1, 1);
  test6.std_convolve_clamp_to_0(1, 3, 3, ker_gauss, 1, 1);
  test6.std_convolve_clamp_to_0(2, 3, 3, ker_gauss, 1, 1);
  test6.write("build/test_convolve_to_0_gauss.png");

  // TEST 6
  // Convolve clamp to 0
  // Emboss
  Image test7("test/test.jpg");
  test7.std_convolve_clamp_to_border(0, 3, 3, ker_emboss, 1, 1);
  test7.std_convolve_clamp_to_border(1, 3, 3, ker_emboss, 1, 1);
  test7.std_convolve_clamp_to_border(2, 3, 3, ker_emboss, 1, 1);
  test7.write("build/test_convolve_to_border_emboss.png");

  // Gaussian blur
  Image test8("test/test.jpg");
  test6.std_convolve_clamp_to_border(0, 3, 3, ker_gauss, 1, 1);
  test6.std_convolve_clamp_to_border(1, 3, 3, ker_gauss, 1, 1);
  test6.std_convolve_clamp_to_border(2, 3, 3, ker_gauss, 1, 1);
  test6.write("build/test_convolve_to_border_gauss.png");

  return 0;
}
