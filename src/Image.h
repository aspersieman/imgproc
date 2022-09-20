#include <stdint.h>
#include <cstdio>
#include <complex>

//legacy feature of C
#undef __STRICT_ANSI__
#define _USE_MATH_DEFINES 
#include <cmath>
#ifndef M_PI
	#define M_PI (3.14159265358979323846)
#endif

#if !defined(__CHEERP__)
#include "Font.h"
#endif

#define STEG_HEADER_SIZE sizeof(uint32_t) * 8

enum ImageType {
  PNG, JPG, BMP, TGA
};

struct Image {
  uint8_t* data = NULL;
  size_t size = 0;
  int w;
  int h;
  int channels;

  Image(const char* filename, int channel_force = 0);
  Image(int w, int h, int channels = 3);
  Image(const Image& img);
  ~Image();

  bool read(const char* filename, int channel_force = 0);
  bool write(const char* filename);

  ImageType get_file_type(const char* filename);

  Image& grayscale_avg();
  Image& grayscale_lum();

  Image& colour_mask(float r, float g, float b);

	Image& flip_x();
	Image& flip_y();

  Image& diffmap(Image& img);
  Image& diffmap_scale(Image& img, uint8_t scl = 0);
  
  Image& std_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
  Image& std_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
  Image& std_convolve_cyclic(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);

	static uint32_t rev(uint32_t n, uint32_t a);
	static void bit_rev(uint32_t n, std::complex<double> a[], std::complex<double>* A);

	static void fft(uint32_t n, std::complex<double> x[], std::complex<double>* X);
	static void ifft(uint32_t n, std::complex<double> X[], std::complex<double>* x);
	static void dft_2D(uint32_t m, uint32_t n, std::complex<double> x[], std::complex<double>* X);
	static void idft_2D(uint32_t m, uint32_t n, std::complex<double> X[], std::complex<double>* x);

	static void pad_kernel(uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc, uint32_t pw, uint32_t ph, std::complex<double>* pad_ker);
	static inline void pointwise_product(uint64_t l, std::complex<double> a[], std::complex<double> b[], std::complex<double>* p);

	Image& fd_convolve_clamp_to_0(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& fd_convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& fd_convolve_cyclic(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	
	Image& convolve_linear(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& convolve_clamp_to_border(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);
	Image& convolve_cyclic(uint8_t channel, uint32_t ker_w, uint32_t ker_h, double ker[], uint32_t cr, uint32_t cc);

  Image& overlay(const Image& source, int x, int y);

  #if !defined(__CHEERP__)
	Image& overlay_text(const char* txt, const Font& font, int x, int y, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255);
  #endif

	Image& crop(uint16_t cx, uint16_t cy, uint16_t cw, uint16_t ch);

	Image& resizeNN(uint16_t nw, uint16_t nh);
};
